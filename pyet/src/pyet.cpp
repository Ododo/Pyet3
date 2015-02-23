#include <boost/python.hpp>
#include <dlfcn.h>
#include <iostream>
#include <cstdarg>
#include <cstdint>

#include "../include/pyet.hpp"
#include "../include/wrapper.hpp"
#include "../include/tools.hpp"


using namespace boost;

//

python::object pyet; //imported module object
World* world = new World; //Collect informations from the game on runtime

static SYSCALL engine_syscall =  (SYSCALL)-1;

//
template<class T>
void PYETPRINT(T str){
    std::cout<<
    "***************\n" <<
    "PYET MSG\n" <<
    "--------\n\n" <<
    str << "\n" <<
    "***************" << std::endl;
}

int wrapper_syscall (int arg, ...){
   //Wrap calls from the mod
   void *arguments = __builtin_apply_args();
   void *result = __builtin_apply((UVARIADIC) engine_syscall, arguments, 16*sizeof(intptr_t));

   va_list  ap;
   va_start(ap, arg);

   if (arg == G_LOCATE_GAME_DATA){
       world->entities = va_arg(ap, gentity_t *);
   }

   //if (arg == G_LINKENTITY){
   //    gentity_t *gent =  va_arg(ap,  gentity_t *);
   //    if (gent->r.linkcount == 1){
        // if it is a new entity , set/replace our null/old entity ptr
    //      world->entities[gent->s.number] = gent;
   //    }
   //}

   va_end(ap);
   __builtin_return(result); // return what the engine wants to return
}

extern "C"{

__attribute__((visibility("default")))
SYSCALL dllEntry( SYSCALL syscallptr)
{
     //Get engine syscall and return our fake syscall
     engine_syscall = syscallptr;
     return wrapper_syscall;
}


__attribute__((visibility("default")))
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) 

{

    try{

    switch (command){

    case 0: //(GAME INIT)
    {

        EtCaller caller;
        //std::string game_mod = caller.et_Cvar_Get("fs_game");
        std::string dir("pyet");
        std::string str = "sys.path.append(\'./" + dir +  "\')";

        Py_Initialize();
        PyRun_SimpleString("import sys");
        PyRun_SimpleString(str.c_str());
        pyet = python::import("et");
        break;
    }

    case 8: //(GAME RUN FRAME)
    {
        world->leveltime = arg0; //update leveltime
        break;
    }

    }

    python::object wrapper = pyet.attr("Wrapper")(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
    //Perfom call to pyetw.wrapper

    }

    catch(...)
        {
                PyErr_Print();
                PyErr_Clear();
        }
    return -1;
}


/*/METHODS/*/

int EtCaller::et_gPrint(char const* msg) {
    engine_syscall( G_PRINT, msg );
    return 1;
}

int EtCaller::et_gError(char const* msg){
    engine_syscall( G_ERROR, msg);
    return 1;
}

std::string EtCaller::et_Cvar_Get(char const* cvar){
    char buff[256];
    engine_syscall(G_CVAR_VARIABLE_STRING_BUFFER, cvar, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

int EtCaller::et_Cvar_Set(char const* cvar, char const* value){
    engine_syscall( G_CVAR_SET, cvar, value );
    return 1;
}

std::string EtCaller::et_getConfigString(int i){
    char buff[256];
    ///UNSAFE
    engine_syscall( G_GET_CONFIGSTRING, i, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

int EtCaller::et_setConfigString(int i, char const* cvs){
    engine_syscall( G_SET_CONFIGSTRING, i, cvs);
    return 1;
}

int EtCaller::et_SendMsg(int client, char const* msg){
    engine_syscall( G_SENDMESSAGE, client, msg, sizeof(msg));
    return 1;
}

int EtCaller::et_ConsoleCmd(int delay, char const* cmd){
	engine_syscall( G_SEND_CONSOLE_COMMAND, delay, va("%s\n", cmd) );
	return 1;
}

int EtCaller::et_ServerCmd(int client, char const* cmd){
    if( strlen( cmd ) > 1022 ) {
		PYETPRINT("et_ServerCmd( ... ) length exceeds 1022.\n");
		return 0;
	}
	engine_syscall( G_SEND_SERVER_COMMAND, client, cmd );
	return 1;
}

int EtCaller::et_DropCLient(int client, char const* reason, int length) {
    engine_syscall( G_DROP_CLIENT, client, reason, length );
    return 1;
}

std::string EtCaller::et_GetUserInfo(int client) {
    char userinfo[1024];
    engine_syscall( G_GET_USERINFO, client, userinfo, sizeof(userinfo));
    std::string str(userinfo);
    return str;
}

int EtCaller::et_SetUserInfo(int client, char const* userinfo){
    engine_syscall( G_SET_USERINFO, client, userinfo);
    return 1;
}

int EtCaller::et_argc(){
    return engine_syscall( G_ARGC );
}

std::string EtCaller::et_argv(int i){
    char buff[1024];
    engine_syscall( G_ARGV, i, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

/*/Tools/*/

std::string EtTools::et_Info_ValueForKey( const char *s, const char *key ){
    std::string str(Info_ValueForKey(s, key));
    return str;
}

std::string EtTools::et_Info_RemoveKey(char const *s, const char *key ){
    char s_[1024];
    strcpy(s_,s);
    Info_RemoveKey(s_, key);
    std::string str(s_);
    return str;
}

std::string EtTools::et_Info_SetValueForKey(char const *s, const char *key, const char *value){
    char s_[1024];
    strcpy(s_, s);
    Info_SetValueForKey(s_, key, value);
    std::string str(s_);
    return str;
}
///*****///


/*/ENTITIES /*/

//World::* methods are rewrited ET functions, adapted for pyet.

gentity_t * World::GetFreeEntity(int &num){
    //Search a unused entity in our array
    int i;
    gentity_t * gent;

    for(i = MAX_CLIENTS; i<1023 ; i++){
        gent = this->entities + i;

        if(!gent){
            continue;
        }

        if (!gent->inuse){
            num = i; //ent->s.number is always 0 at this point but we know that the entity's num was i .

        engine_syscall(G_UNLINKENTITY, gent);
        
        // this->InitEntity(gent);
        return gent;
        }
    }
    return 0;
}


Entity* SpawnTempEntity(python::list tab, int event){
    //G_tempentity + G_SetOrigin in one function

    int num;
    vec3_t origin;
    gentity_t *e = world->GetFreeEntity(num);

    if (!e){
        return 0;
    }

    e->s.number = num;

    for(int i = 0; i<3 ; i++){
        origin[i] = python::extract<float>(tab[i]);
    }

    vec3_t snapped;

    e->s.eType = static_cast<entityType_t> (ET_EVENTS + event); //  c++ trick

    e->classname = "tempEntity";
    e->eventTime = world->leveltime; //level.time to world->leveltime
    e->r.eventTime =  world->leveltime;
    e->freeAfterEvent = qtrue;

    VectorCopy(origin, snapped);
    SnapVector(snapped);

    VectorCopy(snapped, e->s.pos.trBase);
    e->s.pos.trType = TR_STATIONARY;
    e->s.pos.trTime = 0;
    e->s.pos.trDuration = 0;
    VectorClear(e->s.pos.trDelta);

    VectorCopy(snapped, e->s.origin);
    VectorCopy(snapped, e->r.currentOrigin);

    if (e->client)
    {
        VectorCopy(snapped, e->client->ps.origin);
    }

    engine_syscall(G_LINKENTITY, e);

    return new Entity(e->s.number);
    //return e;
}

Entity* GetFreeEntity(){
    //Return a new Entity class if an entity is free
    int num;
    gentity_t *ent = world->GetFreeEntity(num);
    if (!ent){
        return 0;
    }

    return new Entity(num);
}

void InitEntity(int num){
    gentity_t * gent = world->entities + num;

    if (gent)
    {

    gent->inuse = qtrue;
    gent->classname = "noclass";
    gent->s.number = gent - world->entities;
    gent->r.ownerNum = 1022;
    gent->nextthink = 0;
    gent->free = NULL;
    gent->scriptStatus.scriptEventIndex = -1;
    gent->spawnTime = world->leveltime; //level.time;

    }
}

///

///Python Entity class
Entity::Entity(int index){
    this->index = index;
}

gentity_t* Entity::getentity(){
    return world->entities + this->index;
}

void Entity::link(){
    engine_syscall(G_LINKENTITY, this->getentity());
}
void Entity::unlink(){
    engine_syscall(G_UNLINKENTITY, this->getentity());
}

void Entity::Free(){
    gentity_t *en = this->getentity();
    if (en->free){
        en->free(en);
    }
    this->unlink();
}

void Entity::reached(){
    gentity_t *en = this->getentity();
    if (en->reached){
        en->reached(en);
    }
}

void Entity::blocked(int num){
    gentity_t *en = this->getentity();
    gentity_t *other = world->entities + num;
    if (en->blocked){
        en->blocked(en, other);
    }
}

void Entity::use(int num, int a){
    gentity_t *en = this->getentity();
    gentity_t *other = world->entities + num;
    gentity_t *activator = world->entities + a;
    if (en->use){
        en->use(en, other, activator);
    }
}

 void Entity::pain(int num, int damage, python::list point){
    gentity_t *en = this->getentity();
    gentity_t *attacker = world->entities + num;
    vec3_t array;
    ListToArray(3, array, point);
    if (en->pain){
        en->pain(en, attacker, damage, array);
    }
}

void Entity::die(int num, int a, int damage, int mod){
    gentity_t *en = this->getentity();
    gentity_t *inflictor = world->entities + num;
    gentity_t *attacker = world->entities + a;
    if(en->die){
        en->die(en, inflictor, attacker, damage, mod);
    }

}

python::object Entity::GetField(std::string field){

    return GetValueForString(world->entities, this->getentity(), field);
}

int Entity::SetField(std::string field, python::object value, int relink){
    gentity_t * ent;
    int result;

    ent = this->getentity();

    if(ent->r.linked){
        engine_syscall(G_UNLINKENTITY, ent);
    }

    result = SetValueForString(this->getentity(), field, value);

    if( result && relink){
        engine_syscall(G_LINKENTITY, ent);
    }

    return result;
}
///*****///

} //END EXTERN C

using namespace boost::python;
BOOST_PYTHON_MODULE(pyet)
{

    class_<EtCaller>("EtCaller")
        .def("gPrint", &EtCaller::et_gPrint, "Print message to console")
        .def("gError", &EtCaller::et_gError, "Raise an error, stop the game")
        .def("GetCvar", &EtCaller::et_Cvar_Get)
        .def("SetCvar", &EtCaller::et_Cvar_Set)
        .def("GetConfigStr", &EtCaller::et_getConfigString, "Get Info String by num")
        .def("SetConfigStr", &EtCaller::et_setConfigString, "Set Info String by num and value")
        .def("SendMsg", &EtCaller::et_SendMsg)
        .def("ServerCmd", &EtCaller::et_ServerCmd, "Send command to server, (client,cmd)")
        .def("ConsoleCmd", &EtCaller::et_ConsoleCmd, "Execute console command, (delay, cmd)")
        .def("DropClient", &EtCaller::et_DropCLient, "Kick/Ban a client for x second, (client, reason, length)")
        .def("GetUserInfo", &EtCaller::et_GetUserInfo, "Get Info string of client")
        .def("SetUserInfo", &EtCaller::et_SetUserInfo, "Set Info string of client, (client, InfoString userinfo)")
        .def("argc", &EtCaller::et_argc)
        .def("argv", &EtCaller::et_argv);

    class_<EtTools>("EtTools")
        .def("GetValueForKey", &EtTools::et_Info_ValueForKey, "Get Value for key in infostring")
        .def("RemoveKey", &EtTools::et_Info_RemoveKey, "Remove a key in infostring")
        .def("SetValueForKey", &EtTools::et_Info_SetValueForKey, "Set value by key in infostring (infostring, key, value)");

    //Python interface for world
    class_<Entity>("World", "Entity object must be initialized by passing the entity number to World ( ent = World(num) )", init<int>())
        .def_readonly("index", &Entity::index, "returns the entity Num")
        .def("GetField", &Entity::GetField, "Get field value for current entity, return type can be int,float,list or string")
        .def("SetField", &Entity::SetField, "(field, value, relink) - Set field value for current entity, value can be str,int,float or list for array field (vec3_t ..) \
                                            \n if last argument 'relink' is set to 1 that means you want the entity to be automatically relinked after being \
                                            \n unlinked and modified. It is  similar to \n ent.SetField('x', x , 0) ; ent.Link() , but more faster.")

        .def("Link", &Entity::link, "Link the current entity to world")
        .def("Unlink", &Entity::unlink,"Unlink the current entity from world")
        .def("free", &Entity::Free, "Free the current entity")
        .def("die", &Entity::die)
        .def("reached", &Entity::reached)
        .def("pain", &Entity::pain)
        .def("use", &Entity::use)
        .def("blocked", &Entity::blocked)
        .def("GetFreeEntity", &GetFreeEntity, return_value_policy<manage_new_object>(), "Get a free entity from world, if a free entity was found , World object is returned \
                                                                                    \n otherwise 0 is returned")
        .staticmethod("GetFreeEntity")

        .def("TempEntity", &SpawnTempEntity, return_value_policy<manage_new_object>())
        .staticmethod("TempEntity")

        .def("InitEntity", &InitEntity, "Set default values to entity, this is useful after calling World.GetFreeEntity()")
        .staticmethod("InitEntity")
        ;
}

#include <boost/python.hpp>
#include <dlfcn.h>
#include <iostream>
#include <cstdarg>

#include "../include/main.hpp"

using namespace boost;

python::object pyet;

extern "C"{

static int (*Pyet_syscall)( int arg, ... ) = (int (*)( int, ...))-1;

__attribute__((visibility("default")))
void dllEntry( int (*syscallptr)( int arg,... ) ) {
    Pyet_syscall = syscallptr;
    ///our syscall
}

__attribute__((visibility("default")))
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {

    try{

    if(command == 0){
        EtCaller caller;
        std::string game_mod = caller.et_Cvar_Get("fs_game");
        std::string str = "sys.path.append(\'./" + game_mod +  "\')";
        Py_Initialize();
        PyRun_SimpleString("import sys"); 
        PyRun_SimpleString(str.c_str());
        pyet = python::import("pyetw");
    }

    python::object wrapper = pyet.attr("Wrapper")(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);

    }
    catch(...)
        {
                PyErr_Print();
                PyErr_Clear();
        }
    return -1;
}

}


template<class T>
void PYETPRINT(T str){
    std::cout<<
    "***************\n" <<
    "PYET MSG\n" <<
    "--------\n\n" <<
    str << "\n" <<
    "***************" << std::endl;
}


///METHODS///
int EtCaller::et_gPrint(char const* msg) {
    Pyet_syscall( G_PRINT, msg );
    return 1;
}

int EtCaller::et_gError(char const* msg){
    Pyet_syscall( G_ERROR, msg);
    return 1;
}

std::string EtCaller::et_Cvar_Get(char const* cvar){
    char buff[256];
    Pyet_syscall(G_CVAR_VARIABLE_STRING_BUFFER, cvar, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

int EtCaller::et_Cvar_Set(char const* cvar, char const* value){
    Pyet_syscall( G_CVAR_SET, cvar, value );
    return 1;
}

std::string EtCaller::et_getConfigString(int i){
    char buff[256];
    ///UNSAFE
    Pyet_syscall( G_GET_CONFIGSTRING, i, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

int EtCaller::et_setConfigString(int i, char const* cvs){
    Pyet_syscall( G_SET_CONFIGSTRING, i, cvs);
    return 1;
}

int EtCaller::et_SendMsg(int client, char const* msg){
    Pyet_syscall( G_SENDMESSAGE, client, msg, sizeof(msg));
    return 1;
}

int EtCaller::et_ConsoleCmd(int delay, char const* cmd){
	Pyet_syscall( G_SEND_CONSOLE_COMMAND, delay, va("%s\n", cmd) );
	return 1;
}

int EtCaller::et_ServerCmd(int client, char const* cmd){
    if( strlen( cmd ) > 1022 ) {
		PYETPRINT("et_ServerCmd( ... ) length exceeds 1022.\n");
		return 0;
	}
	Pyet_syscall( G_SEND_SERVER_COMMAND, client, cmd );
	return 1;
}

int EtCaller::et_DropCLient(int client, char const* reason, int length) {
    Pyet_syscall( G_DROP_CLIENT, client, reason, length );
    return 1;
}

std::string EtCaller::et_GetUserInfo(int client) {
    char userinfo[1024];
    Pyet_syscall( G_GET_USERINFO, client, userinfo, sizeof(userinfo));
    std::string str(userinfo);
    return str;
}

int EtCaller::et_SetUserInfo(int client, char const* userinfo){
    Pyet_syscall( G_SET_USERINFO, client, userinfo);
    return 1;
}

int EtCaller::et_argc(){
    return Pyet_syscall( G_ARGC );
}

std::string EtCaller::et_argv(int i){
    char buff[1024];
    Pyet_syscall( G_ARGV, i, buff, sizeof(buff));
    std::string str(buff);
    return str;
}

//uintptr_t EtCaller::et_Cvar_Register(char const* name, char const* value, int flags){

//    vmCvar_t *cvar;
//    Pyet_syscall(G_CVAR_REGISTER, &cvar, name, value, flags);
//    return (uintptr_t)&cvar;
// }

// char const* EtCaller::et_Cvar_Update(uintptr_t addr){
//     vmCvar_t* cvar = (vmCvar_t*)addr;
//     Pyet_syscall(G_CVAR_UPDATE, cvar);
//     return cvar->string;
// }


///Tools///
std::string EtTools::et_Info_ValueForKey( const char *s, const char *key ){
    std::string str(Info_ValueForKey(s, key));
    return str;
}

std::string EtTools::et_Info_RemoveKey( char *s, const char *key ){
    Info_RemoveKey(s, key);
    std::string str(s);
    return str;
}

std::string EtTools::et_Info_SetValueForKey( char *s, const char *key, const char *value){
    Info_SetValueForKey(s, key, value);
    std::string str(s);
    return str;
}
///*****///


using namespace boost::python;
BOOST_PYTHON_MODULE(pyet)
{
    class_<EtCaller>("EtCaller")
        .def("gPrint", &EtCaller::et_gPrint)
        .def("gError", &EtCaller::et_gError)
        .def("GetCvar", &EtCaller::et_Cvar_Get)
        .def("SetCvar", &EtCaller::et_Cvar_Set)
        .def("GetConfigStr", &EtCaller::et_getConfigString)
        .def("SetConfigStr", &EtCaller::et_setConfigString)
        .def("SendMsg", &EtCaller::et_SendMsg)
        .def("ServerCmd", &EtCaller::et_ServerCmd)
        .def("ConsoleCmd", &EtCaller::et_ConsoleCmd)
        .def("DropClient", &EtCaller::et_DropCLient)
        .def("GetUserInfo", &EtCaller::et_GetUserInfo)
        .def("SetUserInfo", &EtCaller::et_SetUserInfo)
        .def("argc", &EtCaller::et_argc)
        .def("argv", &EtCaller::et_argv);
        //.def("RegisterCvar", &EtCaller::et_Cvar_Register)
        //.def("UpdateCvar", &EtCaller::et_Cvar_Update);

    class_<EtTools>("EtTools")
        .def("GetValueForKey", &EtTools::et_Info_ValueForKey)
        .def("RemoveKey", &EtTools::et_Info_RemoveKey)
        .def("SetValueForKey", &EtTools::et_Info_SetValueForKey);
}

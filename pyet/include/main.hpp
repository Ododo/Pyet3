#include <string>

#include "../include/ettools.hpp"
#include "../include/gent_parser.hpp"


class EtCaller
{
    public:
    int et_gPrint(char const* msg);
    int et_gError(char const* msg);
    std::string et_Cvar_Get(char const* cvar);
    int et_Cvar_Set(char const* cvar, char const* value);
    std::string et_getConfigString(int i);
    int et_setConfigString(int i, char const* cvs);
    int et_SendMsg(int client, char const* msg);
    int et_ConsoleCmd(int delay, char const* cmd);
    int et_ServerCmd(int client, char const* cmd);
    int et_DropCLient(int client, char const* reason, int length);
    std::string et_GetUserInfo(int client);
    int et_SetUserInfo(int client, char const* userinfo);
    int et_argc();
    std::string et_argv(int i);
    //uintptr_t et_Cvar_Register(char const* name, char const* value, int flags);
   // std::string et_Cvar_Update(uintptr_t addr);
};

class EtTools
{
    public:
    std::string et_Info_ValueForKey( char const *s, const char *key );
    std::string et_Info_RemoveKey( char const *s, const char *key );
    std::string et_Info_SetValueForKey( char const *s, const char *key, const char *value);
};


class Entity
{
    public:
    int set = 0;
    int index;

    Entity(int index);
    boost::python::object GetField(std::string);
    int SetField(std::string, boost::python::object, int);
    void Free();
    void link();
    void unlink();
    void reached();
    void blocked(int num);
    void use(int num, int a);
    void pain(int num, int damage, python::list point);
    void die(int num, int a, int damage, int mod);

    private:
    gentity_t * getentity();
};

//Runtime game informations.
class World{
    public:
    int leveltime;
    gentity_t *entities;
    gentity_t * GetFreeEntity(int&);
};

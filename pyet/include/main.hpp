class EtCaller
{
    public:
    int et_gPrint(char const* msg);
    int et_gError(char const* msg);
    char const* et_Cvar_Get(char const* cvar);
    int et_Cvar_Set(char const* cvar, char const* value);
    char const* et_getConfigString(int i);
    int et_setConfigString(int i, char const* cvs);
    int et_SendMsg(int client, char const* msg);
    int et_ConsoleCmd(int delay, char const* cmd);
    int et_ServerCmd(int client, char const* cmd);
    int et_DropCLient(int client, char const* reason, int length);
    char const* et_GetUserInfo(int client);
    int et_SetUserInfo(int client, char const* userinfo);
    int et_argc();
    char const* et_argv(int i);
};

class EtTools
{
    public:


};



#include <stdbool.h>

#include "common.h"
#include "pyet.h"

#define VM_CALL(cmd, ...)					\
	(vmcalls_allowed() ? engine_syscall(cmd, ##__VA_ARGS__)	\
	: vmcall_blocked(#cmd))

static SYSCALL engine_syscall;


void vmcalls_on(SYSCALL syscallptr)
{
	engine_syscall = syscallptr;
}

void vmcalls_off(void)
{
	engine_syscall = NULL;
}

static bool vmcalls_allowed(void)
{
	return engine_syscall != NULL;
}

static int vmcall_blocked(const char *cmd)
{
	LOG_ERR("vm call %s blocked: engine_syscall is not initialized", cmd);
	return 0;
}

/* Syscalls */

void vm_Print(const char *msg)
{
	VM_CALL(G_PRINT, msg);
}

void vm_Error(const char *msg)
{
	VM_CALL(G_ERROR, msg);
}

void vm_Cvar_Get(const char *cvar, char *buff, int bufferSize)
{
	VM_CALL(G_CVAR_VARIABLE_STRING_BUFFER, cvar, buff, bufferSize);
}

void vm_Cvar_Set(const char *cvar, const char *value)
{
	VM_CALL(G_CVAR_SET, cvar, value);
}

void vm_GetConfigString(int i, char *buff, int bufferSize)
{
	VM_CALL(G_GET_CONFIGSTRING, i, buff, bufferSize);
}

void vm_SetConfigString(int i, const char *cvs)
{
	VM_CALL(G_SET_CONFIGSTRING, i, cvs);
}

void vm_SendConsoleCommand(int exec_when, const char *text)
{
	VM_CALL(G_SEND_CONSOLE_COMMAND, exec_when, text);
}

void vm_SendServerCommand(int clientnum, const char *text)
{
	if (strlen(text) > 1022) {
		LOG_INFO("Ignoring server command > 1022");
		return;
	}
	VM_CALL(G_SEND_SERVER_COMMAND, clientnum, text);
}

void vm_GetUserInfo(int clientnum, char *buff, int bufferSize)
{
	VM_CALL(G_GET_USERINFO, clientnum, buff, bufferSize);
}

void vm_SetUserInfo(int clientnum, const char *userinfo)
{
	VM_CALL(G_SET_USERINFO, clientnum, userinfo);
}

void vm_DropClient(int clientnum, const char *reason, int length)
{
	VM_CALL(G_DROP_CLIENT, clientnum, reason, length);
}

int vm_SendMsg(int client, char *buf, int bufferSize)
{
	return VM_CALL(G_SENDMESSAGE, client, buf, bufferSize);
}

int vm_Milliseconds(void)
{
	return VM_CALL(G_MILLISECONDS);
}

int vm_Argc(void)
{
	return VM_CALL(G_ARGC);
}

void vm_Argv(int n, char *buffer, int bufferSize)
{
	VM_CALL(G_ARGV, n, buffer, bufferSize);
}

#ifndef _PYET_PYET_H
#define _PYET_PYET_H

#include <unistd.h>
#include <stdbool.h>

#include "common.h"

#ifdef HEADERS_ETLEGACY
#include "../etlegacy/src/qcommon/q_shared.h"
#include "../etlegacy/src/game/g_local.h"
#else
#include "../Enemy-Territory/src/game/q_shared.h"
#include "../Enemy-Territory/src/game/g_local.h"
#endif


extern void event_vmMain(intptr_t cmd, intptr_t arg0, intptr_t arg1,
			 intptr_t arg2, intptr_t arg3, intptr_t arg4,
			 intptr_t arg5, intptr_t arg6, intptr_t arg7,
			 intptr_t arg8, intptr_t arg9, intptr_t arg10,
			 intptr_t arg11);

extern void event_modSyscall(intptr_t cmd, intptr_t arg0, intptr_t arg1,
			     intptr_t arg2, intptr_t arg3, intptr_t arg4,
			     intptr_t arg5, intptr_t arg6, intptr_t arg7,
			     intptr_t arg8, intptr_t arg9, intptr_t arg10,
			     intptr_t arg11);

void vmcalls_on(SYSCALL syscallptr);
void vmcalls_off(void);

size_t gentity_get_fields_count(void);
size_t gclient_get_fields_count(void);
const struct gentity_field *gentity_get_fields(void);
const struct gentity_field *gclient_get_fields(void);


/* Syscalls */

void vm_Print(const char *msg);
void vm_Error(const char *msg);
void vm_Cvar_Get(const char *cvar, char *buff, int bufferSize);
void vm_Cvar_Set(const char *cvar, const char *value);
void vm_GetConfigString(int i, char *buff, int bufferSize);
void vm_SetConfigString(int i, const char *cvs);
void vm_SendConsoleCommand(int exec_when, const char *text);
void vm_SendServerCommand(int clientnum, const char *text);
void vm_GetUserInfo(int clientnum, char *buff, int bufferSize);
void vm_SetUserInfo(int clientnum, const char *userinfo);
void vm_DropClient(int clientnum, const char *reason, int length);
int vm_SendMsg(int client, char *buf, int bufferSize);
int vm_Milliseconds(void);
int vm_Argc(void);
void vm_Argv(int n, char *buffer, int bufferSize);

#endif

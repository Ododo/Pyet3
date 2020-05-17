#ifndef _WRAPPER_COMMON_H
#define _WRAPPER_COMMON_H

#include <unistd.h>
#include <stdbool.h>

#include "log.h"

#include "game_headers/game/q_shared.h"
#include "game_headers/game/g_local.h"

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

typedef intptr_t (*SYSCALL)(intptr_t arg, ...);

void vmcalls_on(SYSCALL syscallptr);
void vmcalls_off(void);
bool vm_Print(const char *msg);

#endif

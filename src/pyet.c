#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#include "common.h"
#include "pyet.h"

static SYSCALL engine_syscall;


__attribute__((visibility("default")))
intptr_t wrapper_syscall(intptr_t arg, ...)
{
	/* Wrap calls from the mod */
	void *arguments = __builtin_apply_args();

	if (!engine_syscall) {
		LOG_ERR("Mod syscall rcv but engine ptr is null");
		return -1;
	}

	/* Pass arguments to cffi */
	__builtin_apply((void *) event_modSyscall, arguments,
			13*(sizeof(intptr_t)));

	void *result = __builtin_apply((void *) engine_syscall, arguments,
					13*sizeof(intptr_t));

	/* return what the engine wants to return */
	__builtin_return(result);
}


__attribute__((visibility("default")))
SYSCALL dllEntry(SYSCALL syscallptr)
{
	//Get engine syscall and return our fake syscall
	engine_syscall = syscallptr;

	vmcalls_on(syscallptr);

	LOG_INFO("Pyet loaded, vmcalls on");
	return wrapper_syscall;
}

__attribute__((visibility("default")))
intptr_t vmMain(intptr_t command, intptr_t arg0, intptr_t arg1, intptr_t arg2,
	   intptr_t arg3, intptr_t arg4, intptr_t arg5, intptr_t arg6,
	   intptr_t arg7, intptr_t arg8, intptr_t arg9, intptr_t arg10,
	   intptr_t arg11)
{

	event_vmMain(command, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
		     arg8, arg9, arg10, arg11);
	return 0;
}


__attribute__((destructor))
void dllDestructor(void)
{
	vmcalls_off();
	LOG_INFO("Pyet unloaded, vmcalls off");
}


#include <stdbool.h>

#include "common.h"

#define VM_CALL(...) (vmcalls_allowed() && engine_syscall(__VA_ARGS__))

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

bool vm_Print(const char *msg)
{
	return VM_CALL(G_PRINT, msg);
}

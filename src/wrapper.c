#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "common.h"

static intptr_t (*mod_vmMain)(intptr_t, ...);
static intptr_t (*pyet_vmMain)(intptr_t, ...);

static SYSCALL engine_syscall;

char *errstr;

bool library_loaded;

char pyet_path[2048];
char mod_path[2048];

void *mod_lib;
void *pyet_lib;


void dllEntry(SYSCALL syscallptr)
{
	void (*mod_dllEntry)(SYSCALL sys);
	SYSCALL (*pyet_dllEntry)(SYSCALL sys);
	SYSCALL wrapper;

	engine_syscall = syscallptr;

	mod_lib = dlopen(mod_path, RTLD_NOW);
	pyet_lib = dlopen(pyet_path, RTLD_LAZY | RTLD_GLOBAL);

	errstr = dlerror();

	if (errstr) {
		LOG_ERR("%s", errstr);
		return;
	}

	mod_dllEntry = (void (*)(SYSCALL)) dlsym(mod_lib, "dllEntry");
	pyet_dllEntry = (SYSCALL (*)(SYSCALL)) dlsym(pyet_lib, "dllEntry");

	if (mod_dllEntry && pyet_dllEntry) {
		wrapper = pyet_dllEntry(syscallptr);
		mod_dllEntry(wrapper);
	}

	else {
		LOG_ERR("Could not get dll entries");
	}
}

intptr_t vmMain(intptr_t command, intptr_t arg0, intptr_t arg1, intptr_t arg2,
	   intptr_t arg3, intptr_t arg4, intptr_t arg5, intptr_t arg6,
	   intptr_t arg7, intptr_t arg8, intptr_t arg9, intptr_t arg10,
	   intptr_t arg11)
{
	if (command == 0) {
		mod_vmMain = dlsym(mod_lib, "vmMain");
		pyet_vmMain = dlsym(pyet_lib, "vmMain");
	}

	if (!mod_vmMain || !pyet_vmMain) {
		LOG_ERR("Failed to get (mod/pyet)_vmMain symbols");
		return -1;
	}

	pyet_vmMain(command, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
		    arg8, arg9, arg10, arg11);

	return mod_vmMain(command, arg0, arg1, arg2, arg3, arg4, arg5, arg6,
			  arg7, arg8, arg9, arg10, arg11);
}

__attribute__((constructor))
void dllConstructor(void)
{
	char cwd[1024];

	if (library_loaded)
		return;

	memset(pyet_path, 0, sizeof(pyet_path));
	memset(mod_path, 0, sizeof(mod_path));

	getcwd(cwd, sizeof(cwd));
	strcat(pyet_path, cwd);
	strcat(mod_path, cwd);
	strcat(pyet_path, "/pyet/_pyet.so");
	strcat(mod_path, "/pyet/mod.so");
	library_loaded = true;

	LOG_INFO("Wrapper loaded\n");
}


__attribute__((destructor))
void dllDestructor(void)
{
	if (mod_lib)
		dlclose(mod_lib);
	if (pyet_lib)
		dlclose(pyet_lib);

	LOG_INFO("Wrapped unloaded");
}

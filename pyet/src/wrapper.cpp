#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <cstdint>
#include <unistd.h>
#include <string.h>

#include "../include/wrapper.hpp"

IVARIADIC mod_entryPoint;
IVARIADIC pyet_entryPoint;
char *errstr;

extern "C"{

static SYSCALL engine_syscall =  (SYSCALL)-1;

int library_loaded = 0;

char pyet_path[2048];
char mod_path[2048];

void *mod_lib;
void *pyet_lib;


__attribute__((visibility("default")))
void dllEntry( SYSCALL  syscallptr) 
{
    void  (*mod_dllEntry)( SYSCALL );
    SYSCALL  (*pyet_dllEntry)( SYSCALL);
    SYSCALL wrapper;

    engine_syscall = syscallptr;
    mod_lib = dlopen(mod_path, RTLD_NOW);
    pyet_lib = dlopen(pyet_path, RTLD_NOW | RTLD_GLOBAL);
    errstr = dlerror();

    if (errstr){
        std::cout << errstr << std::endl;
    }

    mod_dllEntry = (void  (*)( SYSCALL ) ) dlsym( mod_lib, "dllEntry" );
    pyet_dllEntry = (SYSCALL  (*)( SYSCALL ) ) dlsym( pyet_lib, "dllEntry" );

    if (mod_dllEntry && pyet_dllEntry){
        wrapper = pyet_dllEntry(syscallptr);
        mod_dllEntry(wrapper);
    }

    else
    {
        std::cout << "mod.so or pyet.so not found :" << std::endl;
        std::cout << "[Pyet]" << dlerror() << std::endl;
    }

}


__attribute__((visibility("default")))
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) 

{

    if(command == 0){
        mod_entryPoint = (IVARIADIC) dlsym( mod_lib, "vmMain" );
        pyet_entryPoint =(IVARIADIC) dlsym( pyet_lib, "vmMain" );
    }

    if(mod_entryPoint && pyet_entryPoint){
        pyet_entryPoint(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
        return mod_entryPoint(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
    }

    return -1;
}

}

__attribute__((constructor))
void dllConstructor (void)
{
    char cwd[1024];
    if (!library_loaded){

    getcwd(cwd, sizeof(cwd));
    strcat(pyet_path, cwd);
    strcat(mod_path, cwd);
    strcat(pyet_path, "/pyet/pyet.so");
    strcat(mod_path, "/pyet/mod.so");
    library_loaded = 1;

    }
}


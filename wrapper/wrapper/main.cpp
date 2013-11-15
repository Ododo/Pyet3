#include <dlfcn.h>
#include <iostream>

extern "C"{

void *mode_lib;
void *pyet_lib;


__attribute__((visibility("default")))
void dllEntry( int (*syscallptr)( int arg,... ) ) {

    void  (*mode_dllEntry)( int (*m_syscallptr)(int, ...) );
    void  (*pyet_dllEntry)( int (*m_syscallptr)(int, ...) );

    mode_dllEntry = (void  (*)( int (*)(int, ...) ) ) dlsym( mode_lib, "dllEntry" );
    pyet_dllEntry = (void  (*)( int (*)(int, ...) ) ) dlsym( pyet_lib, "dllEntry" );

    if (mode_dllEntry && pyet_dllEntry){
        mode_dllEntry(syscallptr);
        pyet_dllEntry(syscallptr);
    }

}

int (*mode_entryPoint)(int, ...);
int (*pyet_entryPoint)(int, ...);

__attribute__((visibility("default")))
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {

    if(command == 0){
        mode_entryPoint = (int (*)(int, ...))dlsym( mode_lib, "vmMain" );
        pyet_entryPoint = (int (*)(int, ...))dlsym( pyet_lib, "vmMain" );
    }

    if(mode_entryPoint && pyet_entryPoint){
        pyet_entryPoint(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
        return mode_entryPoint(command,arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11);
    }

    return -1;
}

}

__attribute__((constructor))
void dllConstructor (void)
{
    mode_lib = dlopen( "pyet/mode.so", RTLD_NOW);
    pyet_lib = dlopen( "pyet/pyet.so", RTLD_NOW);
}

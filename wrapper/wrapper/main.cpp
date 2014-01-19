#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include <cstdint>


typedef int  (*SYSCALL)( int arg, ... ) ;
typedef void (*UVARIADIC) (...);
typedef int  (*IVARIADIC)  (int...);

IVARIADIC mod_entryPoint;
IVARIADIC pyet_entryPoint;

extern "C"{

static SYSCALL engine_syscall =  (SYSCALL)-1;

void *mod_lib;
void *pyet_lib;


__attribute__((visibility("default")))
void dllEntry( SYSCALL  syscallptr) {
    engine_syscall = syscallptr;
    void  (*mod_dllEntry)( SYSCALL );
  //  void  (*pyet_dllEntry)( SYSCALL );
    SYSCALL  (*pyet_dllEntry)( SYSCALL);

    mod_dllEntry = (void  (*)( SYSCALL ) ) dlsym( mod_lib, "dllEntry" );
    pyet_dllEntry = (SYSCALL  (*)( SYSCALL) ) dlsym( pyet_lib, "dllEntry" );

    if (mod_dllEntry && pyet_dllEntry){
        SYSCALL wrapper = pyet_dllEntry(syscallptr);
        mod_dllEntry(wrapper);
    }
    else{
        std::cout << "mod.so or pyet.so not found :" << std::endl;
        std::cout << "[Pyet]" << dlerror() << std::endl;
    }

}


__attribute__((visibility("default")))
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11  ) {

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
    Dl_info dl_info;
    dladdr((void *)dllConstructor, &dl_info);
    std::string str(dl_info.dli_fname);
    std::string path = str.substr(0, str.size()-17);
    std::string pyet_path(path + "pyet.so");
    std::string mod_path(path + "mod.so");

    mod_lib = dlopen( mod_path.c_str(), RTLD_NOW);
    pyet_lib = dlopen( pyet_path.c_str(), RTLD_NOW | RTLD_GLOBAL);
}

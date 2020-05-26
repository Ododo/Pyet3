from cffi import FFI
import linecache
import os
import sys

ffibuilder = FFI()

ffi_exports_h = open("../ffi/ffi_exports.h")
fields_h = open("../src/fields.h", "r")

ffibuilder.set_source("_pyet", """
#include "../src/common.h"
#include "../src/fields.h"
#include "../src/pyet.h"
""", sources=["../src/pyet.c", "../src/vmcalls.c", "../src/fields.c"],
     extra_compile_args=[f'-D {sys.argv[1]}']
)

ffibuilder.cdef("""
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
    const struct gentity_field *gentity_get_fields(void);
    const struct gentity_field *gclient_get_fields(void);
    size_t gentity_get_fields_count(void);
    size_t gclient_get_fields_count(void);
""")

ffibuilder.cdef(ffi_exports_h.read())
ffibuilder.cdef(fields_h.read())

ffi_exports_h.close()
fields_h.close()


ffibuilder.embedding_api("""
    void event_vmMain({});
    void event_modSyscall({});
""".format(*([",".join((13*["intptr_t"]))]*2)))


ffibuilder.embedding_init_code("""
    from _pyet import ffi, lib
    import sys, os
    p = os.path.join(os.getcwd(), "pyet", "plugins")
    sys.path.insert(0, p)

    import plugins
    cbs = [p(ffi, lib) for p in plugins.loaded]

    @ffi.def_extern()
    def event_vmMain(*args):
        for c in cbs:
            c.dispatcher("vmMain", *args)

    @ffi.def_extern()
    def event_modSyscall(*args):
        for c in cbs:
            c.dispatcher("modSyscall", *args)
""")


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)

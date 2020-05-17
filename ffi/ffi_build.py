from cffi import FFI
import os


ffibuilder = FFI()

ffibuilder.set_source("_pyet", "", sources=["../src/pyet.c", "../src/vmcalls.c"])

ffibuilder.cdef("""
	bool vm_Print(const char *msg);
""")

ffibuilder.embedding_api("""
	void event_vmMain({});
	void event_modSyscall({});
""".format(*([",".join((13*["intptr_t"]))]*2)))

ffibuilder.embedding_init_code("""
	from _pyet import ffi, lib
	import sys, os
	p = os.path.join(os.getcwd(), "pyet")
	sys.path.insert(0, p)
	
	from plugins import plugins
	cbs = [p(lib) for p in plugins]

	@ffi.def_extern()
	def event_vmMain(*args):
		for c in cbs:
			c.dispatcher(*args)

	@ffi.def_extern()
	def event_modSyscall(*args):
		pass
		#print(f"event_modSyscall {args}")
""")


if __name__ == "__main__":
	ffibuilder.compile(verbose=True)

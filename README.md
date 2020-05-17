Pyet3
=====


Python3 scripting API for Wolfenstein:Enemy Territory 

This branch is an ongoing restructuration of the API to work with cffi and not boost::python anymore.
cffi is more lightweight and has very few dependencies.
Only a very few functionalities are currently supported such as listening to events and printing to the console :)



BUILD
============
	sudo pip3 -r requirements.txt #note: this only installs cffi for python and its dependencies
	cd build
	./build.sh

Installation
============

     Pyet can be used with any EnemyTerritory mod and with etlegacy on Linux x86 or x86_64.

    -Create a folder named pyet at the game root (enemyterritory/pyet) or (etlegacy/pyet) 
    -Rename the qagame.mp.(i386/x86_64).so of your ET mod to mod.so
    -Copy mod.so into the pyet folder
    -Copy qagame.mp.(i386/x86_64).so from build/out directory to your mod folder.
    -Copy build/out/plugins.py and build/out/pyet.so to the pyet directory 
    -Run etded/etlded as usual.
    
    
Get Started
===========

Just look at plugins/plugins.py
You can start to implement what to do on what event here.
self.vmcalls allows you  to call the engine.
Only one function is implemented for that version of Pyet3 currently:
self.vmcalls.vm_Print(bytes)

If you want to contribute or just hack and you want to extend the current functionalities here is what you can do:
Create a new function under self.vmcalls (very easy !)

edit src/vmcalls.c

see the current function

	bool vm_Print(const char *msg)
	{
		return VM_CALL(G_PRINT, msg);
	}

For it to be callable, it's just about adding it's prototype to ffi/ffi_build.py.

	ffibuilder.cdef("""
		bool vm_Print(const char *msg);
	""")


You can define whatever vmcall you want to implement in vmcalls, cffi will take take of the 
bindings for you.

so for exemple

	ffibuilder.cdef("""
		bool vm_Print(const char *msg);
		bool vm_Error(const char *msg);
	""")
Or something like that.

Next work for me is to reimplement those vmcalls and to handle entities or stuffs like that.


Coding style
================

pep 8 for python.
For C and other relevent files use linux kernel coding style which you can check with 
		
	./checkpatch.pl -F <files>
    
Troubleshooting
================

    You are free open issues on github, or to contact me 
    by mail (check my github profile).
       
  
Doc
======

    Events
    ======
        GameConsoleCommand()
        GameInit(leveltime, randomSeed, restart)
        GameShutdown()
        ClientConnect(client, firstTime, isBot)
        ClientBegin(client)
        ClientUserInfoChanged(client)
        ClientDisconnect(client)
        ClientCommand(client)
        ClientThink(client)
        GameRunFrame(leveltime)

        
    
        
    
    

Pyet3
=====


Python3 scripting API for Wolfenstein:Enemy Territory  (**server-side**)

This branch is an ongoing restructuration of the API to work with cffi and not boost::python anymore.
cffi is more lightweight and has very few dependencies.

Pyet can be used with any vanilla EnemyTerritory mod and with ETlegacy on Linux x86(not tested) or x86_64

No cross-compil yet so you'll have to do the x86 build on a 32-bit system or a chroot.

You will have to have Python >= 3.5 on your machine.

BUILD
============
>git clone https://github.com/Ododo/Pyet3

>git submodule init

If you are building for vanilla ET:
>git submodule update Enemy-Territory

If you are building for ETLegacy:
>git submodule update etlegacy

(This will clone the corresponding repository)

Then install the requirements and build:

>sudo pip3 -r requirements.txt #note: this only installs cffi for python and its dependencies

>cd build

>./build.sh [vanilla | etlegacy]


Installation
============
.

    -Create a folder named pyet at the game root (enemyterritory/pyet) or (etlegacy/pyet) 
    -Rename the qagame.mp.(i386/x86_64).so of your ET mod to mod.so
    -Copy mod.so into the pyet folder
    -Copy qagame.mp.(i386/x86_64).so from build/out directory to your mod folder.
    -Copy build/out/plugins dir and build/out/_pyet.so into the pyet directory 
    -Run etded/etlded as usual.
    
    
Get Started
===========

Just look at plugins/plugins.py
You can start to implement what to do on what event here by implementing them in the
MyPlugin class. Those events will be triggered **before** being called in the real mod.

       
  
    Events
    ======
    def GameConsoleCommand(self):
        pass

    def GameInit(self, leveltime, randomSeed, restart):
        pass

    def GameShutdown(self):
        pass

    def ClientConnect(self, client, firstTime, isBot):
        pass

    def ClientBegin(self, client):
        pass

    def ClientUserInfoChanged(self, client):
        pass

    def ClientDisconnect(self, client):
        pass

    def ClientCommand(self, client):
        pass

    def ClientThink(self, client):
        pass

    def GameRunFrame(self, leveltime):
        pass



### High level api
**self.easy** is an intance of the EasyApi class (plugins/easyapi.py)  that provides a layer on top of the cffi
api. It allows you to do the usual system calls of the server (trap_* functions in Lua api).
Not all those syscalls are implemented yet. (please contribute or create an issue if you need a specific syscall).


    def ClientConnect(self, client, firstTime, isBot):
        userinfo = self.easy.GetUserInfo(client)


### Cffi level api:
self.vmcalls allows you to call exported functions from c directly. (**vm_** prefix)
Those functions are implemented in src/vmcalls.c
Note that the types of the arguments have to be those defined by cffi.


### Entities

    def ClientBegin(self, client):
        gent = self.entities.get(client) #  Get entity object
        print(gent.classname)
        gcli = gent.client #  Player specific
        print(gcli.pers.netname)
        
 You can also set the entity attributes to another value. This will be effective in-memory,
 Just keep in mind that those changes are totally out of control by the module or the server vm.
Not all the types conversions are implemented and some fields are readonly.

Coding style
================

pep 8 for python.
For C and other relevent files use linux kernel coding style which you can check with 
		
	./checkpatch.pl -F <files>
    
Troubleshooting
================

    You are free open issues on github, or to contact me 
    by mail (check my github profile).

        
    
        
    
    

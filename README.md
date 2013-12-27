Pyet2
=====

Python scripting API for Wolfenstein:Enemy Territory 

    os : linux x86
    requirements : python 2.7


Installation
============

    -Rename the qagame.mp.i386.so of your Enemy Territory mod to mod.so
    -Extract Pyet2 to your mod directory (ex: enemyterritory/etpub/.)
    -Run etded as usually.
    In Theory, pyet can be used with any enemyTerritory mod ;)
    
    
How To
======

    Addons are located in the ./addons subdirectory.
    The python library pyetw allow you to interact with the game.
    
    -Create a file in this directory , for example my_first_addon.py .
    -In this file, create a class inherited from pyetw.Addon.
       see addons/example.py
    -add 'import my_first_addon' to addons/__init__.py
       
       
Communicate with pyet through the Console
========
    pyet_load [group] or pl [group] : load a group of addons.
    pyet_unload [group] or pu[group] : unload a group of addons.
    pyet_list or ps : list all the addons loaded.

       
       
  
Doc
======
(provisional documentation)
This api is very similar to LUA api, doc can easily be found on web.
The plugin is still in development, this is the list of features available at the moment:

    Events
        Events from server. (to implement)
    ======
    
    pyetw.Addon.
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
        
    EtCaller (pyetw.EtCaller)
        Class that allow you to call ET on runtime.
    =======
    
    pyetw.Addon.call.
        gPrint(msg) //print str on console / str
        gError(msg) // raise error with message /str
        GetCvar(cvar) // get value of cvar /str
        SetCvar(cvar,value) // set value to cvar /str,str
        GetConfigStr(i) // get the value of the ConfigString with number i /int, returns configString
        SetConfigStr(i, cvs) // set the value of ConfigString i to cvs /int,str(configString)
        SendMsg(client, msg) //int,str 
        ConsoleCmd(delay, cmd) //int,str
        ServerCmd(client, cmd) //int,str
        DropCLient(client, reason, length)  //int,str,int
        GetUserInfo(client) //int, returns str (infostring)
        SetUserInfo(client, userinfo) //int, str (infostring)
        argc() // returns int, 
        argv(i)// int , returns str
        
     EtTools(pyetw.EtTools)
         class with useful tools from ET.
     =======
     
     pyetw.Addon.tools.
         GetValueForKey(infostring, key) //str,str returns str (infostring)
         RemoveKey(infostring, key) //str,str returns str (infostring)
         SetValueForKey(infostring, key, value) //str,str,str returns str (infostring)
         
         
    Constants from ET can be found in EtConstants.py    
        
        
    
        
    
    

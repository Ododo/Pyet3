Pyet3
=====

DOC   ===> http://pywet.sourceforge.net/html/

Python scripting API for Wolfenstein:Enemy Territory 

    os : linux x86 / x64
    Requirements : python 3.x , boost-python (on debian-based systems : 'apt-get install python3(-dev) libboost-python-dev)'


Installation
============

     Pyet can be used with any EnemyTerritory mod.

    -Place the pyet folder at the game root ("../enemyterritory/pyet")
    -Rename the qagame.mp.(i386/x86_64).so of your Enemy Territory mod to mod.so
    -Place it into pyet folder ("../enemyterritory/pyet/mod.so")
    -Copy qagame.mp.(i386/x86_64).so (the fake one) from the archive to your mod folder.
    -Copy pyet.so from the archive to the pyet folder
    -Run etded as usual.
    
    
Get Started
===========

    Addons are located in the pyet/addons subdirectory.
    Create a file in this directory , for example my_addon.py.
    In this addon you have access to a couple of classes to interact with the game:
    
        pyet.EtCaller: used to perform calls to the game api 
            e.g: a = pyet.EtCaller().argv(0)
            
        pyet.EtTools: used to perform calls to some tool functions provided by the game 
            e.g: a = pyet.EtTools().GetValueForKey(configstring, key)
            
        pyet.World: The entity management class 
            e.g: entity = pyet.World(entitynum) ; a = entity.GetField(field)
            
        et.Listener: Each created class inheriting from et.Listener will catch events triggered by the api
            see addons/example.py to understand
        
        et.Client: Client class to interact with clients userinfo (not finished)
            e.g: a = Client(client_entity_num) ; a["name"] = "newname" //update in-game userinfo
            
    In order to load your addons on game initialization you must add 'set pyet_autoload addon1,addon2,..'
    to your autoexec.cfg
    


Troubleshooting
================

    Pyet is at a very unstable stade, if you encounter segfaults check if pyet has access to ET files.
    You are free open issues on github, or to contact me 
    by mail (check my github profile).
       
Communicate with pyet through the Console
========

    pyet_load or pl   [addon]
    pyet_unload or pu [addon]
    pyet_reload or pr [addon]
    pyet_state or ps : list all the addons and listeners loaded.
  
Doc
======
SEE http://pywet.sourceforge.net/html/
This api is very similar to LUA api, doc can easily be found on web.

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
        
         
    Constants from ET can be found in EtConstants.py    
        
        
    
        
    
    

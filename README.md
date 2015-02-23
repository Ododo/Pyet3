Pyet3
=====

DOC   ===> http://pywet.sourceforge.net/html/

Python scripting API for Wolfenstein:Enemy Territory 

    os : linux x86 / x64
    Requirements : python 3.x , boost-python (on debian-based systems : 'apt-get install python3(-dev) libboost-python-dev)'


Installation
============

     Pyet can be used with any EnemyTerritory mod.

    -place the pyet folder at the game root ("../enemyterritory/pyet")
    -Rename the qagame.mp.(i386/x86_64).so of your Enemy Territory mod to mod.so
    -place it into pyet folder ("../enemyterritory/pyet/mod.so")
    -Copy qagame.mp.(i386/x86_64).so (the fake one) from pyet folder to your mod folder.
    -Run etded as usually.
    
    
Get Started
===========

    Addons are located in the pyet/addons subdirectory.
    The python library et.py allow you to interact with the game.
    
    -Create a file in this directory , for example my_first_addon.py .
       see addons/example.py 


Troubleshooting
================

    Pyet is at a very unstable stade, if you encounter segfaults check if pyet has access to ET files.
    You are free open issues on github, or to contact me 
    by mail (check my github profile).
       
Communicate with pyet through the Console
========

    pyet_load or pl   [addon]
    pyet_unload or pu [addon]
    pyet_state or ps : list all the addons loaded.

  
Doc
======
SEE http://pywet.sourceforge.net/html/
This api is very similar to LUA api, doc can easily be found on web.

    Events
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
        
         
    Constants from ET can be found in EtConstants.py    
        
        
    
        
    
    

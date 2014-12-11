Pyet2
=====
r0.0.3


DOC   ===> http://pywet.sourceforge.net/html/

Python scripting API for Wolfenstein:Enemy Territory 

    os : linux x86 
    ( PyET will only work on a 32bits system, if you are on a 64bits system, use a virtualmachine or
    a 32-bits chroot)
                    
    Requirements : python 2.7 , boost-python


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



Troubleshooting
================

    Pyet is at a very unstable stade, if you encounter segfaults check if pyet has access to ET files.
    Forum address : http://pywet.sourceforge.net/forum/
    You are free to ask questions on IRC (#pyet, @quakenet), open issues on github, or contact me 
    by mail (check my github profile).
       
Communicate with pyet through the Console
========
    pyet_load [group] or pl [group] : load a group of addons.
    pyet_unload [group] or pu[group] : unload a group of addons.
    pyet_list or ps : list all the addons loaded.

       
       
  
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
        
        
    
        
    
    

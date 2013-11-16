import traceback

import pyet
from etConstants import *

def PyetPrint(text):
    print (
"""
**********
::Pyetw.py::

 %s
**********
"""%text ) 

class RunTime:
    loaded_addons=dict()
runtime = RunTime()

class Addon(object):
    oninit=1
    name="Main"
    group="pyetw"
    
    def __init__(self):
        self.call = pyet.EtCaller()
        if self.oninit:
            runtime.loaded_addons[self.name] = self

    def __del__(self):
        del runtime.loaded_addons[self.name]

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
    
try:
    import addons
except (ImportError, SyntaxError):
    PyetPrint(traceback.format_exc())

############

def Wrapper(*args):
    """
    Et Callbacks
    """
    cmd = args[0]
    if cmd == GAME_INIT:
        f = "GameInit"
        tpl= args[0:3]
    elif cmd == GAME_SHUTDOWN:
        f = "GameShutdown"
        tpl = ()
    elif cmd == GAME_CLIENT_CONNECT:
        f = "ClientConnect"
        tpl = args[0:3]
    elif cmd == GAME_CLIENT_BEGIN:
        f = "ClientBegin"
        tpl = args[0],
    elif cmd == GAME_CLIENT_USERINFO_CHANGED:
       f = "ClientUserInfoChanged"
       tpl = args[0],
    elif cmd == GAME_CLIENT_DISCONNECT:
        f = "ClientDisconnect"
        tpl = args[0],
    elif cmd == GAME_CLIENT_COMMAND:
        f = "ClientCommand"
        tpl = args[0],
    elif cmd == GAME_CLIENT_THINK:
        f = "ClientThink"
        tpl = args[0],
    elif cmd == GAME_RUN_FRAME:
        f = "GameRunFrame"
        tpl = args[0],
    elif cmd == GAME_CONSOLE_COMMAND:
        f = "GameConsoleCommand"
        tpl = ()

    for a in runtime.loaded_addons.values():
        getattr(a, f)(*tpl)

#################













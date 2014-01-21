# -*- coding: utf-8 -*-

import traceback

import pyet
from etConstants import *
from collections import defaultdict

CALLER = pyet.EtCaller()
TOOLS = pyet.EtTools()

def PyetPrint(text):
    print (
"""
**********
::Pyetw.py::

 %s
**********
"""%text ) 


class RunTime:
    loaded_addons = defaultdict(dict)
runtime = RunTime()

class Addon(object):
    name="Main"
    group="pyetw"
    
    def __init__(self):
        self.call = CALLER
        self.tools = TOOLS
        runtime.loaded_addons[self.group][self.name] = self

    def unload(self):
        pass

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


class Client(object):
    """
    The Client class give an easy access to the player attributes.
    and provides useful methods to interact with the client.
    To use it , import it from an addon with 'from pyetw import Client'
    and instanciate  'inst = Client()'.
    
    After that you have a nice access to client data:
    cl = inst.get_client(client)
    print cl["name"] // access UserInfo
    cl["name"] = "changedname" // update UserInfo
    cl.kick("msg", 1000) // kick player
    """

    def get_client(self, client_num):
        return self._client(client_num)

    class _client(dict):
        #available keys
  	keys = ["cg_etVersion", "cg_uinfo", "g_password",
                "cl_guid", "cl_anonymous","snaps", "rate", 
                "name", "cl_wwwDownload", "cl_punkbuster", 
                "ip"]

        def __init__(self, client_num):
            self.client_num = client_num
            self.call = CALLER
            self.tools = TOOLS
        
        def __getitem__(self, key):
            if key not in self.keys: 
               self.msg_error(key)
               return
            userinfo = self.call.GetUserInfo(int(self.client_num))
            return self.tools.GetValueForKey(userinfo, str(key))

        def __setitem__(self, key, value):
            if key not in self.keys: 
                self.msg_error(key)
                return
            userinfo = self.call.GetUserInfo(self.client_num)
            userinfo = self.setvalueforkey(userinfo, key, value)
            self.call.SetUserInfo(self.client_num, userinfo)
           
        def kick(self, reason, length):
            self.call.DropCLient(self.client_num, str(reason), int(length))

        def msg_error(self, key):
           PyetPrint("UserInfo Key %s doest not exist \
                    ; available keys are %s" % (key, repr(self.keys)) )

        def setvalueforkey(self, userinfo, key, value):
           """
           fix for self.tools.SetValueForkey
           """
           info = self.tools.RemoveKey(userinfo, key)
           return info + "\%s\%s" %(key,value)

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
    f = ""
    if cmd == GAME_INIT:
        f = "GameInit"
        tpl= args[0:3]

    elif cmd == GAME_SHUTDOWN:
        f = "GameShutdown"
        tpl = ()
    elif cmd == GAME_CLIENT_CONNECT:
        f = "ClientConnect"
        tpl = args[1:4]
    elif cmd == GAME_CLIENT_BEGIN:
        f = "ClientBegin"
        tpl = args[1],
    elif cmd == GAME_CLIENT_USERINFO_CHANGED:
       f = "ClientUserInfoChanged"
       tpl = args[1],
    elif cmd == GAME_CLIENT_DISCONNECT:
        f = "ClientDisconnect"
        tpl = args[1],
    elif cmd == GAME_CLIENT_COMMAND:
        f = "ClientCommand"
        tpl = args[1],
    elif cmd == GAME_CLIENT_THINK:
        f = "ClientThink"
        tpl = args[1],
    elif cmd == GAME_RUN_FRAME:
        f = "GameRunFrame"
        tpl = args[1],
    elif cmd == GAME_CONSOLE_COMMAND:
        f = "GameConsoleCommand"
        tpl = ()

    if f:
        for g in runtime.loaded_addons.values():
            for a in g.values():
                getattr(a, f)(*tpl)

#################















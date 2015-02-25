# -*- coding: utf-8 -*-

import traceback
import inspect

import pyet
import addons

from imp import reload
from etConstants import pyet_events


class RunTime:
    listeners = list()
    addons = dict()
runtime = RunTime()

class Listener:
        
    def __repr__(self):
        return "empty listener"

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

class Core(Listener):

    def __repr__(self):
        return "core listener"

    def loadAddon(self, name, re=False):
         try:
             a = __import__("addons." + name)
             module = getattr(a, name)
             if re:
                 reload(module) #in case of reloading
             runtime.addons[name] = module
             for attr in module.__dict__.values():
                 if inspect.isclass(attr) and attr is not Listener \
                                          and issubclass(attr, Listener):
                     runtime.listeners.append(attr())
             print("\nAddon %s loaded" %name)

         except (ImportError, SyntaxError):
             print(traceback.format_exc())

         return module

    def unloadAddon(self, module):
        #todo fix : allow a unique listener class to be used in multiple addons
        for l in list(runtime.listeners):
            if type(l) in runtime.addons[module].__dict__.values():
                print("removing listener %s" % l)
                runtime.listeners.remove(l)
        del runtime.addons[module]
        print("\nAddon unloaded")

    def GameInit(self, leveltime, randomSeed, restart):
        autoloads = pyet.EtCaller().GetCvar("pyet_autoload")
        if not autoloads:
            return
        for name in autoloads.split(','):
             self.loadAddon(name)

    def GameConsoleCommand(self):
        caller = pyet.EtCaller()
        cmd = caller.argv(0)
        module = caller.argv(1)

        if cmd in ("pyet_status", "ps"):
            print("\nActive addons:")
            for a in runtime.addons:
                print ("", a)
            print("\nActive listeners:")
            for a in runtime.listeners:
                print("", a)

        if not module: 
            return

        if cmd in ("pyet_load", "pl"):
            self.loadAddon(module)
       
        if cmd in ("pyet_unload", "pu"):
            self.unloadAddon(module)
           
        if cmd in ("pyet_reload", "pr"):
            self.unloadAddon(module)
            self.loadAddon(module, True)


runtime.listeners.append(Core())

def Wrapper(*args):
    for listener in runtime.listeners:
        func = getattr(listener, pyet_events[args[0]])
        func(* args[1:len(inspect.getargspec(func)[0])])


class Client:

    keys = ["cg_etVersion", "cg_uinfo", "g_password",
            "cl_guid", "cl_anonymous","snaps", "rate", 
            "name", "cl_wwwDownload", "cl_punkbuster", 
            "ip"]

    def __init__(self, client_num):
        self.client_num = client_num
        self.call = pyet.EtCaller()
        self.tools = pyet.EtTools()

    def __getitem__(self, key):
        if key not in Client.keys: 
           self.msg_error(key)
           return
        userinfo = self.call.GetUserInfo(int(self.client_num))
        return self.tools.GetValueForKey(userinfo, str(key))

    def __setitem__(self, key, value):
        if key not in Client.keys: 
            self.msg_error(key)
            return
        userinfo = self.call.GetUserInfo(self.client_num)
        userinfo = self.setvalueforkey(userinfo, key, value)
        self.call.SetUserInfo(self.client_num, userinfo)
           
    def kick(self, reason, length):
        self.call.DropClient(self.client_num, str(reason), int(length))

    def msg_error(self, key):
        print("UserInfo Key %s doest not exist \
                ; available keys are %s" % (key, repr(Client.keys)) )

    def setvalueforkey(self, userinfo, key, value):
       """
       fix for self.tools.SetValueForkey
       """
       info = self.tools.RemoveKey(userinfo, key)
       return info + "\%s\%s" %(key,value)



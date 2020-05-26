import os
import sys

from inspect import signature

from gentities import Gentities
from easyapi import EasyApi

class BasePlugin:

    vmMain_events = (
        "GameInit", "GameShutdown", "ClientConnect",
        "ClientBegin", "ClientUserInfoChanged", "ClientDisconnect",
        "ClientCommand", "ClientThink", "GameRunFrame",
        "GameConsoleCommand"
    )
     
    def __init__(self, ffi, lib):
        self.ffi = ffi
        self.lib = lib
        self.easy = EasyApi(ffi, lib)
        self.gentities = Gentities(ffi, lib)

    def dispatcher(self, event_type, *args):
        if event_type == "vmMain":
            ev = BasePlugin.vmMain_events[args[0]]
            f = getattr(self, ev)
            f(*args[1:len(signature(f).parameters)+1])
        elif event_type == "modSyscall":
            self.ModSyscall(*args)

    def ModSyscall(self, *args):
        if args[0] == self.lib.G_LOCATE_GAME_DATA:
            self.gentities.update(*args[1:4])

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



class MyPlugin(BasePlugin):
        def GameInit(self, leveltime, randomSeed, restart):
            self.easy.Print("Greetings from my Plugin !")

loaded = [MyPlugin]

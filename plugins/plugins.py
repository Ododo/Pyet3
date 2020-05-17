from inspect import signature


class BasePlugin:

    pyet_events = ("GameInit", "GameShutdown", "ClientConnect",
                   "ClientBegin", "ClientUserInfoChanged", "ClientDisconnect",
                   "ClientCommand", "ClientThink", "GameRunFrame",
                   "GameConsoleCommand")

    def __init__(self, vmcalls):
        self.vmcalls = vmcalls

    def dispatcher(self, *args):
        ev = BasePlugin.pyet_events[args[0]]
        if hasattr(self, ev):
            f = getattr(self, ev)
            f(*args[1:len(signature(f).parameters)+1])


class MyPlugin(BasePlugin):

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


plugins = [MyPlugin]
all = (plugins)

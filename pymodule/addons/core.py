from pyetw import Addon, runtime, PyetPrint

class Core(Addon):
    group= "core"
    name = "Core"

    def GameConsoleCommand(self):
        cmd = self.call.argv(0)
        if cmd in ("pyet_load", "pl"):
           group = self.call.argv(1)
           if group in [a.group for a in runtime.loaded_addons.values()]:
               PyetPrint("Addon group already loaded, try 'pyet_unload %s' before" %(group))
           else:
                reload(getattr( __import__("addons"), group))
                PyetPrint( "module loaded" )

        elif cmd in ("pyet_unload", "pu"):
           group = self.call.argv(1)
           runtime.loaded_addons = dict((n,a) for n,a in runtime.loaded_addons.iteritems() if a.group != group)
           PyetPrint( "module unloaded" )

CORE = Core()
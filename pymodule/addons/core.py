from pyetw import Addon, runtime, PyetPrint
from json import dumps

class Core(Addon):
    group= "core"
    name = "Core"

    def GameConsoleCommand(self):
        cmd = self.call.argv(0)
        if cmd in ("pyet_load", "pl"):
           group = self.call.argv(1)               
           if group in runtime.loaded_addons:
               PyetPrint("Addon group already loaded, try 'pyet_unload %s' before" %(group))
           else:
                reload(getattr( __import__("addons"), group)) #dirty
                PyetPrint( "group loaded" )

        elif cmd in ("pyet_unload", "pu"):
           group = self.call.argv(1)

           if group == "core":
               PyetPrint( "You can't unload the Core addon !" )
               return

           for a in runtime.loaded_addons[group].values():
               a.unload()
               del a
           del runtime.loaded_addons[group]

           PyetPrint( "group unloaded" )

        elif cmd in ("pyet_list", "ps"):
            dca =  dict( (n,a.keys()) for n,a in runtime.loaded_addons.iteritems())
            PyetPrint( "Loaded groups:\n " + dumps(dca, indent=2 ))

CORE = Core()

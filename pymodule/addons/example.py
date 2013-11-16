from pyetw import Addon

#Get Started with Pyet2 :)
#You can define several Addons in one file (group), each addon is represented by a class inherited from pyetw.Addon

class ExampleAddon(Addon):
    oninit=1 #run your addon on initialization ? (0 or 1)(default:1)
    group="example" #<--- The name of the file (group) where your addon is defined. (required)
    name= "ExampleAddon"# <---  Set the name you like (excluding 'Core','Main' and 'ExampleAddon'). 
                        #       Be careful to not give the same name twice. (required) 

    def __init__(self):
        Addon.__init__(self)# <--- required if overloading __init__()
        self.call.gPrint("ExampleAddon Loaded\n")#Access to ET functions through self.call.xxx
	
    #redefine which event you want to trigger
    def GameInit(self, leveltime, randomSeed, restart):
        #do stuff
        pass


inst = ExampleAddon()#required for each module, name of instance does not matter.





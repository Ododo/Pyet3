import pyet

from et import Listener
from et import Client #userinfo
from pyet import World #entities


class simpleListener(Listener):
    def __repr__(self):
        return "mylistener"

    def GameConsoleCommand(self):
        #parse configstrings example
        caller = pyet.EtCaller()
        tools = pyet.EtTools()

        if caller.argv(0) == "getkey":
            info = caller.GetConfigStr(int(caller.argv(1)))
            key = caller.argv(2)
            if info:
                print( "\nFound ConfigString !! : \n" + info)
                if key:
                    value = tools.GetValueForKey(info, key)
                    if value:
                        print ("\nValue in configstring for key %s is :" %key)
                        print (value)
                    else:
                        print ("\nkey does not exist in configstring")
            else:
                print("ConfigString is empty :/")

class ClientListener(Listener):

    """
    How to use the Client class
    """
    def __repr__(self):
        return "clientlistener"

    def ClientUserInfoChanged(self, clientnum):
        """
        This function reverse the player name
        """
        cl = Client(clientnum)
        
        current_name = cl["name"]
        new_name = current_name[::-1] #reverse the string
        cl["name"] = new_name #update userinfo (effective in game)
        #short version : cl["name"] = cl_["name"][::-1]


    def ClientThink(self, client):
        caller = pyet.EtCaller()
        ent = World(client)
        ping = ent.GetField("ps.ping")
        if ping > 1:
            caller.DropClient(client, "Too high ping !", 15)

  



#! /usr/bin/env python

####CONFIG##############
SERVER="irc.quakenet.org"
CHANNEL="#pyet"
NICKNAME="EtBOT"
PORT=6667
WELCOME_MSG="\o/"
ADMINS_MASKS = [""]
####CONFIG##############


import threading
import sys
from pyetw import Addon, PyetPrint
import irc.bot
    
        
class ETBot(Addon, irc.bot.SingleServerIRCBot):
    group="etirc"
    name = NICKNAME

    def __init__(self, channel, nickname, server, port=6667):
        Addon.__init__(self)
        irc.bot.SingleServerIRCBot.__init__(self, [(server, port)], nickname, nickname)
        self.channel = channel
        self.serv = None

        PyetPrint("""ETbot will now try to join the server
	%s on port %i
        with name %s
        on channel %s""" %(SERVER,PORT,NICKNAME,CHANNEL))

    def on_nicknameinuse(self, c, e):
        c.nick(c.get_nickname() + "_")

    def on_welcome(self, c, e):
        self.serv = c
        c.join(self.channel)
        c.privmsg(self.channel, WELCOME_MSG)

    def on_pubmsg(self,c ,e):
       """
       IRC ===> ET
       Simple message broadcast
       """
       msg = e.arguments[0]
       nick = e.source.nick
       self.call.ServerCmd(-1, str("cpm (IRC)%s:%s\n" %(nick, msg)) )

       #admin part
       if not e.source.host in ADMINS_MASKS:
           return
       msgl = msg.split()
       if msgl[0] == "!et" and len(msgl) >= 2:
           self.call.ConsoleCmd(0, str(" ".join(msgl[1:])))	

    def ClientCommand(self, client):
       """
       ET ===> IRC
       Simple message broadcast
       """
       client_name = self.tools.GetValueForKey(self.call.GetUserInfo(client), "name")
       cmd = self.call.argv(0)
       if cmd == "say":
           self.serv.privmsg(self.channel, "[%s] : %s" \
                       %(client_name, self.call.argv(1)))
            
    def unload(self):
        self.disconnect("Bye ! [Pyet/EtBOt]")

class ThreadManager(Addon):
    group="etirc"
    name = "threadmanager"	
    
    def __init__(self, bot):
        Addon.__init__(self)
        self.bot = bot
        self.th = threading.Thread(target=self.bot.start)
        self.th.start()

    def GameRunFrame(self, leveltime):
         """
         Need to update tty (to solve) 
         """
         sys.stdout.flush()

bot = ETBot(CHANNEL, NICKNAME, SERVER, PORT)
tm = ThreadManager(bot)


        



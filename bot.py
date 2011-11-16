#!/usr/bin/env python
# -*- coding: utf-8 -*-
############

import os
import sys
import serial
import re
import time
import Skype4Py

patts = [
         r"(?:please\s*)?(?:terabot)?\s*(?:open|abrir?)\s*(?:the|la)?\s*(?:(?:pod\s*)?bay)?\s*(?:puerta|door)",
         r"(?:^hal$|\s+hal$|^hal\s+)",
         r"1\s*",
         r"2\s*"
        ]

for i, patt in enumerate(patts):
    patts[i] = re.compile(patt)

def open_door(msj):
    ##serial.Serial("/dev/ttyS0").send(255)
    #os.popen("./send 255")
    msj.Chat.SendMessage("Done!")

def my_name(msj):
    msj.Chat.SendMessage("My name is NOT HAL, i'm TeraBot")

def dummy(msj):
    msj.Chat.SendMessage("Dummy test: " + msj.Body)

dic = {
        patts[0] : open_door,
        patts[1] : my_name,
        patts[2] : dummy,
        patts[3] : dummy
      } 

def nombrar(quien):
    nombre = str(quien)
    nombre = nombre.split(" ")[0]
    decir='espeak -v spanish "'+nombre+'"'
    f = os.popen(decir)

#skype.CreateChatWith(user).SendMessage('Hola')  

def usuarios_conectados():
    ninguno = True
    f = os.popen("espeak -v spanish 'Usuarios Conectados'")
    for usuario in skype.Friends():
        if usuario.OnlineStatus != 'OFFLINE' and usuario.OnlineStatus != 'UNKNOWN':
            nombrar(usuario.FullName)
            ninguno = False
    if ninguno:
        f = os.popen("espeak -v spanish 'Ninguno'")
        
def autobot(mensaje):
    linea = mensaje.Body.lower()
    for patt in patts:
        if re.match(patt, linea):
            dic[patt](mensaje)
    print(str(mensaje.FromDisplayName))

def say_hi(nick, status):
    print("Hola "+nick)
    print(status)

def OnNotify(status):
    pyisland = ["manuel", "pablo", "sergio", "mariano"]
    if "ONLINESTATUS ONLINE" in status:
        for user in pyisland:
            if user in status:
                say_hi(user, status)

def OnAttach(status):
    print 'API attachment status: ' + skype.Convert.AttachmentStatusToText(status)
    if status == Skype4Py.apiAttachAvailable:
        skype.Attach()
    if status == Skype4Py.apiAttachSuccess:
        #usuarios_conectados()
        print('***************************************')
    if status == 3:
        sys.exit()

def OnMessageStatus(Message, Status):
    if Status == 'RECEIVED':
        print(Message.FromDisplayName+": "+Message.Body)
        estado = autobot(Message)
        #Message.Chat.SendMessage("")            
        #Message.Chat.SendMessage("bien y vos?")        

    if Status == 'READ':
        pass #print(Message.FromDisplayName + ": " + Message.Body)            

    if Status == 'SENT':
        print("Yo: "+ Message.Body)

    if Status == 'SENDING':
        pass #print("Yo: " + Message.Body + " -->"

skype = Skype4Py.Skype()
skype.OnAttachmentStatus = OnAttach
skype.OnMessageStatus = OnMessageStatus
skype.OnNotify = OnNotify

print('***************************************')
print('Connectando con Skype..')
skype.Attach()

estado = ''
while 1:
    time.sleep(0.2)
    pass

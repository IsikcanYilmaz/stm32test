#!/usr/bin/python3
'''
UART MIDI Host Program based on the mido python MIDI library
Will send the STM32L053C8 MIDI messages thru UART.
Press 'q' to pause. CTRL-C to break out.
v0.1
'''
import mido
import keyboard
import time
import threading
import sys
import os
from serial import Serial

uartport = None
pause = False

keys = {                                             # Key note
        'z' : {'note':'1c', 'on':False, 'num':72 },  # z : C
        's' : {'note':'1cs','on':False, 'num':73 },  # s : C#
        'x' : {'note':'1d', 'on':False, 'num':74 },  # x : D
        'd' : {'note':'1ds','on':False, 'num':75 },  # d : D#
        'c' : {'note':'1e', 'on':False, 'num':76 },  # c : E
        'v' : {'note':'1f', 'on':False, 'num':77 },  # v : F
        'g' : {'note':'1fs','on':False, 'num':78 },  # g : F#
        'b' : {'note':'1g', 'on':False, 'num':79 },  # b : G
        'h' : {'note':'1gs','on':False, 'num':80 },  # h : G#
        'n' : {'note':'1a', 'on':False, 'num':81 },  # n : A
        'j' : {'note':'1as','on':False, 'num':82 },  # j : A#
        'm' : {'note':'1b', 'on':False, 'num':83 },  # m : B
        ',' : {'note':'2c', 'on':False, 'num':84 }   # , : C
       }

def serialInit():
    port = Serial("/dev/ttyACM0", baudrate=9600, timeout=3.0)
    return port

def serialRecvLine(port):
    retstr = ''
    uartchar = ''
    while(uartchar != b'\n'):
        uartchar = port.read(1)
        retstr += "".join(map(chr, uartchar))
    return retstr

def serialSendLine(port, line):
    port.write(line + "\n")

def serialSendBytes(port, bytes):
        port.write(bytes)

def testSerial(port):
    for i in range(0, 3):
        port.write('A'.encode());

def keyboardEvent(event):
    global pause

    msg = None
    if event.name == 'q':
        pause = True
    if event.name in keys:
        if event.event_type == 'down' and keys[event.name]['on'] == False:
            msg = mido.Message('note_on', note=keys[event.name]['num'])
            keys[event.name]['on'] = True
        elif event.event_type == 'up' and keys[event.name]['on'] == True:
            msg = mido.Message('note_off', note=keys[event.name]['num'])
            keys[event.name]['on'] = False
        else:
            return
        serialSendBytes(uartport, msg.bytes())
        #testSerial(uartport);
        print(keys[event.name], hex(msg.bytes()[0]), hex(msg.bytes()[1]), hex(msg.bytes()[2]), event.event_type)

def main():
    global uartport, pause

    print("KORGI Host MIDI Program")
    keyboard.hook(keyboardEvent)
    uartport = serialInit()
    while True:
        if pause:
            keyboard.unhook_all()
            input("Hit enter to resume.")
            keyboard.hook(keyboardEvent)
            print("Resuming.")
            pause = False
        pass

if __name__ == "__main__":
    main()

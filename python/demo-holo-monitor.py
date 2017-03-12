#!/usr/bin/python
# coding: utf8

# To build the Holobot module, please refer to the project README
# command to launch the demo :
# PYTHONPATH=. python ../demo-holo-monitor.py
 
from holobot import Holobot
import time

print("- connexion à Holobot")
# holo = Holobot('/dev/tty.usbmodem1451', 115200)
holo = Holobot('/dev/tty.holo-DevB', 115200)

holo.debug_state(1)

while True:
    try:
        time.sleep(1)
    except KeyboardInterrupt:
        break


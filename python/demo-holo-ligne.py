#!/usr/bin/python
# coding: utf8

# To build the Holobot module, please refer to the project README
# command to launch the demo :
# PYTHONPATH=. python ../demo-holo-obstacle.py
 
from holobot import Holobot
import time

holo = Holobot('/dev/tty.holo-DevB', 115200)
print("<tapper Ctrl-C pour arreter>")
holo.reset_yaw()

while holo.get_opt(2) < 0.30:
    holo.move_toward(50,0)
    time.sleep(0.050)
holo.move_toward(-30,0)
time.sleep(0.10)
while holo.get_opt(2) < 0.30:
    holo.move_toward(-10,0)
    time.sleep(0.050)

holo.stop_all()
time.sleep(0.10)





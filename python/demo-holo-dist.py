#!/usr/bin/python
# coding: utf8

# To build the Holobot module, please refer to the project README
# command to launch the demo :
# PYTHONPATH=. python ../demo-holo-monitor.py
 
import matplotlib.pyplot as plt
from holobot import Holobot
import time
import math

holo = Holobot('/dev/tty.holo-DevB', 115200)
print("- prise de mesure en cours")
print("<tapper Ctrl-C pour arreter>")

holo.reset_yaw()
distances = []
while True:
    try:
        t = holo.get_time()
        if int(0.75*t)%2 == 0:
            holo.turn(30)
        else:
            holo.turn(-30)
        az = holo.get_yaw()
        distances.append([math.fmod(az+60.0, 360.0), holo.get_dist(2)])
        distances.append([math.fmod(az+180.0,360.0), holo.get_dist(0)])
        distances.append([math.fmod(az+300.0, 360.0), holo.get_dist(1)])
        time.sleep(0.1)
    except KeyboardInterrupt:
        break

holo.stop_all()

X = []
Y = []
for c in distances:
    a = c[0]*math.pi/180 + math.pi/2
    d = c[1]
    if d < 20:
        X.append(d*math.cos(a))
        Y.append(d*math.sin(a))

plt.grid()
plt.scatter(X,Y)
plt.show()

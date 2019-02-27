# coding: utf8

# To build the Holobot module, please refer to the project README
# Go to your build directory and run the following command 
# python3 ../holobot/3-demo-monitor.py <serial port>

import sys
sys.path.append('.')

from holobot import Holobot
import time

if len(sys.argv) != 2:
    print ("error: I need the serial port (bluetooth or wired)")
    sys.exit(0)

holo = Holobot(sys.argv[1], 115200)

# Launch the calibration of the magnetic sensor.
# this limitates the drift of the orientation sensor of the robot

time.sleep(1)
print('calibration of the magnetic sensor, please wait 5 sec')
holo.calibrate_magneto()
time.sleep(5)

# here we just turn on the debug mode: print the global state of the robot
# at 20Hz.
holo.debug_state(1)
while True:
    try:
        time.sleep(1)
    except KeyboardInterrupt:
        break
holo.debug_state(0)


# coding: utf8

# To build the Holobot module, please refer to the project README
# Go to your build directory and run the following command 
# python3 ../holobot/1-demo-first.py <serial port>

# First, one adds the current directory to PYTHONPATH because we need
# to access to the holobot library: one supposes that you launch the
# command from your build directory.
# Note: this can be done manually within the launch command (PYTHONPATH=. python3 ...)
# you can add it also in your .bashrc
import sys
import time
sys.path.append('.')

# Here one import and create the entry point to speak to the robot
# the api is materialized by the instance holo defined below
# this is the object from which you ask robot commands.
from holobot import Holobot
if len(sys.argv) != 2:
    print ("error: I need the serial port (bluetooth or wired)")
    sys.exit(0)
# the constructor needs the port and the baudrate. 115200 bauds
# is the default baudrate defined for the communication onboard.
holo = Holobot(sys.argv[1], 115200)

print('Discover the Holobot...')

# illustation of sensor acces
print ('- distance sensor: %0.2f cm' % holo.get_dist())
time.sleep(1)
print ('- orientation (need calibration!): %0.1f°' % holo.get_yaw())
time.sleep(1)

print ('- optical sensors (%) : ', end='')
for i in range(7):
    print ('%0.2f ' % holo.get_opt(i), end='')
print ('')

print('- listen to the beeper !')
time.sleep(1)
holo.beep(880, 200)
time.sleep(1)
holo.beep(440, 200)
time.sleep(1)


# coding: utf8

# To build the Holobot module, please refer to the project README
# Go to your build directory and run the following command 
# python3 ../holobot/2-demo-motion.py <serial port>

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
import time
import sys
import math

if len(sys.argv) != 2:
    print ("error: I need the serial port (bluetooth or wired)")
    sys.exit(0)

holo = Holobot(sys.argv[1], 115200)
speed = 50

holo.beep(880, 200)

## 4 directions ##

for angle in [0, 90, 180, -90]:
    # motion is defined by giving the instantaneous velocity, linear and rotational
    holo.move_toward(speed, angle) # move at <speed> mm/s toward direction <angle> deg
                                   # rotational velocity is not modified here.
    time.sleep(1.0)
    holo.stop_all() # stop motors
    time.sleep(0.25)
    holo.move_toward(-speed, angle)
    time.sleep(1.0)
    holo.stop_all()
    time.sleep(0.25)

## Rotation ##

# the function control(dx,dy,rot) define the instantaneous speed in the X,Y
# directions <dx,dy> in mm/s and the rotation speed <rot> in deg/s.
holo.control(0,0,speed) # here one defines the rotational velocity, linear velocity is fixed to 0
time.sleep(1)
holo.stop_all()
time.sleep(0.250)
holo.control(0,0,-speed)
time.sleep(1)

## Cercle ##

t = 0.0
dt = 0.050
while t < 4.0:
    x = math.sin(2*math.pi * (t/4) - math.pi/2)
    y = math.sin(2*math.pi * (t/4))
    holo.control(50*x,50*y,0)
    t += dt    
    time.sleep(dt) # 20Hz

holo.stop_all()
time.sleep(1.0)
## Combine motions ##

t = 0.0
dt = 0.050
dir = 0
while t < 4.0:
    if (int(0.5*t)) % 2: rot = 23
    else: rot = -23
    holo.turn(rot) # defines the instantaneous rotation velocity (°/s)
                   # linear velocity is not modified  
    dir += rot*dt

    corr_f = 4.2
    if t < 2.0:
        holo.move_toward(speed, -corr_f*dir) # defines the linear velocity,
                                             # rotational velocity is not modified
    else:
        holo.move_toward(-speed, -corr_f*dir)
    # z = math.sin(2*math.pi * t/1.5)
    # holo.turn(speed*z)
    t += dt
    time.sleep(dt) # 20Hz
    
## Epilogue ##
holo.beep(440,200)


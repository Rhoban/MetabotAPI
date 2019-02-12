# MetabotAPI

Control metabot or holobot robots using API. This will work both in
USB and bluetooth.

## Connexion

There are two possible ways to connect the computer to the robot:

1. *By wire.* The robot is connected to the computer by a USB cable
connected to the robot by the USB B plug. After that, the robot shoud appear on the computer 

2. *By bluetooth.* Robot bluetooth connexion is available
directly. One must apair the robot as a bluetooth device.The connexion
code is 0000 or 1234. Under linux, the easiest way it to use the
blueman utility which offers a GUI.

Under windows or Mac OS X, one must connect the robot as an other
bluetooth device.

After this step, the robot must appear as a serial interface. Under
linux it can be something like /dev/rfcomm0 for bluetooth or /dev/ACM0
if the robot is wired. Under windows, it will appear as a COM
port. Under Mac OS X, it will appear as /dev/tty.usb<something>.

Details under linux:

   > sudo apt-get install blueman
   > sudo blueman-manager
   - right click on the bluetooth device corresponding to the robot
   - "connect to serial port"
   - the robot bluetooth entry should appear in /dev/
     for instance under the name rfcomm0 (it may vary).

## Using the C++ Library

The best way to learn how to use it is to have a look at the example provided in
the `cpp/` directory:

    cd cpp
    mkdir build
    cd build
    cmake ..
    make
    ./metabot

The `main.cpp` and the `CMakeLists.txt` provide a way to produce a binary that will
communicate with the robot.

## Using the python library

You need to install the `pythonXX-dev` packages (replace XX with your
version of python you want to use). For instance:
    sudo apt-get install python3-dev
for python3

First, you will need to compile the native library, for this:

    cd python
    mkdir build
    cd build
    cmake ..
    make
    
If you want, you can give a specific version of the target python (2.7, 3 etc.) like
this instead:

    cmake -DPYTHON_EXECUTABLE=/usr/bin/python ..

We recommand to use python3 as python2 is going to be not maintained
anymore. However, if you want to use python2, it is possible, change
the need python version in CMakelist.txt at lines 6 and 7.

Then, this will produce a `.so` file (`holobot.so`, `metabot.so` or
`metabot.cpython-....so`), this should be in your `PYTHONPATH` (or in
the directory where you run python command).

### Metabot robot

You can run the `demo.py` script from the build directory:

    PYTHONPATH=`pwd` python ../demo.py

You can add the following line in your .bashrc (linux) to add the *.so
to the python path:

    export PYTHONPATH="${PYTHONPATH}:/path/to/MetabotAPI/python/"

Under Mac OS X:
      
    cmake -DPYTHON_EXECUTABLE=/usr/local/bin/python ..

### Holobot robot

Go to the python directory, in your build directory.
Then launch the following command:

     python3 ../holobot/1-demo-first.py <holobot port>

where <holobot port> is the port of the robot (something like
/dev/ACM0 if wired or /dev/rfcomm0 if bluetooth connexion). Look after
in order to add a udev rule.

The python/holobot/ directory contains examples of python control code
in order to start.

## Linux: Automatic detection of the device interface:

Here one installs a udev rule in order to fix the name of the device in /dev directory

    sudo usermod -a -G plugdev $USER
    sudo usermod -a -G dialout $USER
    sudo cp scripts/45-holobot.rules /etc/udev/rules.d/
    sudo service udev restart
      [or, depending on the distribution linux]	 
    sudo restart udev

after that, pluggin the holobot should make it appear under the name /dev/holobot

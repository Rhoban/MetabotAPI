# MetabotAPI

Control metabot robots using API. This will work both in USB and bluetooth.

## Bluetooth under linux
   sudo apt-get install blueman
   sudo blueman-manager
   - click droit sur le periphérique bluetooth corresponding to the robot
   - "connect to serial port"
   - the robot bluetooth entry should appear in /dev/
     for instance under the name rfcomm0 (it may vary).

## Using the C++ Library

The best way to learn how to use it is to have a look at the example provided in
the `cpp/` directory:

    cd cpp/
    mkdir build
    cd build
    cmake ..
    make
    ./metabot

The `main.cpp` and the `CMakeLists.txt` provide a way to produce a binary that will
communicate with the robot.

## Using the python library

Note that you need to install the `pythonXX-dev` packages (replace XX with your
version of python you want to use).

First, you will need to compile the native library, for this:

    cd python/
    mkdir build
    cd build
    cmake ..
    make
    
If you want, you can give a specific version of the target python (2.7, 3 etc.) like
this instead:

    cmake -DPYTHON_EXECUTABLE=/usr/bin/python ..

Then, this will produce a `.so` file (`metabot.so` or `metabot.cpython-....so`), this
should be in your `PYTHON_PATH` (or in the directory where you run python command). For
example, you can run the `demo.py` script from the build directory:

    PYTHONPATH=`pwd` python ../demo.py

You can add the following line in your .bashrc (linux) to add the *.so to the python path:

    export PYTHONPATH="${PYTHONPATH}:/path/to/MetabotAPI/python/"

Under Mac OS X:
      
    cmake -DPYTHON_EXECUTABLE=/usr/local/bin/python ..

Installation of metabotapi for Holobot:
---------------------------------------

[tested on Raspberry Pi 3]

requirement:
- git
- cmake
- pythonXX-dev

> git clone  https://github.com/Rhoban/metabotapi.git
> cd metabotapi/src
> mkdir build
> cd build
> cmake ../.
> cd ../../python
> mkdir build
> cd build
> cmake ../.
> make

installation of a udev rule in order to fix the name of the device in /dev directory
> sudo usermod -a -G plugdev $USER
> sudo usermod -a -G dialout $USER
> sudo cp scripts/45-holobot.rules /etc/udev/rules.d/

> sudo service udev restart
ou
> sudo restart udev

after that, pluggin the holobot should make it appear under the name /dev/holobot

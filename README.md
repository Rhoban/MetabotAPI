# MetabotAPI

Control metabot robots using API. This will work both in USB and bluetooth.

## Using the C++ Library

The best way to learn how to use it is to have a look at the example provided in
the `cpp/` directory:

    cd cpp/
    mkdir build
    cd build
    cmake ..
    ./metabot

The `main.cpp` and the `CMakeLists.txt` provide a way to produce a binary that will
communicate with the robot.

## Using the python librrary

Note that you need to install the `pythonXX-dev` packages (replace XX with your
version of python you want to use).

First, you will need to compile the native library, for this:

    cd python/
    mkdir build
    cd build
    cmake ..

If you want, you can give a specific version of the target python (2.7, 3 etc.) like
this instead:

    cmake -DPYTHON_EXECUTABLE=/usr/bin/python ..

Then, this will produce a `.so` file (`metabot.so` or `metabot.cpython-....so`), this
should be in your `PYTHON_PATH` (or in the directory where you run python command). For
example, you can run the `demo.py` script from the build directory:

    PYTHONPATH=`pwd` python ../demo.py



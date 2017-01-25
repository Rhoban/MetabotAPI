#include "Robot.h"
#include <unistd.h>
#include <serial/serial.h>

namespace Metabot
{
    Robot::Robot(std::string name, int baud)
        : name(name), baud(baud)
    {
        thread = new std::thread([this]() {
            this->process();
        });
    }

    Robot::~Robot()
    {
        if (thread) {
            delete thread;
            thread = NULL;
        }
    }

    void Robot::process()
    {
        serial::Serial port(name, baud, serial::Timeout::simpleTimeout(1000));

        while (true) {
            if (port.waitReadable(1)) {
                size_t n = port.available();
                uint8_t *data = new uint8_t[n];
                port.read(data, n);

                for (size_t k=0; k<n; k++) {
                    printf("%c", data[k]);
                }

                delete[] data;
            }
        }
    }
}

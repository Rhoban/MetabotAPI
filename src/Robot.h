#pragma once

#include <string>
#include <thread>
#include <serial/serial.h>

#include "Packet.h"

namespace Metabot
{
    class Robot
    {
        public:
            Robot(std::string name, int baud=1000000);
            virtual ~Robot();
            
            virtual void onMonitor(Packet &packet)=0;
            void monitor(int frequency);

            void send(Packet &packet);
            void receive(Packet &packet);
            void process();

        protected:
            serial::Serial port;
            std::thread *thread;
    };
}

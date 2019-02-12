#pragma once

#include <string>
#include <mutex>
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
            
            void monitor(int frequency);
            void rhock_mode();

            void send(Packet &packet);
            virtual void receive(Packet &packet);
            void process();
            void set_verbose(int level);
              
        protected:
            bool over;
			int verbose;
            serial::Serial port;
            std::thread *thread;
            std::mutex mutex;
    };
}

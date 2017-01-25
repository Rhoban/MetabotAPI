#pragma once

#include <string>
#include <thread>

namespace Metabot
{
    class Robot
    {
        public:
            Robot(std::string name, int baud=1000000);
            virtual ~Robot();

            void process();

        protected:
            std::string name;
            int baud;
            std::thread *thread;
    };
}

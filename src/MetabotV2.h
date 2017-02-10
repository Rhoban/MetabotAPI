#pragma once

#include "Robot.h"

namespace Metabot
{
    class MetabotV2 : public Robot
    {
        public:
            enum {
                METABOT_MONITOR=5,
                METABOT_COMMAND=50
            };

            enum {
                START=0,
                STOP=1,
                ROTATE_CALIBRATION=2,
                SET_CONTROL=3,
                CONTROL=4,
                BEEP=5,
                LEDS=6,
                RESET=7
            };

            enum {
                LED_B=1,
                LED_G=2,
                LED_R=4
            };

            MetabotV2(std::string port, int baud=1000000);

            void receive(Packet &packet);
            Packet command(uint8_t instruction);

            /**
             * Wait for the robot to receive an update
             */
            void waitUpdate();

            /**
             * Enable the motors (this take several seconds since the torque is
             * slowly increased in the robot)
             */
            void start();

            /**
             * Disables the motors
             */
            void stop();

            /**
             * Reset (stops all motion, buzzer, restore leds etc.)
             */
            void reset();

            /**
             * Controls the robot speed (in mm/s and °/s)
             */
            void control(float x, float y, float turn);

            /**
             * Beeps (freq is Hz, duration is ms)
             */
            void beep(uint16_t freq, uint16_t duration);

            /**
             * LEDs
             */
            void setLeds(uint8_t value);

            /**
             * LEDs (by color name)
             */
            void setLeds(std::string color);

            // Motors position
            float motors[12];

            // Imu
            float yaw, pitch, roll;

            // Leds
            int leds[12];
            
            // Distance sensor
            float distance;

            // Voltage
            float voltage;
    };
}

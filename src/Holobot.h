#pragma once
#include "Robot.h"

#define METABOT_MONITOR 5
#define HOLOBOT_COMMAND 80

#define OPTICS_NB 5

namespace Metabot
{
    class Holobot : public Robot
    {
            bool output_state;
        public:
	    float current_time; 
	    float distances[3];
	    float optics[OPTICS_NB];
	    float wheel_speeds[3];
	    float gyro_yaw;
	    float acc_x, acc_y, acc_z;

            Holobot(std::string port, int baud=1000000);
            void receive(Packet &packet);
            Packet command(uint8_t instruction);
	    void waitUpdate();
	    
	    /* the time in seconds from the starting of the robot system */
	    float get_time();
	    /* distance sensors (cm), the sensors id are as follows:
	     * 0 : the distance sensor at the bottom of the usb plug
	     * 1 : the distance sensor of the switch (at the right of the robot, viewed from up) 
	     * 2 : the left one */
	    float get_dist(int i); 
	    /* optical sensors, in [0,1] */
	    float get_opt(int i); /* sensors are identified from 0 to 4, from right to left, viewed from up */
	    /* yaw, relative to the start in degree, in trigonometric way from the upper view */
	    float get_yaw(); /* the yaw computed from the gyro, more precise than the magnetic yaw, but drift (several degree/mn) */
	    /* the speeds of the wheels (deg/s). The wheels ids are as follows:
	     * 0: the wheel at the left (from up view) of the usb plug
	     * 1: the wheel at the right of the usb plug
	     * 2: the wheel at the opposite of the usb plug 
	     * the way (positive value) make the robot turn in the trigonometric way (from up view) */
	    float get_wheel_speeds(int id);

	    /* TODO: unités ? */
	    void control(float dx, float dy, float turn);
	    void set_board_led(uint8_t state);
	    void beep(short freq, short duration);
	    void play(short id);
	    void print_state();
	    void debug_state(uint8_t on_or_off);
    };
}

#include <map>
#include <iostream>
#include "MetabotV2.h"

namespace Metabot
{
    MetabotV2::MetabotV2(std::string port, int baud)
        : Robot(port, baud)
    {
    }

    void MetabotV2::receive(Packet &packet)
    {
        if (packet.type == METABOT_MONITOR && packet.getSize() == 40) {
            for (int k=0; k<12; k++) {
                motors[k] = packet.readSmallFloat();
            }
            
            yaw = packet.readSmallFloat();
            pitch = packet.readSmallFloat();
            roll = packet.readSmallFloat();

            for (int k=0; k<12; k+=2) {
                uint8_t b = packet.readByte();
                leds[k] = (b>>4)&0xf;
                leds[k+1] = b&0xf;
            }

            distance = packet.readSmallFloat();
            voltage = packet.readSmallFloat();
        }
    }

    Packet MetabotV2::command(uint8_t instruction)
    {
        return Packet(METABOT_COMMAND).appendByte(instruction);
    }

    void MetabotV2::start()
    {
        Packet packet = command(START);
        send(packet);
    }
    
    void MetabotV2::stop()
    {
        Packet packet = command(STOP);
        send(packet);
    }

    void MetabotV2::control(float x, float y, float turn)
    {
        Packet packet = command(CONTROL);
        packet.appendSmallFloat(x);
        packet.appendSmallFloat(y);
        packet.appendSmallFloat(turn);
        send(packet);
    }

    void MetabotV2::beep(uint16_t freq, uint16_t duration)
    {
        Packet packet = command(BEEP);
        packet.appendShort(freq);
        packet.appendShort(duration);
        send(packet);
    }

    void MetabotV2::setLeds(uint8_t value)
    {
        Packet packet = command(LEDS);
        packet.appendByte(value);
        send(packet);
    }
            
    void MetabotV2::setLeds(std::string color)
    {
        std::map<std::string, uint8_t> mapping = {
            {"red", LED_R},
            {"blue", LED_B},
            {"green", LED_G},

            {"yellow", LED_R|LED_G},
            {"cyan", LED_G|LED_B},
            {"magenta", LED_R|LED_B},

            {"off", 0},
            {"white", LED_R|LED_G|LED_B},
        };

        if (mapping.count(color)) {
            setLeds(mapping[color]);
        } else {
            std::cerr << "Unknown color: " << color << std::endl;
        }
    }
}

#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Holobot.h"

namespace Metabot
{

  Holobot::Holobot(std::string port, int baud) 
    : Robot(port, baud)
  {
    output_state = false;
  }

  void Holobot::receive(Packet &packet) {
    if (packet.type == METABOT_MONITOR) {
      for (int i=0; i<3; i++)
	distances[i] = packet.readSmallFloat();
      for (int i=0; i<OPTICS_NB; i++) 
	optics[i] = ((float) packet.readByte()) / 255;
      for (int i=0; i<3; i++)
	wheel_speeds[i] = packet.readSmallFloat();
      gyro_yaw = 10*packet.readSmallFloat();
      current_time = (float) ((uint32_t) packet.readInt()) / 1000;
      if (output_state) print_state();
      mutex.unlock();
    }
  }

  void Holobot::waitUpdate()
  {
    mutex.lock();
  }

  float Holobot::get_dist(int i) {
    if (i<0 || i>=3) return 0.0;
    return distances[i];
  }

  float Holobot::get_opt(int i) {
    if (i<0 || i>=OPTICS_NB) return 0.0;
    return optics[i];
  }

  float Holobot::get_yaw() {
    return gyro_yaw;
  }

  float Holobot::get_time() {
    return current_time;
  }

  Packet Holobot::command(uint8_t instruction) {
    return Packet(HOLOBOT_COMMAND).appendByte(instruction);
  }

  void Holobot::set_board_led(uint8_t state) {
    Packet p = command(0);
    p.appendByte(state);
    send(p);
  }

  void Holobot::control(float dx, float dy, float turn)
  {
    // TODO: attention aux limites (faire remonter un warning en cas de dépassement)
    Packet packet = command(2);
    packet.appendShort((short) dx);
    packet.appendShort((short) dy);
    packet.appendShort((short) turn);
    send(packet);
  }

  void Holobot::beep(short freq, short duration)
  {
    // TODO: attention aux limites
    Packet packet = command(3);
    packet.appendShort(freq);
    packet.appendShort(duration);
    send(packet);
  }

  void Holobot::play(short id)
  {
    // TODO: attention aux limites
    Packet packet = command(4);
    packet.appendShort(id);
    send(packet);
  }

  void Holobot::print_state() {
    printf("-------------------------------------------------------------------------------\n");
    printf("- time : %0.3fs\n", current_time);
    printf("- wheel speeds(deg/s): %4.1f %4.1f %4.1f\n", wheel_speeds[0], wheel_speeds[1], wheel_speeds[2]);
    printf("- opticals (%%):");
    for (int i=0; i<OPTICS_NB; i++) printf("%3.0f", 100*optics[i]);
    printf("\n");
    printf("- distances (cm): %4.1f %4.1f %4.1f\n", distances[0], distances[1], distances[2]);
    printf("- gyro yaw (deg): %4.0f\n", gyro_yaw);
  }

  void Holobot::debug_state(uint8_t on_or_off) {
    output_state = (bool) on_or_off;
  }
}


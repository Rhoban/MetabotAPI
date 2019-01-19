#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "Holobot.h"
#include <math.h>

namespace Metabot
{

  Holobot::Holobot(std::string port, int baud) 
    : Robot(port, baud)
  {
    output_state = false;
    usleep(250000);
    rhock_mode();
    usleep(250000);
    printf("- monitoring at 20Hz\n");
    monitor(20);
    waitUpdate();
    sent_dx = 0;
    sent_dy = 0;
    sent_turn = 0;
    yaw0 = 0;
    experiment_mode = false;
    if (experiment_mode)
      experiment_file = fopen("experiment.log", "w");
    else
      experiment_file = NULL;
  }

  Holobot::~Holobot() {
    control(0,0,0);
    usleep(500000);
    if (experiment_file != NULL) fclose(experiment_file);
  }

  void Holobot::receive(Packet &packet) {
    if (packet.type == METABOT_MONITOR) {
      // for (int i=0; i<3; i++)
      distances[0] = packet.readSmallFloat();
      distances[1] = -1; // txmp
      distances[2] = -1; // tmp
      for (int i=0; i<OPTICS_NB; i++) 
	optics[i] = ((float) packet.readByte()) / 255;
      for (int i=0; i<3; i++)
	wheel_speeds[i] = packet.readSmallFloat();
      if (experiment_mode) {
	for (int i=0; i<3; i++)
	  wheel_speed_tgts[i] = packet.readSmallFloat();
      }
      gyro_yaw = 10*packet.readSmallFloat();
      acc_x = 10*packet.readSmallFloat();
      acc_y = 10*packet.readSmallFloat();
      acc_z = 10*packet.readSmallFloat();
      current_time = (float) ((uint32_t) packet.readInt()) / 1000;
      if (output_state) print_state();
      if (experiment_file != NULL) {
	fprintf(experiment_file, "%f %f %f %f %f %f %f\n",
		current_time,
		wheel_speeds[0],wheel_speeds[1],wheel_speeds[2],
		wheel_speed_tgts[0], wheel_speed_tgts[1], wheel_speed_tgts[2]);
      }

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

  void Holobot::reset_yaw() {
    yaw0 = gyro_yaw;
  }

  float Holobot::get_yaw() {
    float yaw = gyro_yaw - yaw0;
    while (yaw < -180.0) yaw += 360;
    while (yaw > 180.0) yaw -= 360;
    return yaw;
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
    short dx_to_send = (short) dx;
    short dy_to_send = (short) dy;
    short turn_to_send = (short) turn;
    if (dx_to_send != sent_dx || dy_to_send != sent_dy || turn_to_send != sent_turn) {
      packet.appendShort(dx_to_send);
      packet.appendShort(dy_to_send);
      packet.appendShort(turn_to_send);
      send(packet);
      sent_dx = dx_to_send;
      sent_dy = dy_to_send;
      sent_turn = turn_to_send;
    }
  }

  void Holobot::move_toward(float speed, float direction) {
    float rad_dir = M_PI * direction / 180.0;
    control(cos(M_PI/3 + rad_dir)*speed, sin(M_PI/3 + rad_dir)*speed, sent_turn);
  }

  void Holobot::turn(float rot_speed) {
    control(sent_dx, sent_dy, rot_speed);
  }

  void Holobot::stop_all() {
    control(0, 0, 0);
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

  float Holobot::get_wheel_speeds(int id) {
    return wheel_speeds[id];
  }

  void Holobot::print_state() {
    printf("-------------------------------------------------------------------------------\n");
    printf("- time : %0.3fs\n", current_time);
    printf("- wheel speeds(deg/s)    : %4.1f %4.1f %4.1f\n", wheel_speeds[0], wheel_speeds[1], wheel_speeds[2]);
    printf("- wheel speed tgts(deg/s): %4.1f %4.1f %4.1f\n", wheel_speed_tgts[0], wheel_speed_tgts[1], wheel_speed_tgts[2]);
    printf("- opticals (%%):");
    for (int i=0; i<OPTICS_NB; i++) printf("%3.2f ", 100*optics[i]);
    printf("\n");
    printf("- distances (cm): %4.1f %4.1f %4.1f\n", distances[0], distances[1], distances[2]);
    printf("- gyro yaw (deg): %4.0f\n", gyro_yaw);
    printf("- accelerometer: X:%4.0f Y:%4.0f Z:%4.0f\n", acc_x, acc_y, acc_z); 
  }

  void Holobot::debug_state(uint8_t on_or_off) {
    output_state = (bool) on_or_off;
  }
}


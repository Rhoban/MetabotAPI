#include "Holobot.h"
#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace Metabot {

Holobot::Holobot(std::string port, int baud) : Robot(port, baud) {
  output_state = false;

  if (verbose > 0) {
    printf("- monitoring\n");
  }
  updates = 0;
  waitUpdate();
  sent_dx = 0;
  sent_dy = 0;
  sent_turn = 0;
  yaw0 = 0;

  // Optical raw
  Packet packet = command(9);
  packet.appendByte(1);
  send(packet);
}

Holobot::~Holobot() {
  control(0, 0, 0);
  usleep(500000);
}

void Holobot::receive(Packet &packet) {
  if (packet.type == METABOT_MONITOR) {

    uint8_t metabot_version = packet.readByte();

    current_time = ((float)packet.readInt()) / 1000;

    distance = packet.readSmallFloat();

    for (int i = 0; i < OPTICS_NB; i++)
      optics[i] = ((float)packet.readByte()) / 255;

    for (int i = 0; i < 3; i++)
      wheel_speeds[i] = packet.readSmallFloat();

    yaw = packet.readSmallFloat();
    gyro_yaw = packet.readSmallFloat();
    pitch = packet.readSmallFloat();
    roll = packet.readSmallFloat();

    odometry_x = packet.readShort() / 1000.;
    odometry_y = packet.readShort() / 1000.;
    odometry_yaw = packet.readSmallFloat();

    battery1 = packet.readByte() / 40.;
    battery2 = packet.readByte() / 40.;

    if (output_state) {
      print_state();
    }

    updates += 1;
    mutex.unlock();
  }
}

void Holobot::waitUpdate() { 
  int initial_updates = updates;
  
  while (updates == initial_updates) {
    rhock_mode();
    monitor(5);
    usleep(100000);
  }
}

float Holobot::get_dist() { return distance; }

float Holobot::get_opt(int i) {
  if (i < 0 || i >= OPTICS_NB)
    return 0.0;
  return optics[i];
}

std::vector<float> Holobot::get_opts() {
  std::vector<float> opts;
  for (int k = 0; k < OPTICS_NB; k++) {
    opts.push_back(get_opt(k));
  }
  return opts;
}

void Holobot::reset_yaw() { yaw0 = gyro_yaw; }

float Holobot::get_yaw() {
  float yaw = gyro_yaw - yaw0;
  while (yaw < -180.0)
    yaw += 360;
  while (yaw > 180.0)
    yaw -= 360;
  return yaw;
}

float Holobot::get_time() { return current_time; }

Packet Holobot::command(uint8_t instruction) {
  return Packet(HOLOBOT_COMMAND).appendByte(instruction);
}

void Holobot::set_board_led(uint8_t state) {
  Packet p = command(0);
  p.appendByte(state);
  send(p);
}

void Holobot::control(float dx, float dy, float turn) {
  // TODO: attention aux limites (faire remonter un warning en cas de
  // dépassement)
  Packet packet = command(2);
  short dx_to_send = (short)dx;
  short dy_to_send = (short)dy;
  short turn_to_send = (short)turn;
  if (dx_to_send != sent_dx || dy_to_send != sent_dy ||
      turn_to_send != sent_turn) {
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
  control(cos(M_PI / 3 + rad_dir) * speed, sin(M_PI / 3 + rad_dir) * speed,
          sent_turn);
}

void Holobot::turn(float rot_speed) { control(sent_dx, sent_dy, rot_speed); }

float Holobot::get_battery() { return battery1 + battery2; }

void Holobot::stop_all() { control(0, 0, 0); }

void Holobot::calibrate_opticals(bool black) {
  Packet packet = command(5);
  packet.appendByte(black ? 1 : 0);
  send(packet);
}

void Holobot::beep(short freq, short duration) {
  // TODO: attention aux limites
  Packet packet = command(3);
  packet.appendShort(freq);
  packet.appendShort(duration);
  send(packet);
}

void Holobot::play(short id) {
  // TODO: attention aux limites
  Packet packet = command(4);
  packet.appendShort(id);
  send(packet);
}

void Holobot::calibrate_magneto() {
  Packet packet = command(6);
  send(packet);
}

float Holobot::get_wheel_speeds(int id) { return wheel_speeds[id]; }

void Holobot::print_state() {
  printf("---------------------------------------------------------------------"
         "----------\n");
  printf("- time : %0.3fs\n", current_time);
  printf("- wheel speeds(deg/s): %4.1f %4.1f %4.1f\n", wheel_speeds[0],
         wheel_speeds[1], wheel_speeds[2]);
  printf("- opticals (%%):");

  for (int i = 0; i < OPTICS_NB; i++)
    printf("%3.2f ", 100 * optics[i]);

  printf("\n");
  printf("- distance (cm): %4.1f\n", distance);
  printf("- gyro yaw (deg): %4.1f\n", gyro_yaw);
  printf("- pitch (deg): %4.1f\n", pitch);
  printf("- roll (deg): %4.1f\n", roll);
  printf("- odometry, x=%.3f, y=%.3f, yaw=%.2f\n", odometry_x, odometry_y,
         odometry_yaw);
}

void Holobot::debug_state(uint8_t on_or_off) { output_state = (bool)on_or_off; }

void Holobot::set_leds(uint8_t red, uint8_t green, uint8_t blue) {
  Packet packet = command(7);
  packet.appendByte(red);
  packet.appendByte(green);
  packet.appendByte(blue);
  send(packet);
}

void Holobot::leds_breath() {
  Packet packet = command(8);
  send(packet);
}
} // namespace Metabot

#include <wheels.h>
#include <Arduino.h>

#define DIR1 2          // direction of engine 1 spin
#define SPD1 3          // speed of engine 1 spin
#define DIR2 4          // direction of engine 2 spin
#define SPD2 5          // speed of engine 2 spin

//spin directions
const bool FORWARD = false;
const bool BACKWARD = true;

//speeds
const int MOVE = 100;
const int STOP = 0;

static void turn(bool dir1, bool dir2, int speed);

void Wheels_setup(void) {
  pinMode(DIR1, OUTPUT);
  pinMode(SPD1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(SPD2, OUTPUT);
}

void Wheels_forward(void) {
  turn(FORWARD, BACKWARD, MOVE);
}

void Wheels_backward(void) {
  turn(BACKWARD, FORWARD, MOVE);
}

void Wheels_stop(void) {
  turn(FORWARD, FORWARD, STOP);
  delay(300);
}

void Wheels_right(void) {
  turn(FORWARD, FORWARD, MOVE);
}

void Wheels_left(void) {
  turn(BACKWARD, BACKWARD, MOVE);
}

static void turn(bool dir1, bool dir2, int speed) {
  digitalWrite(DIR1, dir1);
  digitalWrite(DIR2, dir2); //!right wheel is installed in inverse position
  analogWrite(SPD1, speed);
  analogWrite(SPD2, speed);
}

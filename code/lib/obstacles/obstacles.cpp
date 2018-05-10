#include <obstacles.h>
#include <wheels.h>
#include <Arduino.h>
#include <stdbool.h>

#define OINP 8
#define OOUT 9
#define CRITICAL_DIST 10

static double getDist(void);
static void defaultPos(void);
static void lookLeft(void);
static void lookRight(void);
static bool checkDist(void);
static void turn90(void (*dir)(void));
static void proceed(void (*dir)(void));

void Obstacles_setup(void) {
  pinMode(OINP, INPUT);
  pinMode(OOUT, OUTPUT);
}

bool Obstacles_detect(void) {
  if(getDist() <= CRITICAL_DIST) {
    return true;
  }
  return false;
}

void Obstacles_avoid(void) {
  Wheels_stop();
  bool dir = checkDist();
  if(dir) {
    proceed(Wheels_right);
  } else {
    proceed(Wheels_left);
  }
  if(Obstacles_detect()) {
    Obstacles_avoid();
  }
}

static bool checkDist(void) {
  lookRight();
  double distRight = getDist();
  lookLeft(); //getting to initial position

  lookLeft();
  double distLeft = getDist();
  lookRight(); //getting to initial position

  if(distLeft > distRight) {
    turn90(Wheels_left);
    return true;
  }
  turn90(Wheels_right);
  return false;
}

static void lookRight(void) {
  //32000 is a const determined experimentally to make car turn right ~ 60 deg
  for(int i = 0; i < 33000; i++) {
    Wheels_right();
  }
  Wheels_stop();
}

static void lookLeft(void) {
  //25000 is a const determined experimentally to make car turn left ~ 60 deg
  for(int i = 0; i < 25000; i++) {
    Wheels_left();
  }
  Wheels_stop();
}

static void turn90(void (*dir)(void)) {
  for(int i = 0; i < 30000; i++) {
    dir();
  }
  Wheels_stop();
}

static double getDist(void) {
  digitalWrite(OOUT, LOW);
  digitalWrite(OOUT, HIGH);
  delayMicroseconds(10); //emmiting soundwave for 10 microseconds
  digitalWrite(OOUT, LOW);

  double dur = pulseIn(OINP, HIGH); //duration of travel in microseconds
  double dist = dur / 29 / 2; //29 microseconds per cm
  return dist;
}

static void proceed(void (*dir)(void)) {
  //20000 is a const determined experimentally to make car move forward ~ 10cm
  for(int i = 0; i < 20000; i++) {
    // if(Obstacles_detect()) {
    //   Obstacles_avoid();
    //   break;
    // }
    Wheels_forward();
  }
  Wheels_stop();
  turn90(dir);
}

#include <wheels.h>
#include <fire.h>
#include <water.h>
#include <obstacles.h>
#include <Arduino.h>

void setup() {
  Fire_setup();
  Wheels_setup();
  Obstacles_setup();
  Serial.begin(9600);
}

void loop() {
  if(Fire_detect()) {
    Wheels_stop();
    while(!Obstacles_detect() && !Fire_isHot()) {
      Wheels_forward();
      //if(!Fire_detect()) break;
    }
    Wheels_stop();
    if(Obstacles_detect()) {
      Obstacles_avoid();
    } else if(Fire_isHot()) {
      Water_activate();
    }
  }
  Wheels_left();
}

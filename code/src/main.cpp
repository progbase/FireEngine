#include <wheels.h>
#include <fire.h>
#include <water.h>
#include <Arduino.h>

void setup() {
  Fire_setup();
  Wheels_setup();
}

void loop() {
  if(Fire_detect()) {
    Wheels_stop();
    while(Fire_detect() && !Fire_isHot()) {
      Wheels_forward();
    }
    Wheels_stop();
    if(Fire_detect()) Water_activate();
  }
  Wheels_right();
}

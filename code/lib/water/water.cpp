#include <water.h>
#include <fire.h>
#include <Arduino.h>

#define WPM 7

//@todo
//make circuit for pump

void Water_setup(void) {
  pinMode(WPM, OUTPUT);
}

void Water_activate(void) {
  while(Fire_detect()) {
    digitalWrite(WPM, HIGH);
  }
}

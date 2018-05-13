#include <water.h>
#include <fire.h>
#include <Arduino.h>

#define WPM 13

void Water_setup(void) {
  pinMode(WPM, OUTPUT);
}

void Water_activate(void) {
  while(Fire_detect()) {
    //1000000 - experimentally determined value
    for(long i = 0; i < 1000000; i++) {
      digitalWrite(WPM, HIGH);
    }
  }
  digitalWrite(WPM, LOW);
}

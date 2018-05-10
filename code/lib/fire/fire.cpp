#include <fire.h>
#include <stdbool.h>
#include <Arduino.h>

#define FSR_DIGITAL 6
#define FSR_ANALOG A0
//max value given by sensor when the fire source is too close
#define CRITICAL_VAL 25

static void wait(void);

void Fire_setup(void) {
  pinMode(FSR_DIGITAL, INPUT);
  pinMode(FSR_ANALOG, INPUT);
}

bool Fire_detect(void) {
  if(digitalRead(FSR_DIGITAL) == 1) {
    wait();
    return true;
  }
  return false;
}

bool Fire_isHot(void) {
  if(analogRead(FSR_ANALOG) <= CRITICAL_VAL) {
    return true;
  }
  return false;
}

static void wait(void) {
  delay(300);
}


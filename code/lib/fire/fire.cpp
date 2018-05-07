#include <fire.h>
#include <stdbool.h>
#include <Arduino.h>

#define FSR 6

static void wait(void);

void Fire_setup(void) {
  pinMode(FSR, INPUT);
}

bool Fire_detect(void) {
  if (digitalRead(FSR) == 0) {
    wait();
    return true;
  }
  return false;
}

bool Fire_isHot(void) {
  return false;
}

static void wait(void) {
  delay(300);
}

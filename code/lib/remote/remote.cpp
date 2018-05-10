#include <remote.h>
#include <wheels.h>
#include <IRremote.h>
#include <stdbool.h>

#define INP 13

enum Codes {ACT_CODE1, ACT_CODE2,
            RIGHT_CODE, LEFT_CODE,
            FORW_CODE, BACK_CODE};

IRrecv receiver(INP);
decode_results results;

static void turnLeft(void);
static void turnRight(void);
static void moveForward(void);
static void moveBackward(void);

void Remote_setup(void) {
  receiver.enableIRIn();
}

long Remote_get(void) {
  if(receiver.decode(&results)) {
    receiver.resume();
    return results.value;
  }
  return 0;
}

//activates/diactivates remote control
bool Remote_activate(void) {
  long code = Remote_get();
  if(code == ACT_CODE1 || code == ACT_CODE2) {
    return true;
  }
  return false;
}

void Remote_control(void) {
  if(Remote_activate()) {
    Wheels_stop();
    //until we deactivate RC it works
    while(!Remote_activate()) {
      long code = Remote_get();
      if (code == RIGHT_CODE) {
        turnRight();
      } else if(code == LEFT_CODE){
        turnLeft();
      } else if(code == FORW_CODE) {
        moveForward();
      } else if(code == BACK_CODE) {
        moveBackward();
      }
    }
  }
}

static void turnLeft(void) {
  long code = Remote_get();
  while(code == LEFT_CODE) {
    Wheels_left();
    code = Remote_get();
  }
  Wheels_stop();
}

static void turnRight(void) {
  long code = Remote_get();
  while(code == RIGHT_CODE) {
    Wheels_right();
    code = Remote_get();
  }
  Wheels_stop();
}

static void moveForward(void) {
  long code = Remote_get();
  while(code == FORW_CODE) {
    Wheels_forward();
    code = Remote_get();
  }
  Wheels_stop();
}

static void moveBacward(void) {
  long code = Remote_get();
  while(code == BACK_CODE) {
    Wheels_backward();
    code = Remote_get();
  }
  Wheels_stop();
}

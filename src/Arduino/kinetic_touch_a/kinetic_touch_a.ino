#include <MPR121.h>
#include <Wire.h>
#include "touchboard.h"

#define TouchBoard_baudRate 57600
#define TouchBoard_touchThreshold 40
#define TouchBoard_releaseThreshold 20

uint8_t state[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  initTouchBoard();
}

void loop() {
  updateTouchBoardWithId(8, state);
  delay(20);
}

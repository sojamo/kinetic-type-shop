#ifndef TouchBoard_h
#define TouchBoard_h


void initTouchBoard() {

#ifndef TouchBoard_baudRate
#define TouchBoard_baudRate 57600
#endif

  Serial.begin(TouchBoard_baudRate);
  while(!Serial);
  
  // 0x5C is the MPR121 I2C address on the Bare Touch Board
  if (!MPR121.begin(0x5C)) {
    Serial.println("error setting up MPR121");
    switch (MPR121.getError()) {
      case NO_ERROR:
        Serial.println("no error");
        break;
      case ADDRESS_UNKNOWN:
        Serial.println("incorrect address");
        break;
      case READBACK_FAIL:
        Serial.println("readback failure");
        break;
      case OVERCURRENT_FLAG:
        Serial.println("overcurrent on REXT pin");
        break;
      case OUT_OF_RANGE:
        Serial.println("electrode out of range");
        break;
      case NOT_INITED:
        Serial.println("not initialised");
        break;
      default:
        Serial.println("unknown error");
        break;
    }
    while (1);
  }

  // pin 4 is the MPR121 interrupt on the Bare Touch Board
  MPR121.setInterruptPin(4);

#ifndef TouchBoard_touchThreshold
#define TouchBoard_touchThreshold 40
#endif

  MPR121.setTouchThreshold(TouchBoard_touchThreshold);     // this is the threshold at which the board senses a touch
  // higher values are less sensitive, lower values are more sensitive
  // for proximity operation, you could try a value of 6

#ifndef TouchBoard_releaseThreshold
#define TouchBoard_releaseThreshold 20
#endif

  MPR121.setReleaseThreshold(TouchBoard_releaseThreshold);   // this is the threshold at which the board senses a release
  // higher values are less sensitive, lower values are more sensitive
  // for proximity operation, you could try a value of 3
  // this must ALWAYS be lower than the touch threshold

  // initial data update
  MPR121.updateTouchData();
}


void updateTouchBoardWithId(int theId, uint8_t *theState) {
  if (MPR121.touchStatusChanged()) {
    MPR121.updateTouchData();
    for (int i = 0; i < 12; i++) {
      if (MPR121.isNewTouch(i)) {
        theState[i] = 1;
      } else if (MPR121.isNewRelease(i)) {
        theState[i] = 0;
      }
    }
    String str = "{\"id\":";
    str += theId;
    str += ",\"value\":[";
    str += theState[0];
    for (int i = 1; i < 12; i++) {
      str += ",";
      str += theState[i];
    }
    str += "]}";
    Serial.println(str);
  }
}
#endif


int state[6];
int current[6];

void setup() {
  Serial.begin(57600);
  while(!Serial);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {

  current[0] = digitalRead(2);
  current[1] = digitalRead(3);
  current[2] = digitalRead(4);
  current[3] = digitalRead(5);
  current[4] = analogRead(A0);
  current[5] = analogRead(A1);

  int isChange = 0;
  
  for (uint8_t i = 0; i < 4; i++) {
    if (state[i] != current[i]) {
      isChange = 1;
    }
  }

  if (abs(state[4] - current[4]) > 5 || abs(state[5] - current[5]) > 5) {
    isChange = 1;
  }

  if (isChange == 1) {

    for (uint8_t i = 0; i < 6; i++) state[i] = current[i];

    String str = "{\"id\":7, \"value\":[";
    str += (current[0]);
    str += ",";
    str += (current[1]);
    str += ",";
    str += (current[2]);
    str += ",";
    str += (current[3]);
    str += ",";
    str += mapFloat(current[4],0.,1023.,0.,1.);
    str += ",";
    str += mapFloat(current[5],0.,1023.,0.,1.);
    str += "]}";
    Serial.println(str);
  }
  delay(20);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
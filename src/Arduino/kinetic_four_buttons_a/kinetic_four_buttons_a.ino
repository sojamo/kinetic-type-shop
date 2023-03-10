
int state[4];
int current[4];

void setup() {
  Serial.begin(57600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  
  current[0] = digitalRead(2);
  current[1] = digitalRead(4); 
  current[2] = digitalRead(6);
  current[3] = digitalRead(8);

  int isChange = 0;
  for (uint8_t i = 0; i < 4; i++) {
    if (state[i] != current[i]) {
      isChange = 1;
    }
  }
  if (isChange == 1) {

    for (uint8_t i = 0; i < 4; i++) state[i] = current[i];
    
    String str = "{\"id\":4, \"value\":[";
    str += (state[0]);
    str += ",";
    str += (state[1]);
    str += ",";
    str += (state[2]);
    str += ",";
    str += (state[3]);
    str += "]}";
    Serial.println(str);
  }
  delay(20);
}

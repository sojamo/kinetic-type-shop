
int state[3];
int current[3];

void setup() {
  Serial.begin(57600);
  while(!Serial);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  
  current[0] = digitalRead(5);
  current[1] = digitalRead(6); 
  current[2] = digitalRead(7);

  boolean isChange = false;

  for (uint8_t i = 0; i < 3; i++) {
    if (state[i] != current[i]) {
      isChange = true;
    }
  }
  if (isChange == true) {

    for (uint8_t i = 0; i < 3; i++) state[i] = current[i];
    
    String str = "{\"id\":10, \"value\":[";
    str += (state[0]);
    str += ",";
    str += (state[1]);
    str += ",";
    str += (state[2]);
    str += "]}";
    Serial.println(str);
  }
  delay(20);
}

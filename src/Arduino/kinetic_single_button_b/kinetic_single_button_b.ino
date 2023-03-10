int state = 0;

void setup() {
  Serial.begin(57600);
  while(!Serial);
  pinMode(2, INPUT_PULLUP);
  
}

void loop() {
  if (digitalRead(2) != state) {
    trigger(digitalRead(2));
  }
  delay(20);
}


void trigger(int theValue) {
  state = theValue;
  String str = "{\"id\":1, \"value\":[";
  str += state;
  str += "]}";
  Serial.println(str);
}

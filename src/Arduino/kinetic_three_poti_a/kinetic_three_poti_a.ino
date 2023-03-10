void setup() {
  Serial.begin(57600);
  while(!Serial);
}

void loop() {
  String str = "{\"id\":9, \"value\":[";
  str += mapFloat(1023 - analogRead(A2),0.,1023.,0.,1.);
  str += ",";
  str += mapFloat(1023 - analogRead(A1),0.,1023.,0.,1.);
  str += ",";
  str += mapFloat(analogRead(A0),0.,1023.,0.,1.);
  str += "]}";
  Serial.println(str);
  delay(20);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
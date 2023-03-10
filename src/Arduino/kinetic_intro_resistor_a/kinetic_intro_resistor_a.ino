// from https://github.com/PaulStoffregen/CapacitiveSensor
#include <CapacitiveSensor.h>

// 1M or 10M resistor between pins 4 & 2, pin 2 is sensor pin,
// add a wire and or foil if desired
CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);

long state = 0;

void setup() {
  Serial.begin(57600);
  while(!Serial);
}

void loop() {
  long v0 = cs_4_2.capacitiveSensor(30);
  if (abs(state - v0) > 50) {
    state = v0;
    String str = "{\"id\":11, \"value\":[";
    str += state;
    str += "]}";
    Serial.println(str);
  }
  delay(20);
}
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Accelerometer x,y,z plus roll, pitch
// Andreas Schlegel, 2023
//
// for Teensy 3.2
// Datasheet: https://www.sparkfun.com/datasheets/DevTools/LilyPad/ADXL335.pdf
//
// Directions taken:
// Callibration: https://chionophilous.wordpress.com/2012/08/28/sensorlib-using-calibration/
// Orientation: https://howtomechatronics.com/tutorials/arduino/how-to-track-orientation-with-arduino-and-adxl345-accelerometer/
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int pinX = A0;
const int pinY = A1;
const int pinZ = A2;

double x;
double y;
double z;
float velocity = 0.02;
float roll, pitch, filteredRoll, filteredPitch = 0;
float flatZ = 620; // z-axis value when flat on a table for example.

void setup() {
  Serial.begin(57600);
}


void loop() {
  float zeroG = 512.0;
  float scale = flatZ - zeroG;

  float x = ((analogRead(pinX) - zeroG) / scale);
  float y = ((analogRead(pinY) - zeroG) / scale);
  float z = ((analogRead(pinZ) - zeroG) / scale);

  // Calculate Roll and Pitch
  // The atan() function returns a value in the range -π/2 to π/2 radians.

  roll = atan(y / sqrt(pow(x, 2) + pow(z, 2))) * 180 / PI;
  pitch = atan(-1 * x / sqrt(pow(y, 2) + pow(z, 2))) * 180 / PI;

  // apply Low-pass filter
  filteredRoll = 0.90 * filteredRoll + 0.1 * roll;
  filteredPitch = 0.90 * filteredPitch + 0.1 * pitch;


  float normalizedX = mapFloat(x, -1.1, 1.1, 0, 1);
  float normalizedY = mapFloat(y, -1.1, 1.1, 0, 1);
  float normalizedZ = mapFloat(z, -1.1, 1.1, 0, 1);
  float normalizedRoll = mapFloat(filteredRoll, -90, 90, 0, 1);
  float normalizedPitch = mapFloat(filteredPitch, -90, 90, 0, 1);
  String str = "{\"id\":";
  str += 5;
  str += ", \"value\":[";
  str += String(normalizedX) + "," + String(normalizedY) + "," + String(normalizedZ) + "," + String((normalizedRoll)) + "," + String((normalizedPitch));
  str += "]}";
  Serial.println(str);
  delay(20);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

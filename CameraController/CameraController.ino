#include <Servo.h>

Servo pitch, yaw;
int pos = 0;

void setup() {
  Serial.begin(9600);
  pitch.attach(10);
  yaw.attach(9);
}

void loop() {
  for (pos = 0; pos <= 180; ++pos) {
    pitch.write(pos);
    delay(15);
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    pitch.write(pos);
    delay(15);
  }
}


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *left_mtr = AFMS.getMotor(1), *right_mtr = AFMS.getMotor(2);
Servo pitch, yaw;
int spd = 0;

void setup() {
  AFMS.begin();

  left_mtr->run(RELEASE);
  right_mtr->run(RELEASE);
  pitch.attach(10);
  yaw.attach(9);
}

void loop() {
  left_mtr->run(FORWARD);
  right_mtr->run(FORWARD);

#define SET_SPEEDS(x) do { \
  left_mtr->setSpeed(x);   \
  right_mtr->setSpeed(x);  \
  pitch.write(x);          \
  delay(10);               \
} while (0)

  for (spd = 0; spd < 180; ++spd) SET_SPEEDS(spd);
  for (spd = 180; spd != 0; --spd) SET_SPEEDS(spd);

  left_mtr->run(BACKWARD);
  right_mtr->run(BACKWARD);

  for (spd = 0; spd < 180; ++spd) SET_SPEEDS(spd);
  for (spd = 180; spd != 0; --spd) SET_SPEEDS(spd);

#undef SET_SPEEDS

  left_mtr->run(RELEASE);
  right_mtr->run(RELEASE);
  delay(1000);
}

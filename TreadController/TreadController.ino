#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *left_mtr = AFMS.getMotor(1);
Adafruit_DCMotor *right_mtr = AFMS.getMotor(2);
int spd = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  left_mtr->setSpeed(150);
  left_mtr->run(FORWARD);
  left_mtr->run(RELEASE);

  right_mtr->setSpeed(150);
  right_mtr->run(FORWARD);
  right_mtr->run(RELEASE);
}

void loop() {
  left_mtr->run(FORWARD);
  right_mtr->run(FORWARD);

#define SET_SPEEDS(x) do { \
  left_mtr->setSpeed(x);   \
  right_mtr->setSpeed(x);  \
  delay(10);               \
} while (0)

  for (spd = 0; spd < 255; ++spd) SET_SPEEDS(spd);
  for (spd = 255; spd != 0; --spd) SET_SPEEDS(spd);

  left_mtr->run(BACKWARD);
  right_mtr->run(BACKWARD);

  for (spd = 0; spd < 255; ++spd) SET_SPEEDS(spd);
  for (spd = 255; spd != 0; --spd) SET_SPEEDS(spd);

  left_mtr->run(RELEASE);
  right_mtr->run(RELEASE);
  delay(1000);
}

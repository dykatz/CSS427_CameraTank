#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *left_front_mtr = AFMS.getMotor(2);
Adafruit_DCMotor *right_front_mtr = AFMS.getMotor(1);
Adafruit_DCMotor *left_back_mtr = AFMS.getMotor(3);
Adafruit_DCMotor *right_back_mtr = AFMS.getMotor(4);
int spd = 0;

#define set_left_speed(s) do { \
  left_front_mtr->setSpeed(s); \
  left_back_mtr->setSpeed(s);  \
} while (0)

#define set_right_speed(s) do { \
  right_front_mtr->setSpeed(s); \
  right_back_mtr->setSpeed(s);  \
} while (0)

#define set_left_run(r) do { \
  left_front_mtr->run(r);    \
  left_back_mtr->run(r);     \
} while (0)

#define set_right_run(r) do { \
  right_front_mtr->run(r);    \
  right_back_mtr->run(r);     \
} while (0)

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  set_left_run(RELEASE);
  set_right_run(RELEASE);
}

void loop() {
  set_left_run(FORWARD);
  set_right_run(FORWARD);

#define SET_SPEEDS(x) do { \
  set_left_speed(x);       \
  set_right_speed(x);      \
  delay(10);               \
} while (0)

  for (spd = 0; spd < 255; ++spd) SET_SPEEDS(spd);
  for (spd = 255; spd != 0; --spd) SET_SPEEDS(spd);

  set_left_run(BACKWARD);
  set_right_run(BACKWARD);

  for (spd = 0; spd < 255; ++spd) SET_SPEEDS(spd);
  for (spd = 255; spd != 0; --spd) SET_SPEEDS(spd);

#undef SET_SPEEDS

  set_left_run(RELEASE);
  set_right_run(RELEASE);
  delay(1000);
}

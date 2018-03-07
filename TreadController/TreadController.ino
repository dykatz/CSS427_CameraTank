#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *left_mtr = AFMS.getMotor(1), *right_mtr = AFMS.getMotor(2);
//Servo pitch, yaw;
int spd = 0;
int ySpeed = 0;
int xSpeed = 0;
int rMotor = 0;
int lMotor = 0;
int countWithoutInput;

void setup() {
  AFMS.begin();
  countWithoutInput = 0;

  left_mtr->run(RELEASE);
  right_mtr->run(RELEASE);
  //pitch.attach(10);
  //yaw.attach(9);

  Serial.begin(9600);
  Serial2.begin(9600);

  ySpeed = 0;
  xSpeed = 0;
  rMotor = 0;
  lMotor = 0;
}

void loop() {
  //left_mtr->run(FORWARD);
  //right_mtr->run(FORWARD);

#define SET_SPEEDS(x,y) do { \
  left_mtr->setSpeed(x);   \
  right_mtr->setSpeed(y);  \
} while (0)

  if(Serial2.available() > 1)
  {
    xSpeed = Serial2.read() - 128;
    ySpeed = 128 - Serial2.read();
    countWithoutInput = 0;
  }
  else
  {
    if(countWithoutInput++ > 20)
    {
      xSpeed = 0;
      ySpeed = 0;
    }
  }
  Serial.print(xSpeed, DEC);
  Serial.write(" ");
  Serial.print(ySpeed, DEC);
  Serial.write("\n");

  lMotor = ySpeed + xSpeed;
  rMotor = ySpeed - xSpeed;

  if(lMotor > 0)
  {
    left_mtr->run(FORWARD);
  }
  else
  {
    left_mtr->run(BACKWARD);
  }
  
  if(rMotor > 0)
  {
    right_mtr->run(FORWARD);
  }
  else
  {
    right_mtr->run(BACKWARD);
  }
  
  SET_SPEEDS( (lMotor > 0 ? lMotor : -lMotor),
              (rMotor > 0 ? rMotor : -rMotor));
  delay(5);

  /*
  for (spd = 0; spd < 180; ++spd) SET_SPEEDS(spd);
  for (spd = 180; spd != 0; --spd) SET_SPEEDS(spd);

  left_mtr->run(BACKWARD);
  right_mtr->run(BACKWARD);

  for (spd = 0; spd < 180; ++spd) SET_SPEEDS(spd);
  for (spd = 180; spd != 0; --spd) SET_SPEEDS(spd);
  */

#undef SET_SPEEDS

  //left_mtr->run(RELEASE);
  //right_mtr->run(RELEASE);
  //delay(1000);
}

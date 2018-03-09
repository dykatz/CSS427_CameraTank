
#include <Wire.h>
#define IN1  8   //K1、K2 motor direction
#define IN2  9     //K1、K2 motor direction
#define IN3  10    //K3、K4 motor direction
#define IN4  12   //K3、K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed ENB
#define LED1 2  //lefe led connect to D2
#define LED2 3  //right led connect to D3

int spd = 0;
int ySpeed = 0;
int xSpeed = 0;
int rMotor = 0;
int lMotor = 0;
int countWithoutInput;

void setup() {
  countWithoutInput = 0;

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
    /******L298N******/
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);

  ySpeed = 0;
  xSpeed = 0;
  rMotor = 0;
  lMotor = 0;
}

void loop() {
  if(Serial.available() > 1)
  {
    xSpeed = Serial.read();
    ySpeed = Serial.read();
    countWithoutInput = 0;
  }
  else
  {
    if(countWithoutInput++ > 2000)
    {
      xSpeed = 128;
      ySpeed = 128;
      go_stop();
      delay(50);
      countWithoutInput = 2001;
    }
  }
  if(ySpeed > 128)
  {
    if(xSpeed < 64)
    {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENA, ySpeed - xSpeed); 
      analogWrite(ENB, ySpeed - xSpeed);
    }
    else if(xSpeed >= 192)
    {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(ENA, (ySpeed + xSpeed - 128) % 256); 
      analogWrite(ENB, (ySpeed + xSpeed - 128) % 256);
    }
    else
    {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENA, ySpeed); 
      analogWrite(ENB, ySpeed);
    }
  }
  else if(ySpeed < 128)
  {
    if(xSpeed < 64)
    {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(ENA, 255 - ySpeed - xSpeed); 
      analogWrite(ENB, 255 - ySpeed - xSpeed);
    }
    else if(xSpeed >= 192)
    {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      analogWrite(ENA, (127 + ySpeed + xSpeed) % 256); 
      analogWrite(ENB, (127 + ySpeed + xSpeed) % 256);
    }
    else
    {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW); 
      analogWrite(ENA, 255 - ySpeed); 
      analogWrite(ENB, 255 - ySpeed);
    }
  }
  else if(xSpeed < 192 && xSpeed > 64)
  {
    go_stop();
  }
  //delay(5);
}

/*robot go ahead*/
void go_ahead()
{
  //set motor spped
  analogWrite(ENA,255); 
  analogWrite(ENB,255);
  //motor go ahead
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
}
/*robot go back*/
void go_back()
{ 
  //set motor spped
  analogWrite(ENA,255); 
  analogWrite(ENB,255);
  //motor go back
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
}
/*robot stop*/
void go_stop()
{
  //change the speed to 0 to stop the motor
  analogWrite(ENA,0); 
  analogWrite(ENB,0);
}


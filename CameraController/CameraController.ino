#include <Servo.h>

Servo pitch, yaw;
int pos = 0;
int pitchPos;
int yawPos;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pitch.attach(10);
  yaw.attach(9);
  pitchPos = 128;
  yawPos = 128;
}

void loop()
{
  if(Serial1.available() > 1)
  {
    if(true)
    {
       pitchPos -= (Serial1.read() - 128)/2;
       yawPos   += (Serial1.read() - 128)/2;
    }
    else
    {
       yawPos   += (Serial1.read() - 128)/2;
       pitchPos -= (Serial1.read() - 128)/2;
    }
   

    if(pitchPos < 0)   pitchPos = 0;
    if(pitchPos > 255) pitchPos = 255;
    if(yawPos < 0)     yawPos = 0;
    if(yawPos > 255)   yawPos = 255;
    
    pitch.write(pitchPos);
    yaw.write(yawPos);

    Serial.write("P ");
    Serial.print(pitchPos, DEC); 
    Serial.write(" Y ");
    Serial.print(yawPos, DEC); 
    Serial.write("\n");
    delay(5);
  }
}

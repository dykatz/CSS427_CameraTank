#include <RH_ASK.h>
#include <SPI.h>

//#define TRANSMITTER
#define RECEIVER

#ifdef TRANSMITTER
#define SRL Serial1
#define PC Serial
#endif

#ifdef RECEIVER
#define SRL Serial1
#define PC Serial
#endif

#define LED_ON  100
#define LED_OFF 35
#define WAIT_TIME 5
#define MSG_SIZE 8

#define ADDRESS 5

bool button;
RH_ASK driver;

/*
 *  UP and LEFT are small numbers (2-ish)
 *  DOWN and RIGHT are big numbers (1000-ish)
 *  the center is about 500
 */

void setup()
{
  // put your setup code here, to run once:
   pinMode(2, OUTPUT);
   pinMode(13, OUTPUT);
   pinMode(3, INPUT);
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(A2, INPUT);
   pinMode(A3, INPUT);
   SRL.begin(1200);
   PC.begin(1200);

   button = false;
   digitalWrite(2, LOW);
   Serial3.begin(9600);
   Serial2.begin(9600);

   driver.init();
}

#ifdef TRANSMITTER
void loop()
{
  uint16_t sig = analogRead(A0);
  uint8_t msg[MSG_SIZE];
  msg[0] = (sig >> 8) & 0xFF;
  msg[1] = (sig     ) & 0xFF;
  sig = analogRead(A1);
  msg[2] = (sig >> 8) & 0xFF;
  msg[3] = (sig     ) & 0xFF;
  sig = analogRead(A2);
  msg[4] = (sig >> 8) & 0xFF;
  msg[5] = (sig     ) & 0xFF;
  sig = analogRead(A3);
  msg[6] = (sig >> 8) & 0xFF;
  msg[7] = (sig     ) & 0xFF;
  //bool current = digitalRead(3);
  driver.send((uint8_t*)msg, MSG_SIZE);
  driver.waitPacketSent();
  delay(5);
  /*bool current = digitalRead(3);
  // put your main code here, to run repeatedly:
  if(current != button)
  {
    button = current;
    if(button)
    {
      sendInt(LED_ON);
      digitalWrite(13, HIGH);
    }
    else
    {
      sendInt(LED_OFF);
      digitalWrite(13, LOW);
    }
  }
  delay(50);*/
}
#endif

#ifdef RECEIVER
void loop()
{
  uint8_t buf[MSG_SIZE];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen))
  {
    Serial3.write( ((buf[0] << 8) + buf[1]) /4);
    Serial3.write( ((buf[2] << 8) + buf[3]) /4);
    PC.print( ((buf[0] << 8) + buf[1]) /4, DEC);
    PC.write(" ");
    PC.print( ((buf[2] << 8) + buf[3]) /4, DEC);
    PC.write("\n");

    Serial2.write( ((buf[4] << 8) + buf[5]) /4);
    Serial2.write( ((buf[6] << 8) + buf[7]) /4);
  }
}
#endif

void sendInt(unsigned int num)
{
  SRL.write(num);
  /*digitalWrite(2, HIGH);
  delay(WAIT_TIME);
  for(int i=15; i>=0; i--)
  {
    if(num >> i & 1 == 1)
    {
      digitalWrite(2, HIGH);
    }
    else
    {
      digitalWrite(2, LOW);
    }
    delay(WAIT_TIME);
  }
  digitalWrite(2, LOW);*/
}

unsigned int readInt(bool wait)
{
  if(wait)
  {
    while(SRL.available() <= 0);
  }
  return SRL.read();
}

/*
const byte g_network_sig[3] = {0x8F, 0xAA, ADDRESS};

void sendInt(unsigned int num)
{
  byte checksum = (num/256) ^ (num&0xFF);
  SRL.write(0xF0);  // This gets reciever in sync with transmitter
  SRL.write(g_network_sig, 3);
  SRL.write((byte*)&num, 2);
  SRL.write(checksum); //CHECKSUM_SIZE

  PC.write(0xF0);  // This gets reciever in sync with transmitter
  PC.write(g_network_sig, 3);
  PC.write((byte*)&num, 2);
  PC.write(checksum); //CHECKSUM_SIZE
}

unsigned int readInt(bool wait)
{
  int pos = 0;
  unsigned int retval;
  byte b = 0;
  
  // if we're not blocking on input and there's no serial, just return an error code
  if(!wait && (SRL.available() < PACKET_SIZE))
  {
    return 0xFFFF;
  }

  while(pos < NETWORK_SIG_SIZE)
  {
    while(SRL.available() == 0);
    b = SRL.read();
    PC.write(b);
    if( b == g_network_sig[pos])
    {
      if(pos == NETWORK_SIG_SIZE - 1)
      {
        byte checksum;

        while(SRL.available() < VAL_SIZE + CHECKSUM_SIZE) ;

        retval =   SRL.read();
        retval &= (SRL.read() << 8);
        checksum = SRL.read();

        if(checksum != (retval/256) ^ (retval&0xFF) )
        {
          // checksum failed, start reading again.
          pos = 1;
        }
      }
      pos++;
    }
    else if(b == g_network_sig[0])
    {
      pos = 1;
    }
    else
    {
      pos = 0;
      if(!wait) return 0xFFFF;
    }
  }

  return retval;
}
*/

#include <DRF702x.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A0, 13); // RX, TX

#define EnPin   7
#define SetPin  2

DRF7020Dx DRF(EnPin,SetPin);
void setup() 
{
  mySerial.begin(9600);
  mySerial.println("DRF Started...");
  if(DRF.Setup(DR_IN_9_6,420789,POUT_Max,DR_FSK_19200,No_Parity,"ABS")==DRF_Error)
  {
    mySerial.println("DRF Setup Error!!!");
    while(1);  
  }
}

char str[50];

void loop() 
{
  if(DRF.Check_WireLess(str))
  {
    mySerial.println(str);    
  }
}

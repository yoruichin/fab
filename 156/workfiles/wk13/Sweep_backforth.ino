#include <SoftwareServo.h>

SoftwareServo myServo1;
SoftwareServo myServo2;  

int angle = 0; 
void setup()
{
  myServo1.attach(0);
  myServo2.attach(3);
}

void loop(){
    for(angle = 1; angle < 180; angle++) 
    {
      myServo1.write(angle);
      delay(20);
      myServo2.write(angle);
      delay(10);
      SoftwareServo::refresh(); 
    }
    for(angle = 180; angle > 1; angle--) 
    {
      myServo1.write(angle);
      delay(20);
      myServo2.write(angle);
      delay(10);
      SoftwareServo::refresh(); 
    }


}

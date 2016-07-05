#include <SoftwareSerial.h>

SoftwareSerial mySerial = SoftwareSerial (0,2);

int sensorPin = A3;    
 
int sensorValue = 0;  

void setup() {
  mySerial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  //mySerial.print(sensorValue);
  if (sensorValue < 500)
  {
    mySerial.println(" I sensed warmth.");
  }
  else if (sensorValue == 1023)
  {
    mySerial.println(" Reading error.");
  }
  else if (sensorValue >= 540)
  { 
    mySerial.println(" It's cold.");  
  }
  else 
  {
    mySerial.println(" I feel normal.");
  }
  delay(1000);
}



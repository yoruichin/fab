#include <SoftwareSerial.h>

SoftwareSerial mySerial = SoftwareSerial (0,2);

int sensorPin = A3;    
 
int sensorValue = 0;  

void setup() {
  mySerial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  mySerial.print(sensorValue);
  if (sensorValue < 300)
    mySerial.println(" I sensed bright light.");
  else
    mySerial.println(" Not bright enough for me.");   
  delay(5000);
}



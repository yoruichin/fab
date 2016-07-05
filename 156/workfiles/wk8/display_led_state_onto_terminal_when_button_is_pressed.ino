/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 7, when pressing a pushbutton attached to pin 3.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 25 March 2016
 by Yue Siew Chin

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */
#include <SoftwareSerial.h>
// constants won't change. They're used here to
// set pin numbers:
const int rx=1;
const int tx=0;
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin
int val = 0;
int old_val = 0;
int state = 0;
int flag = 0;

SoftwareSerial mySerial(rx,tx);
// variables will change:

void setup() {
  mySerial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  if(mySerial.available() > 0){
    state = mySerial.read();
    flag=0;
  }
  // read the state of the pushbutton value:
  val = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  // resets written counter to 0
  if ((val == HIGH) && (old_val == LOW)) {
    state = 1 - state;
    flag = 0;
    delay(10);
  }
  old_val = val; 

  if ((state == 1) && (flag == 0)) {
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    mySerial.println("led is on!");
    flag = 1;
  } else if ((state == 0) && (flag == 0)) {
        digitalWrite(ledPin, LOW);
        mySerial.println("led is off!");
        flag = 1;
        }
    else {
      //do nothing
    }
  
  
}

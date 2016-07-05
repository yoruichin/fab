/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 21 March 2016
  by Yue Siew Chin

  Turn on LED when the button is pressed
  and keep it on after it is released
  including simple de-bouncing
  
*/

#include <SoftwareSerial.h>
#define LED 7     // the pin of for the LED
#define BUTTON 3  // the input pin where the pushbutton is connected

int val = 0;      // used to store the state of the input pin
int old_val = 0;  // this variable stores the previous value of "val"
int state = 0;      // 0 = LED off while 1 = LED on



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED, OUTPUT);   // tells Arduino LED is an output
  pinMode(BUTTON, INPUT); // and BUTTON is an input
  
}

// the loop function runs over and over again forever
void loop() {
  val = digitalRead(BUTTON);  // read input value and store it

  // check if the input is HIGH (button pressed)
  // and change the state

  if ((val == HIGH) && (val != old_val)) { // differeniate the exact moment when 
                                           // the button is pressed.
    state = 1 - state;
    delay(10);
    
  }

  old_val = val; // val is now old

  if (state == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

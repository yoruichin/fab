/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 7, when pressing a pushbutton attached to pin 3.


 The circuit:
 * LED attached from pin 7 to ground
 * pushbutton attached to pin 3 from +5V


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 25 March 2016
 by Yue Siew Chin

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  7;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);
  } else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
  }
}
//
//
// hello.stepper.bipolar.44.full.c
//
// bipolar full stepping hello-world
//
// Neil Gershenfeld
// 11/21/12
//
// (c) Massachusetts Institute of Technology 2012
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//
// Documentation
// =============
// Modified by Yue Siew Chin, Fablab Singapore, 2016
//
// This program causes a stepper motor to turn a page at the press of a pushbutton.
// Microcontroller = ATtiny44
// Pushbutton = PB2
// LED = PA7
// Stepper motor pins = PA0, PA1, PA3, PA4 (A2, A1, B2, B1)
// Bipolar stepper motor 14HS13-0804S
// H-bridge PWM Motor Driver Allegro A4950 
// 5V Regulator LM2940



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define toggle(port,pin) (port ^= pin)
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set

#define bridge_port PORTA // H-bridge port
#define bridge_direction DDRA // H-bridge direction
#define A2 (1 << PA0) // H-bridge output pins
#define A1 (1 << PA1) // "
#define B2 (1 << PA3) // "
#define B1 (1 << PA4) // "
#define on_delay() _delay_us(35) // PWM on time
#define off_delay() _delay_us(15) // PWM off time
#define PWM_count 100 // number of PWM cycles
#define step_count 53 // number of steps


#define button_port PORTB
#define button_pins PINB
#define button_direction DDRB
#define button (1 << PB2) // set button input pin

#define led_port PORTA
#define led_direction DDRA
#define led (1 << PA7) // set LED output pin


static uint8_t count;

//
// A+ B+ PWM pulse
//
void pulse_ApBp() {
  clear(bridge_port, A2);
  clear(bridge_port, B2);
  set(bridge_port, A1);
  set(bridge_port, B1);
   for (count = 0; count < PWM_count; ++count) {
      set(bridge_port, A1);
      set(bridge_port, B1);
      on_delay();
      clear(bridge_port, A1);
      clear(bridge_port, B1);
      off_delay();
    }
  }
//
// A+ B- PWM pulse
//
void pulse_ApBm() {
  clear(bridge_port, A2);
  clear(bridge_port, B1);
  set(bridge_port, A1);
  set(bridge_port, B2);
   for (count = 0; count < PWM_count; ++count) {
      set(bridge_port, A1);
      set(bridge_port, B2);
      on_delay();
      clear(bridge_port, A1);
      clear(bridge_port, B2);
      off_delay();
    }
  }
//
// A- B+ PWM pulse
//
void pulse_AmBp() {
  clear(bridge_port, A1);
  clear(bridge_port, B2);
  set(bridge_port, A2);
  set(bridge_port, B1);
   for (count = 0; count < PWM_count; ++count) {
      set(bridge_port, A2);
      set(bridge_port, B1);
      on_delay();
      clear(bridge_port, A2);
      clear(bridge_port, B1);
      off_delay();
    }
  }
//
// A- B- PWM pulse
//
void pulse_AmBm() {
  clear(bridge_port, A1);
  clear(bridge_port, B1);
  set(bridge_port, A2);
  set(bridge_port, B2);
   for (count = 0; count < PWM_count; ++count) {
      set(bridge_port, A2);
      set(bridge_port, B2);
      on_delay();
      clear(bridge_port, A2);
      clear(bridge_port, B2);
      off_delay();
    }
  }
//
// clockwise step
//
void step_cw() {
   pulse_ApBp();
   pulse_AmBp();
   pulse_AmBm();
   pulse_ApBm();
}
//
// counter-clockwise step
//
void step_ccw() {
   pulse_ApBm();
   pulse_AmBm();
   pulse_AmBp();
   pulse_ApBp();
}

uint8_t debounce(void) {                      // check for button bounce
  if (bit_is_clear(button_pins, button)) {     // button is pressed
    _delay_us(1000);                          // debounce timeout in microseconds
    if (bit_is_clear(button_pins, button)) {   // button is still pressed after a short delay
      return (1);       // return true
    }
  }
  return (0);           // otherwise return false
} 

int main(void) {
   //
   // main
   //
   static uint8_t i,j;
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //
   // initialize bridge pins
   //
   clear(bridge_port, A1);
   output(bridge_direction, A1);
   clear(bridge_port, A2);
   output(bridge_direction, A2);
   clear(bridge_port, B1);
   output(bridge_direction, B1);
   clear(bridge_port, B2);
   output(bridge_direction, B2);

   input(button_direction, button);  // clear bit
   // set(button_port, button);         // value = HIGH; enable pull-up on the button
   output(led_direction, led);   // set bit of LED for output
   set(led_port, led);

   //
   // main loop
   //
  while (1) {

    if (bit_is_clear(PINB, PB2)) {
      clear(led_port, led); 
      for (i = 0; i < step_count; ++i) {
//          for (j = 0; j < i; ++j)
          step_cw();
        _delay_ms(10); 

//  stop stepper motor rotation
           clear(bridge_port, A1);
           clear(bridge_port, A2);
           clear(bridge_port, B1);
           clear(bridge_port, B2);

      }         
    }
    else {
      set(led_port, led);   // indicates ready to receive input
   }
  }
}
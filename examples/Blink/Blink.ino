/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  This example does not utilize the encoder.
*/

#include "IwitVolumeKnob.h"

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize hardware
  IwitKnob.begin();
}

// the loop function runs over and over again forever
void loop() {
  IwitKnob.setLed(true);   // turn the LED on
  delay(1000);             // wait for a second
  IwitKnob.setLed(false);  // turn the LED off
  delay(1000);             // wait for a second
}

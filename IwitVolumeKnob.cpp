/*
    Arduino IwitVolumeKnob library
    Copyright (C) 2019  Manuel Reimer <manuel.reimer@gmx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Arduino.h"
#include "IwitVolumeKnob.h"

IwitKnob_ IwitKnob;

// Hook into the constructor of the EncoderStepCounter library to set our pins
IwitKnob_::IwitKnob_():
  EncoderStepCounter(IWIT_ENCODER_PIN1, IWIT_ENCODER_PIN2, HALF_STEP)
{
}

// Interrupt routine for attachInterrupt
void interrupt() {
  IwitKnob.tick();
}

// Handles attaching the two interrupts needed for the encoder
void IwitKnob_::AttachInterrupts() {
  // https://github.com/NicoHood/HoodLoader2/wiki/Arduino-Uno-Mega-16u2-Pinout
  // Pin 14: PD1 INT1
  // Pin 19: PD6 INT6
  //
  // So we are aiming for INT1 and INT6.
  // Up to and including ArduinoCore-avr version 1.8.1 the interrupt numbers
  // are not 1:1 the INTx numbers. Newer versions have 1:1 mapping.
  //
  // Old mapping: INT1 -> interrupt number 3
  //              INT6 -> interrupt number 6
  //
  // Problem is, that digitalPinToInterrupt() for HoodLoader2 always expected
  // the 1:1 mapping. So for now we can't trust digitalPinToInterrupt()...
  //
  // --> INT6 -> 6 is safe in all cases (was never mixed up). Do this first:
  attachInterrupt(6, interrupt, CHANGE);
  //
  // INT1 can be set with either number 1 (new AVR core) or 3 (old AVR core)
  attachInterrupt(1, interrupt, CHANGE); // Try new number first
  if ((EIMSK & (1 << INT1)) == 0) { // If we haven't set INT1 with this
    detachInterrupt(1); // Remove wrong interrupt
    attachInterrupt(3, interrupt, CHANGE); // And use the old number
  }
}

// Forward to EncoderStepCounter.begin() first. Then init our hardware.
void IwitKnob_::begin() {
  pinMode(IWIT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(IWIT_LED_PIN, OUTPUT);
  EncoderStepCounter::begin(); // Has a delay for charging filter caps built in
  AttachInterrupts();
}

// PWM variant of setting the LED
void IwitKnob_::setLed(int aValue) {
  analogWrite(IWIT_LED_PIN, aValue);
}

// Digital variant of setting the LED
void IwitKnob_::setLed(bool aValue) {
  digitalWrite(IWIT_LED_PIN, aValue);
}

// Reads button status
bool IwitKnob_::getButton() const {
  return !digitalRead(IWIT_BUTTON_PIN);
}

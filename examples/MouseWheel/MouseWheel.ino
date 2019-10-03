/*
 This example clones your mouse wheel to the encoder wheel.
 The push button has no functionality in this example.
*/

#include "IwitVolumeKnob.h"
#include "HID-Project.h"

void setup() {
  // Initialize hardware
  IwitKnob.begin();
  Mouse.begin();
}

bool lastsuspended = true;
void loop() {
  // Read values on every loop run
  signed char pos = IwitKnob.getPosition();
  bool suspended = USBDevice.isSuspended();

  // Disable the LED if the PC is shut down
  if (suspended != lastsuspended) {
    lastsuspended = suspended;
    if (suspended)
      IwitKnob.setLed(false);
    else
      IwitKnob.setLed(127); // Enable with 50% brightness
  }

  // Send encoder position as mouse scroll wheel movement
  if (pos != 0) {
    Mouse.move(0, 0, pos);
    IwitKnob.reset();
  }
}

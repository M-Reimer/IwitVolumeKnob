/*
 This example somewhat replicates the original behaviour of the device.
 Turning the knob changes volume. Pressing it mutes sound.
 I decided to not replicate the ugly LED behaviour.
*/

#include "IwitVolumeKnob.h"
#include "HID-Project.h"

void setup() {
  // Initialize hardware
  IwitKnob.begin();
  Consumer.begin();
}

bool lastbtn = false;
bool lastsuspended = true;
void loop() {
  // Read values on every loop run
  signed char pos = IwitKnob.getPosition();
  bool btn = IwitKnob.getButton();
  bool suspended = USBDevice.isSuspended();

  // Disable the LED if the PC is shut down
  if (suspended != lastsuspended) {
    lastsuspended = suspended;
    if (suspended)
      IwitKnob.setLed(false);
    else
      IwitKnob.setLed(127); // Enable with 50% brightness
  }

  // Send volume keys based on position
  if (pos > 0) {
    Consumer.write(MEDIA_VOL_UP);
    IwitKnob.reset();
  }
  else if (pos < 0) {
    Consumer.write(MEDIA_VOL_DOWN);
    IwitKnob.reset();
  }

  // Send mute key based on encoder button
  if (btn != lastbtn) {
    lastbtn = btn;
    if (btn)
      Consumer.press(MEDIA_VOL_MUTE);
    else
      Consumer.release(MEDIA_VOL_MUTE);
  }
}

/* 
 This example can be used to test the encoder on the iWit volume knob 
 device. Open the serial console and press or rotate the encoder.
*/

#include "IwitVolumeKnob.h"

void setup() {
  Serial.begin(9600);
  delay(2000);
  // Initialize hardware
  //IwitKnob.begin(FULL_STEP);
  IwitKnob.begin();
  // Light LED
  IwitKnob.setLed(100);
}

signed char lastpos = 0;
bool lastbtn = false;
void loop() {
  signed char pos = IwitKnob.getPosition();
  bool btn = IwitKnob.getButton();

  if (pos != lastpos) {
    lastpos = pos;
    Serial.println(pos);
  }

  if (btn != lastbtn) {
    lastbtn = btn;
    Serial.println(btn ? "PRESS" : "RELEASE");
  }
}

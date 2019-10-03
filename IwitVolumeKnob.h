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

#pragma once

#include "Arduino.h"
#include "EncoderStepCounter.h"

#define IWIT_ENCODER_PIN1 14
#define IWIT_ENCODER_PIN2 19
#define IWIT_BUTTON_PIN 20
#define IWIT_LED_PIN 7

class IwitKnob_ : public EncoderStepCounter {
public:
  IwitKnob_();
  void setLed(int aValue);
  void setLed(bool aValue);
  bool getButton() const;
  using EncoderStepCounter::begin; // Use the begin(EncoderType) from base class
  void begin() override;
private:
  void AttachInterrupts();
};

extern IwitKnob_ IwitKnob;

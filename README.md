IwitVolumeKnob Arduino Library
==============================

Introduction
------------

The iWit volume knob is a device that can be ordered in many online shops. It is supposed to control your multimedia volume by sending multimedia key presses for "volume up", "volume down" and "mute".

So far I know of two variants of this device that are built based on the exactly same circuit around the exactly same microcontroller. The square ones with the text "USB Volume Cotrol" (note the typo :P ) and the round ones with the text "AIMOS" on it.

![](https://raw.githubusercontent.com/wiki/M-Reimer/IwitVolumeKnob/images/iwit.jpg)

By default this device is not easily reprogrammable and has a microcontroller on board with the markings removed. The boards usually have an exposed ICSP header. Attaching a programmer to this header allows to read the device signature which exposes that the microcontroller is an ATmega32u2

    avrdude: Device signature = 0x1e958a (probably m32u2)

With the HoodLoader2 there is an Arduino compatible boot loader available for this chip, which can replace the original firmware to allow reprogramming this device like any regular Arduino board. Together with the library, maintained in this repository, this allows you to modify the functionality of the nice rotary encoder devices in any way you like.

Burning the bootloader
----------------------

1. Follow the [Software Installation instructions for HoodLoader2](https://github.com/NicoHood/HoodLoader2/wiki/Software-Installation)
2. Open the housing of the device. The square device can be opened by removing two screws. The round device has a glass disc glued to the aluminium case. The glue is not that strong. Just pry it off with your fingernails.
3. Temporarily attach a programmer to the board. I found that it's easiest to do this by separating the programming pins to two 3 pin pinheaders, sticking them into the board holes and pressing them apart from each other by placing a finger between them. You can use the cheap "usbasp" programmer which can be ordered in many online marketplaces for around 5€. It is also possible to use any regular [Arduino as an ISP](https://www.arduino.cc/en/tutorial/arduinoISP).
4. Open the Arduino IDE
5. Select your programmer via "Tools" -> "Programmer"
6. Select the board "HoodLoader2 23u2" via "Tools" -> "Board"
7. Burn the bootloader with "Tools" -> "Burn Bootloader"
8. If you get a success message after burning and the device gets visible in "Tools" -> "Port" in the Arduino IDE, then close the device housing. For the round one double sided sticky tape helps to reattach the round glass disc. You may remove the glue from the aluminium part with a sharp blade, first.

Controlling the device with the IwitVolumeKnob library
------------------------------------------------------

You need the following libraries to run the examples. They all can be found in the Arduino library manager:
- EncoderStepCounter by Manuel Reimer
- IwitVolumeKnob by Manuel Reimer
- HID-Project by NicoHood

After installing the libraries, you can try out some example sketches in "File" -> "Examples" -> "IwitVolumeKnob". The "VolumeKnob" example actually replicates a functionality similar to the original firmware.

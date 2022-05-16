# ESP-Rider_Meccanoid_Two_Motor_L298N_Version
ESP-32 controls a Meccanoid servo and two dc motors with a L298N motor driver.



ESP-Rider with L298N, a 12 volt and USB output from a 3amp power pack is recommended for one inch motors.

Uses an ESP32 Dev kit module to control a small cars direction and speed with a L298N H-bridge.

The code uses PWM and channels.

This will set up a wifi access point on the car which will allow a user to log in and access 192.168.4.1 which is the car's control html page.

Esp32 must be set up in preferences in Arduino IDE. https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

Library required:

meccanoid.h https://github.com/alexfrederiksen/MeccanoidForArduino

Parts required:
ESP32 devkit or similar.
L298N H-bridge.
Meccanoid servo and wiring harness as described here: https://meccontrol.com/help/software/devices/meccanoidservomotor.
USB charging block with two outputs. A 12 volt 3 amp power pack was adequate. https://www.amazon.ca/gp/product/B01M7Z9Z1N
Logic converter.  Suitable mount can be found here https://www.thingiverse.com/thing:5381851/files
Electric motors of your choice.  Motor mounts for the one inch motors available here https://www.thingiverse.com/thing:5361324

This works best on an Android phone. Computer screens are okay. Apple units, shrug.

Can steer either by slider bar or by tapping the left or right buttons.  Sometimes twice. Speed/Direction control buttons must be held.

Html page needs someone with more experience to make it user friendlier.

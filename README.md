# aaWatch

A simplistic device to keep track of time while I am at the gym.


## Schematic
- Currently running on an ESP32.
	- Reference <https://www.wemos.cc/en/latest/_static/files/sch_s2_mini_v1.0.0.pdf>
		- PIN 33 is SDA
		- PIN 35 is SCL
- OLED Screen is SSD1315 (128x64)
	- Using library u8g2 <https://github.com/olikraus/u8g2>
- Three buttons:
	- Button 1: UP (GPIO 37)
	- Button 2: OK (GPIO 38)
	- Button 3: DOWN (GPIO 39)

## Current Features
- Set countdown time with UP and DOWN buttons. OK to confirm and start timer.
- Counts down to zero from a set time. OK to stop and go back to setup.

## Next tasks
- [ ] Feature: Beep when arriving to zero.
- [ ] Feature: Intervals mode (workout/rest).
- [ ] Enhance: Improve button handling (high/low, and hold).

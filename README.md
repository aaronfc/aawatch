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
- Buzzer (passive)
	- PIN 16

## Current Features
- Set countdown time with UP and DOWN buttons. OK to confirm and start timer.
- Counts down to zero from a set time. OK to stop and go back to setup.
- Plays final fantasy victory theme when timer reaches zero.

## Tasks Outline
- [O] Enhance: Improve tune timing, tones and volume.
	- [X] Understand partiture.
	- [X] Update code to follow partiture.
	- [X] Prepare snippet with new approach.
	- [ ] Replace old approach with new approach in code.
- [ ] Enhance: Split code into multiple files.
	- [ ] Extract music playing stuff.
	- [ ] Extract melodies definitions.
	- [ ] Extract button handling.
	- [ ] Extract screen/rendering logic.
	- [ ] Extract separate scenes.
- [ ] Enhance: Improve button handling.
	- [ ] Detect button press by interruption (high/low) transition (not time based).
	- [ ] Detect holding.
- [ ] Feature: Intervals mode (workout/rest).
- [ ] Feature: Add main menu.

## References
- Original emulator project used to iterate over tune: <https://wokwi.com/projects/405205519060590593>
- Improved FFVII emulator project (mine): <https://wokwi.com/projects/405828187237249025>

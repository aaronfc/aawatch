#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <string.h>  // Include the string library for strncpy

/* Constructor */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, -1, 35, 33);

/* Global variables */
long last_millis_tick = 0;
long countdown_setup_time = 10000; // Value setup for countdown.
long countdown_current = 0; // Current countdown counter.
int status = 0; // 0: Setup counter, 1: Countdown
int status_previous = -1; // -1 Not set yet.

/* Pin definitions for buttons */
const int button1Pin = 37;
const int button2Pin = 38;
const int button3Pin = 39;

char last_button_pressed[20] = "none";

/* u8g2.begin() is required and will send the setup/init sequence to the display */
void setup(void) {
  u8g2.begin();

  // Configure buttons as input with pull-down resistors
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

  Serial.begin(9600); // Initialize serial communication for debugging

  last_millis_tick = millis();
}

/*
 * @return bool Whether we have to transition to the next scene or not. 
 */
bool setup_scene(long delta, bool button1, bool button2, bool button3) {
  // Run init if first time processing this scene.
  if ( status_previous != status ) {
    Serial.println("[Setup]]: Init");
    status_previous = status;
  }

  bool result = false;

  // Handle input.
  if ( button1 && button3 ) { // Reset combo!
    countdown_setup_time = 0;
  } else {
    if ( button1 ) { // UP
      countdown_setup_time += 10000;
    } else if ( button2 ) { // OK
      result = true; // Transition to next scene.
    } else if ( button3 ) { // DOWN
      countdown_setup_time -= 1000;
    }
  }

  // Render sreen.
  u8g2.firstPage();
  do {
    char buffer[20];  // Create a buffer to store the formatted string
    sprintf(buffer, "%ld", countdown_setup_time / 1000 );  // Format the string
    u8g2.setFont(u8g2_font_spleen32x64_mn);
    u8g2.drawStr(0, 64, buffer);  // Pass the formatted string to drawStr
  } while (u8g2.nextPage());

  return result;
}

/*
 * @return bool Whether we have to transition to the next scene or not. 
 */
bool countdown_scene(long delta, bool button1, bool button2, bool button3) {
  // Run init if first time processing this scene.
  if ( status_previous != status ) {
    Serial.println("[Countdown]: Init");
    status_previous = status;
    countdown_current = countdown_setup_time;
    return false; // Should we really exit early?
  }

  // Decrease counter.
  countdown_current -= delta;
  if (countdown_current < 0) {
    countdown_current = 0;
  }

  // Handle input.
  if ( button2 ) { // OK
    return true;
  }

  // Render sreen.
  u8g2.firstPage();
  do {
    char buffer[20];  // Create a buffer to store the formatted string
    sprintf(buffer, "%ld", countdown_current / 1000 );  // Format the string
    u8g2.setFont(u8g2_font_spleen32x64_mn);
    u8g2.drawStr(0, 64, buffer);  // Pass the formatted string to drawStr
  } while (u8g2.nextPage());

  return false;
}

/* draw something on the display with the `firstPage()`/`nextPage()` loop*/
void loop(void) {
  /* Handle buttons */
  // Read button states (assuming active low)
  bool button1Pressed = !digitalRead(button1Pin);
  bool button2Pressed = !digitalRead(button2Pin);
  bool button3Pressed = !digitalRead(button3Pin);

  long delta = millis() - last_millis_tick; // Calculate delta.
  last_millis_tick = millis(); // Update tick.

  if ( status == 0 ) { // Setup scene.
    bool is_done = setup_scene( delta, button1Pressed, button2Pressed, button3Pressed );
    if ( is_done ) {
      status = 1; // Next scene.
    }
  } else if( status == 1 ) { // Counting scene.
    bool is_done = countdown_scene( delta, button1Pressed, button2Pressed, button3Pressed );
    if ( is_done ) {
      status = 0; // Previous scene.
    }  
  }
  delay(200);
}
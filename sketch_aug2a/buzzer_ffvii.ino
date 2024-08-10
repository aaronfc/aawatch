#include "pitches.h"

#define SPEAKER_PIN 8

const int TEMPO = 130; // 130 negras per minute
const long MS_PER_UNIT = 60L * 1000L / TEMPO;

const int SEMICORCHEA = MS_PER_UNIT / 4;
const int CORCHEA = MS_PER_UNIT / 2;
const int NEGRA = MS_PER_UNIT * 1;
const int BLANCA = MS_PER_UNIT * 2;
const int BLANCA_PUNT = MS_PER_UNIT * 3;


struct Note {
  int note;
  int duration_ms;
};
const int MELODY_LENGTH = 9;
Note melody[MELODY_LENGTH];

void buzzer() {
  for (int thisNote = 0; thisNote < MELODY_LENGTH; thisNote++) {
    const Note note = melody[thisNote];
    int pauseBetweenNotes = note.duration_ms / 3;
    const int real_duration = note.duration_ms - pauseBetweenNotes;
    Serial.println("Note: " + String(note.note) + " duration: " + String(note.duration_ms));
    Serial.println("Adjusted duration: " + String(real_duration) + " + pause: " + String(pauseBetweenNotes));
    tone(SPEAKER_PIN, note.note, real_duration);
    delay(real_duration); // Wait
    // stop the tone playing:
    noTone(SPEAKER_PIN);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    delay(pauseBetweenNotes);
  }
  delay (3000); // Three seconds pause
}

void setup() {
    Serial.begin(9600);  // Initialize serial communication
    Serial.println(MS_PER_UNIT);
  // Melody (in setup because can't initialise in global scope – wtf?)
  melody[0] = { NOTE_C5, MS_PER_UNIT / 3 };
  melody[1] = { NOTE_C5, MS_PER_UNIT / 3 };
  melody[2] = { NOTE_C5, MS_PER_UNIT / 3 };
  melody[3] = { NOTE_C5, NEGRA };
  melody[4] = { NOTE_GS4, NEGRA };
  melody[5] = { NOTE_AS4, NEGRA };
  melody[6] = { NOTE_C5, MS_PER_UNIT / 3 * 2 };
  melody[7] = { NOTE_AS4, MS_PER_UNIT / 3 * 1 };
  melody[8] = { NOTE_C5, BLANCA_PUNT};
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  buzzer();
}


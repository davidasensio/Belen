#include <Arduino.h>
//#include "songs/silent_night.h"
// #include "songs/joy_to_the_world.h"
// #include "songs/jingle_bells.h"
#include "songs/adeste_fideles.h"

#define LED 27 // 25 or 26 or 27
#define PIEZO 26

int currentNoteIndex = 0;
unsigned long noteStartTime = 0;
bool melodyPlaying = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  updateMelody();  // Non-blocking melody update
  
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  Serial.println("Hola");
  delay(500);
}

void updateMelody() {
  // If melody finished, restart it
  if (currentNoteIndex >= MELODY_LENGTH) {
    currentNoteIndex = 0;
    melodyPlaying = false;
  }

  // Start melody if not playing
  if (!melodyPlaying) {
    melodyPlaying = true;
    noteStartTime = millis();
    tone(PIEZO, melodyNotes[currentNoteIndex]);
    return;
  }

  // Check if current note duration has elapsed
  if (millis() - noteStartTime >= melodyDurations[currentNoteIndex]) {
    noTone(PIEZO);
    currentNoteIndex++;

    // Start next note if available
    if (currentNoteIndex < MELODY_LENGTH) {
      delay(30);  // Small gap between notes (shorter for smoother melody)
      noteStartTime = millis();
      tone(PIEZO, melodyNotes[currentNoteIndex]);
    } else {
      melodyPlaying = false;
    }
  }
}

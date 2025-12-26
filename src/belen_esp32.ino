#include <Arduino.h>
#include "songs/silent_night.h"
#include "songs/joy_to_the_world.h"
#include "songs/jingle_bells.h"
#include "songs/adeste_fideles.h"

#define LED 27 // 25 or 26 or 27
#define PIEZO 26

#define NUM_SONGS 4

// Song data structure
struct Song {
  const int* notes;
  const int* durations;
  int length;
  const char* name;
};

// Array of all available songs
const Song songs[NUM_SONGS] = {
  { silentNightNotes, silentNightDurations, SILENT_NIGHT_LENGTH, "Silent Night" },
  { joyToTheWorldNotes, joyToTheWorldDurations, JOY_TO_THE_WORLD_LENGTH, "Joy to the World" },
  { jingleBellsNotes, jingleBellsDurations, JINGLE_BELLS_LENGTH, "Jingle Bells" },
  { adesteFidelesNotes, adesteFidelesDurations, ADESTE_FIDELES_LENGTH, "Adeste Fideles" }
};

// Current song pointers
const int* melodyNotes;
const int* melodyDurations;
int melodyLength;

int currentNoteIndex = 0;
unsigned long noteStartTime = 0;
bool melodyPlaying = false;

void selectRandomSong() {
  int songIndex = random(NUM_SONGS);
  melodyNotes = songs[songIndex].notes;
  melodyDurations = songs[songIndex].durations;
  melodyLength = songs[songIndex].length;
  Serial.print("Playing: ");
  Serial.println(songs[songIndex].name);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // Seed random with analog noise
  randomSeed(analogRead(0));

  // Select a random song at boot
  selectRandomSong();
}

void loop() {
  updateMelody();

  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  Serial.println("Hola");
  delay(500);
}

void updateMelody() {
  // If melody finished, restart it
  if (currentNoteIndex >= melodyLength) {
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
    if (currentNoteIndex < melodyLength) {
      delay(30);  // Small gap between notes (shorter for smoother melody)
      noteStartTime = millis();
      tone(PIEZO, melodyNotes[currentNoteIndex]);
    } else {
      melodyPlaying = false;
    }
  }
}

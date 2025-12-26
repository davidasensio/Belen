#ifndef JINGLE_BELLS_H
#define JINGLE_BELLS_H

#include "notes.h"

// "Jingle Bells" melody (chorus)
const int jingleBellsNotes[] = {
  // "Jingle bells, jingle bells"
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  // "Jingle all the way"
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4,
  // "Oh what fun it"
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
  // "is to ride in a"
  NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  // "one horse open sleigh"
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4
};

const int jingleBellsDurations[] = {
  // "Jingle bells, jingle bells"
  QUARTER, QUARTER, HALF,
  QUARTER, QUARTER, HALF,
  // "Jingle all the way"
  QUARTER, QUARTER, QUARTER, QUARTER, WHOLE,
  // "Oh what fun it"
  QUARTER, QUARTER, QUARTER, QUARTER,
  // "is to ride in a"
  QUARTER, QUARTER, QUARTER, EIGHTH, EIGHTH,
  // "one horse open sleigh"
  QUARTER, QUARTER, QUARTER, QUARTER, HALF, HALF
};

#define JINGLE_BELLS_LENGTH 26

#endif

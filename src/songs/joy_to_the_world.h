#ifndef JOY_TO_THE_WORLD_H
#define JOY_TO_THE_WORLD_H

#include "notes.h"

// "Joy to the World" melody
const int joyToTheWorldNotes[] = {
  // "Joy to the world"
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  // "the Lord is come"
  NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4,
  // "Let earth re-"
  NOTE_G4, NOTE_A4,
  // "-ceive her"
  NOTE_A4, NOTE_B4,
  // "King"
  NOTE_B4, NOTE_C5,
  // "Let every heart"
  NOTE_C5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  // "prepare Him room"
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  // "And heaven and nature sing"
  NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4,
  // "And heaven and nature sing"
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  // "And heaven, and heaven"
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4,
  // "and nature sing"
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};

const int joyToTheWorldDurations[] = {
  // "Joy to the world"
  DOTTED_HALF, QUARTER, DOTTED_QUARTER, EIGHTH,
  // "the Lord is come"
  DOTTED_HALF, QUARTER, QUARTER, WHOLE,
  // "Let earth re-"
  DOTTED_HALF, QUARTER,
  // "-ceive her"
  DOTTED_HALF, QUARTER,
  // "King"
  DOTTED_HALF, WHOLE,
  // "Let every heart"
  QUARTER, EIGHTH, EIGHTH, DOTTED_QUARTER, EIGHTH,
  // "prepare Him room"
  QUARTER, EIGHTH, EIGHTH, WHOLE,
  // "And heaven and nature sing"
  EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, HALF,
  // "And heaven and nature sing"
  EIGHTH, EIGHTH, EIGHTH, QUARTER, EIGHTH, HALF,
  // "And heaven, and heaven"
  QUARTER, EIGHTH, EIGHTH, QUARTER, HALF,
  // "and nature sing"
  QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, WHOLE
};

#define JOY_TO_THE_WORLD_LENGTH 45

#endif

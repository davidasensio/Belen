#ifndef SILENT_NIGHT_H
#define SILENT_NIGHT_H

#include "notes.h"

// Silent Night melody - first verse
const int silentNightNotes[] = {
  // "Si-lent night" (G A. G E)
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  // "Ho-ly night" (G A. G E)
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  // "All is calm" (D5 D5 B4)
  NOTE_D5, NOTE_D5, NOTE_B4,
  // "All is bright" (C5 C5 G4)
  NOTE_C5, NOTE_C5, NOTE_G4,
  // "Round yon vir-gin" (A4 A4 C5 B4 A4)
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_A4,
  // "Mo-ther and child" (G4 A4 G4 E4)
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  // "Ho-ly in-fant so" (A4 A4 C5 B4 A4)
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_A4,
  // "ten-der and mild" (G4 A4 G4 E4)
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_E4,
  // "Sleep in hea-ven-ly" (D5 D5 F5 D5 B4)
  NOTE_D5, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_B4,
  // "peace" (C5 E5)
  NOTE_C5, NOTE_E5,
  // "Sleep in hea-ven-ly" (C5 G4 E4 G4)
  NOTE_C5, NOTE_G4, NOTE_E4, NOTE_G4,
  // "peace" (F4 D5 C5)
  NOTE_F4, NOTE_D5, NOTE_C5
};

const int silentNightDurations[] = {
  // "Si-lent night"
  DOTTED_QUARTER, EIGHTH, QUARTER, DOTTED_HALF,
  // "Ho-ly night"
  DOTTED_QUARTER, EIGHTH, QUARTER, DOTTED_HALF,
  // "All is calm"
  DOTTED_QUARTER, QUARTER, DOTTED_HALF,
  // "All is bright"
  DOTTED_QUARTER, QUARTER, DOTTED_HALF,
  // "Round yon vir-gin"
  DOTTED_QUARTER, EIGHTH, QUARTER, EIGHTH, QUARTER,
  // "Mo-ther and child"
  DOTTED_QUARTER, EIGHTH, QUARTER, DOTTED_HALF,
  // "Ho-ly in-fant so"
  DOTTED_QUARTER, EIGHTH, QUARTER, EIGHTH, QUARTER,
  // "ten-der and mild"
  DOTTED_QUARTER, EIGHTH, QUARTER, DOTTED_HALF,
  // "Sleep in hea-ven-ly"
  DOTTED_QUARTER, EIGHTH, QUARTER, EIGHTH, QUARTER,
  // "peace"
  DOTTED_QUARTER, DOTTED_HALF,
  // "Sleep in hea-ven-ly"
  QUARTER, EIGHTH, EIGHTH, QUARTER,
  // "peace"
  DOTTED_QUARTER, QUARTER, WHOLE
};

#define SILENT_NIGHT_LENGTH 42

#endif

#ifndef ADESTE_FIDELES_H
#define ADESTE_FIDELES_H

#include "notes.h"

// "Adeste Fideles" (O Come, All Ye Faithful) melody
const int adesteFidelesNotes[] = {
  // "O come, all ye faithful" (A-des-te fi-de-les)
  NOTE_G4, NOTE_G4, NOTE_D4, NOTE_G4, NOTE_A4, NOTE_D4,
  // "Joyful and triumphant" (Lae-ti tri-um-phan-tes)
  NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
  // "O come ye, o come ye to" (Ve-ni-te, ve-ni-te in)
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_D4,
  // "Bethlehem" (Beth-le-hem)
  NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4,
  // "Come and behold Him" (Na-tum vi-de-te)
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4,
  // "Born the King of angels" (Re-gem an-ge-lo-rum)
  NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_D4,
  // "O come let us adore Him" (Ve-ni-te a-do-re-mus)
  NOTE_D5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_A4,
  // "O come let us adore Him" (Ve-ni-te a-do-re-mus)
  NOTE_B4, NOTE_A4, NOTE_B4, NOTE_G4, NOTE_A4, NOTE_F4,
  // "O come let us adore Him" (Ve-ni-te a-do-re-mus)
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4,
  // "Christ the Lord" (Do-mi-num)
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4
};

const int adesteFidelesDurations[] = {
  // "O come, all ye faithful"
  HALF, QUARTER, QUARTER, HALF, HALF, WHOLE,
  // "Joyful and triumphant"
  QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, WHOLE,
  // "O come ye, o come ye to"
  HALF, QUARTER, QUARTER, QUARTER, QUARTER, HALF,
  // "Bethlehem"
  QUARTER, QUARTER, QUARTER, WHOLE,
  // "Come and behold Him"
  QUARTER, QUARTER, QUARTER, HALF, HALF,
  // "Born the King of angels"
  QUARTER, QUARTER, QUARTER, QUARTER, HALF, WHOLE,
  // "O come let us adore Him"
  HALF, QUARTER, QUARTER, HALF, HALF, WHOLE,
  // "O come let us adore Him"
  HALF, QUARTER, QUARTER, HALF, HALF, WHOLE,
  // "O come let us adore Him"
  HALF, QUARTER, QUARTER, QUARTER, WHOLE,
  // "Christ the Lord"
  DOTTED_HALF, QUARTER, HALF, WHOLE
};

#define ADESTE_FIDELES_LENGTH 47

#endif

#ifndef SINRIC_PRO_H
#define SINRIC_PRO_H

// Setup and loop functions
void setupSinricPro();
void handleSinricPro();

// Functions to send contact events to Sinric Pro devices
void sendAlexaCommand(bool powerState);   // Sensor 1
void sendAlexaCommand2(bool powerState);  // Sensor 2

#endif

#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProContactsensor.h>
#include "sinric_pro.h"

// ============================================
// SINRIC PRO CREDENTIALS
// ============================================
// Check if credentials.h exists (gitignored file with real credentials)
#if __has_include("credentials.h")
  #include "credentials.h"
  #define APP_KEY      SINRIC_APP_KEY
  #define APP_SECRET   SINRIC_APP_SECRET
  #define DEVICE_ID_1  SINRIC_DEVICE_ID_1
  #define DEVICE_ID_2  SINRIC_DEVICE_ID_2
#else
  // Fallback - get these from https://sinric.pro after creating an account
  #define APP_KEY      "YOUR_APP_KEY_HERE"
  #define APP_SECRET   "YOUR_APP_SECRET_HERE"
  #define DEVICE_ID_1  "YOUR_DEVICE_ID_1_HERE"
  #define DEVICE_ID_2  "YOUR_DEVICE_ID_2_HERE"
#endif

// Track connection status
bool sinricConnected = false;

// Reference to our contact sensors - must be declared globally
SinricProContactsensor &contactSensor1 = SinricPro[DEVICE_ID_1];
SinricProContactsensor &contactSensor2 = SinricPro[DEVICE_ID_2];

void setupSinricPro() {
  // Setup SinricPro callbacks
  SinricPro.onConnected([]() {
    Serial.println("Sinric Pro connected!");
    sinricConnected = true;
  });
  SinricPro.onDisconnected([]() {
    Serial.println("Sinric Pro disconnected!");
    sinricConnected = false;
  });

  // Start SinricPro
  SinricPro.begin(APP_KEY, APP_SECRET);
  Serial.println("Sinric Pro initialized, waiting for connection...");
}

void handleSinricPro() {
  SinricPro.handle();
}

// Send contact sensor event to Sinric Pro (Sensor 1)
// For Contact Sensor: false = OPEN (triggered), true = CLOSED (normal)
// Alexa routines trigger on "opens" event
void sendAlexaCommand(bool turnOn) {
  if (!sinricConnected) {
    Serial.println("Cannot send - Sinric Pro not connected!");
    return;
  }

  // turnOn=true -> send OPEN event (false) to trigger "opens" routine
  // turnOn=false -> send CLOSED event (true) to trigger "closes" routine
  bool contactState = !turnOn;  // Invert: button ON = contact OPEN (false)
  bool success = contactSensor1.sendContactEvent(contactState);

  Serial.printf("Sensor 1: Sent contact %s event - %s\r\n",
    contactState ? "CLOSED" : "OPEN",
    success ? "SUCCESS" : "FAILED");
}

// Send contact sensor event to Sinric Pro (Sensor 2 - Virtual Sensor 2)
void sendAlexaCommand2(bool turnOn) {
  if (!sinricConnected) {
    Serial.println("Cannot send - Sinric Pro not connected!");
    return;
  }

  bool contactState = !turnOn;
  bool success = contactSensor2.sendContactEvent(contactState);

  Serial.printf("Sensor 2: Sent contact %s event - %s\r\n",
    contactState ? "CLOSED" : "OPEN",
    success ? "SUCCESS" : "FAILED");
}

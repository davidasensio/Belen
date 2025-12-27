#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProContactsensor.h>
#include "sinric_pro.h"

// ============================================
// SINRIC PRO CREDENTIALS - FILL IN YOUR VALUES
// ============================================
// Get these from https://sinric.pro after creating an account
// user: nayedon363@fftube.com / pass: Naye1123
//
#define APP_KEY    "eae7a719-a997-40bf-b850-fb685d9db789"      // App Key from Sinric Pro
#define APP_SECRET "fde5e5ca-0254-45c1-a8eb-0f7caf0d9b57-80373734-51df-457f-ab27-d3ce2c03b30f"   // App Secret from Sinric Pro
#define DEVICE_ID_1  "695442e441d7ad27c3729313"    // Contact Sensor 1
#define DEVICE_ID_2  "69544513971001dc5588c7a2"    // Virtual Sensor 2

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

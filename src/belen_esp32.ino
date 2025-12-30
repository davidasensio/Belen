#include <Arduino.h>
#include <ESP32Servo.h>
#include "songs/silent_night.h"
#include "songs/joy_to_the_world.h"
#include "songs/jingle_bells.h"
#include "songs/adeste_fideles.h"
#include "web_server.h"
#include "sinric_pro.h"

// Check if credentials.h exists (gitignored file with real credentials)
#if __has_include("credentials.h")
  #include "credentials.h"
  const char* ssid = WIFI_SSID;
  const char* password = WIFI_PASSWORD;
#else
  // Fallback - change these to your network
  const char* ssid = "YOUR_WIFI_SSID";
  const char* password = "YOUR_WIFI_PASSWORD";
#endif

#define LED 27 // 25 or 26 or 27
#define PIEZO 26
#define SERVO_PIN 14

// RGB LED pins
#define RGB_RED 25
#define RGB_GREEN 32
#define RGB_BLUE 33

// PWM channels for RGB (ESP32 has 16 channels: 0-15)
// Using channels 5-7 to avoid conflict with tone() which uses lower channels
#define PWM_CHANNEL_RED 5
#define PWM_CHANNEL_GREEN 6
#define PWM_CHANNEL_BLUE 7
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8  // 8-bit resolution (0-255)

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
bool melodyPaused = false;
bool noteGapActive = false;
unsigned long noteGapStartTime = 0;
const int NOTE_GAP = 30;  // Gap between notes in ms

// Status LED variables (non-blocking)
unsigned long lastLedToggle = 0;
const int LED_INTERVAL = 500;
bool ledState = false;

// Ambient light variables
unsigned long lastLightUpdate = 0;
const int LIGHT_UPDATE_INTERVAL = 10;  // Update every 10ms for smooth transitions
int brightnessValue = 0;
int fadeDirection = 1;  // 1 = fading up, -1 = fading down

// Warm yellow color ratio (R=255, G=100 gives a nice warm amber)
const float GREEN_RATIO = 0.4;  // Green at 40% of red for warm yellow

// Servo
Servo myServo;
bool servoEnabled = true;
int servoPosition = 90;

// Control states
bool ledEnabled = true;
bool ambientEnabled = true;

void selectRandomSong() {
  int songIndex = random(NUM_SONGS);
  melodyNotes = songs[songIndex].notes;
  melodyDurations = songs[songIndex].durations;
  melodyLength = songs[songIndex].length;
  Serial.print("Playing: ");
  Serial.println(songs[songIndex].name);
}

void pauseMelody() {
  melodyPaused = true;
  noTone(PIEZO);
  Serial.println("Melody paused");
}

void resumeMelody() {
  melodyPaused = false;
  Serial.println("Melody resumed");
}

void toggleMelody() {
  if (melodyPaused) {
    resumeMelody();
  } else {
    pauseMelody();
  }
}

// RGB LED functions
void setRGB(int r, int g, int b) {
  ledcWrite(PWM_CHANNEL_RED, r);
  ledcWrite(PWM_CHANNEL_GREEN, g);
  ledcWrite(PWM_CHANNEL_BLUE, b);
}

void setupRGB() {
  // Configure PWM channels
  ledcSetup(PWM_CHANNEL_RED, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_GREEN, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_BLUE, PWM_FREQ, PWM_RESOLUTION);

  // Attach channels to pins
  ledcAttachPin(RGB_RED, PWM_CHANNEL_RED);
  ledcAttachPin(RGB_GREEN, PWM_CHANNEL_GREEN);
  ledcAttachPin(RGB_BLUE, PWM_CHANNEL_BLUE);

  // Start with lights off
  setRGB(0, 0, 0);
}


void updateServo() {
  if (!servoEnabled) return;

  static unsigned long lastServoUpdate = 0;
  static int servoDirection = 1;

  if (millis() - lastServoUpdate > 20) {
    lastServoUpdate = millis();
    servoPosition += servoDirection;
    if (servoPosition >= 160) servoDirection = -1;
    if (servoPosition <= 20) servoDirection = 1;
    myServo.write(servoPosition);
  }
}

void startupTest() {
  // Blink blue 4 times
  for (int i = 0; i < 4; i++) {
    setRGB(0, 0, 255);
    delay(100);
    setRGB(0, 0, 0);
    delay(100);
  }

  // Blink red 4 times
  for (int i = 0; i < 4; i++) {
    setRGB(255, 0, 0);
    delay(100);
    setRGB(0, 0, 0);
    delay(100);
  }

  // Fixed green for 500ms
  setRGB(0, 255, 0);
  delay(500);
  setRGB(0, 0, 0);
}

void updateAmbientLight() {
  if (!ambientEnabled) {
    return;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastLightUpdate < LIGHT_UPDATE_INTERVAL) {
    return;
  }
  lastLightUpdate = currentTime;

  // Warm yellow fade: 0 -> 255 -> 0
  brightnessValue += fadeDirection;
  if (brightnessValue >= 255) {
    brightnessValue = 255;
    fadeDirection = -1;
  } else if (brightnessValue <= 0) {
    brightnessValue = 0;
    fadeDirection = 1;
  }

  int redValue = brightnessValue;
  int greenValue = (int)(brightnessValue * GREEN_RATIO);
  setRGB(redValue, greenValue, 0);
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  // Seed random with analog noise
  randomSeed(analogRead(0));

  // Initialize RGB LED
  setupRGB();

  // Run startup test
  startupTest();

  // Initialize servo on channel 8 to avoid conflicts with tone() and RGB PWM
  myServo.setPeriodHertz(50);
  ESP32PWM::allocateTimer(2);  // Use timer 2 for servo
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(90);

  // Connect to WiFi and start web server
  setupWiFi();
  setupWebServer();

  // Initialize Sinric Pro for Alexa control
  setupSinricPro();

  // Select a random song at boot
  selectRandomSong();
}

void updateStatusLed() {
  unsigned long currentTime = millis();
  if (currentTime - lastLedToggle >= LED_INTERVAL) {
    lastLedToggle = currentTime;
    ledState = !ledState;
    digitalWrite(LED, ledState ? HIGH : LOW);
  }
}

void loop() {
  server.handleClient();
  handleSinricPro();
  updateMelody();
  updateAmbientLight();
  updateServo();
  if (ledEnabled) updateStatusLed();
}

void updateMelody() {
  // Skip if paused
  if (melodyPaused) {
    return;
  }

  unsigned long currentTime = millis();

  // Handle gap between notes (non-blocking)
  if (noteGapActive) {
    if (currentTime - noteGapStartTime >= NOTE_GAP) {
      noteGapActive = false;
      noteStartTime = currentTime;
      tone(PIEZO, melodyNotes[currentNoteIndex]);
    }
    return;
  }

  // If melody finished, restart it
  if (currentNoteIndex >= melodyLength) {
    currentNoteIndex = 0;
    melodyPlaying = false;
  }

  // Start melody if not playing
  if (!melodyPlaying) {
    melodyPlaying = true;
    noteStartTime = currentTime;
    tone(PIEZO, melodyNotes[currentNoteIndex]);
    return;
  }

  // Check if current note duration has elapsed
  if (currentTime - noteStartTime >= melodyDurations[currentNoteIndex]) {
    noTone(PIEZO);
    currentNoteIndex++;

    // Start gap before next note if available
    if (currentNoteIndex < melodyLength) {
      noteGapActive = true;
      noteGapStartTime = currentTime;
    } else {
      melodyPlaying = false;
    }
  }
}

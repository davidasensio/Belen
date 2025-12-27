#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "web_server.h"

// External variables from main file
extern const char* ssid;
extern const char* password;
extern bool ledEnabled;
extern bool ambientEnabled;
extern bool servoEnabled;
extern Servo myServo;
extern int currentNoteIndex;
extern bool melodyPlaying;
extern bool melodyPaused;

// External functions from main file
extern void pauseMelody();
extern void resumeMelody();
extern void selectRandomSong();
extern void setRGB(int r, int g, int b);

// Pin definition (must match main file)
#define LED 27

// Web server instance
WebServer server(80);

// Web page HTML
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Belen Control</title>
  <style>
    body { font-family: Arial; text-align: center; margin: 20px; background: #1a1a2e; color: #eee; }
    h1 { color: #ffd700; }
    .btn {
      padding: 15px 30px;
      margin: 10px;
      font-size: 18px;
      border: none;
      border-radius: 10px;
      cursor: pointer;
      min-width: 200px;
    }
    .btn-on { background: #4CAF50; color: white; }
    .btn-off { background: #f44336; color: white; }
    .btn-action { background: #2196F3; color: white; }
    .status { margin: 20px; padding: 10px; background: #16213e; border-radius: 10px; }
  </style>
  <script>
    function send(url) {
      fetch(url).catch(function(e) { console.log(e); });
    }
  </script>
</head>
<body>
  <h1>Belen Control Panel</h1>
  <h2>&#x1F56F;&#xFE0F;&#x1F3B6;&#x1F31F;</h2>

  <div class="status">
    <h2>Blink Led</h2>
    <button class="btn btn-on" onclick="send('/led/on')">ON</button>
    <button class="btn btn-off" onclick="send('/led/off')">OFF</button>
  </div>

  <div class="status">
    <h2>Music</h2>
    <button class="btn btn-on" onclick="send('/music/on')">Play</button>
    <button class="btn btn-off" onclick="send('/music/off')">Pause</button>
    <button class="btn btn-action" onclick="send('/music/next')">Next Song</button>
  </div>

  <div class="status">
    <h2>Ambient Light</h2>
    <button class="btn btn-on" onclick="send('/ambient/on')">ON</button>
    <button class="btn btn-off" onclick="send('/ambient/off')">OFF</button>
  </div>

  <div class="status">
    <h2>Servo</h2>
    <button class="btn btn-on" onclick="send('/servo/on')">Start</button>
    <button class="btn btn-off" onclick="send('/servo/off')">Stop</button>
  </div>

  <footer style="margin-top: 30px; color: gray;">Made with &#x2764;&#xFE0F; by Maria Hurtado &amp; David A.</footer>
</body>
</html>
)rawliteral";

// Handler functions
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleLedOn() {
  ledEnabled = true;
  digitalWrite(LED, HIGH);
  server.send(200, "text/plain", "OK");
}

void handleLedOff() {
  ledEnabled = false;
  digitalWrite(LED, LOW);
  server.send(200, "text/plain", "OK");
}

void handleMusicOn() {
  resumeMelody();
  server.send(200, "text/plain", "OK");
}

void handleMusicOff() {
  pauseMelody();
  server.send(200, "text/plain", "OK");
}

void handleMusicNext() {
  selectRandomSong();
  currentNoteIndex = 0;
  melodyPlaying = false;
  melodyPaused = false;
  server.send(200, "text/plain", "OK");
}

void handleAmbientOn() {
  ambientEnabled = true;
  server.send(200, "text/plain", "OK");
}

void handleAmbientOff() {
  ambientEnabled = false;
  setRGB(0, 0, 0);
  server.send(200, "text/plain", "OK");
}

void handleServoOn() {
  servoEnabled = true;
  server.send(200, "text/plain", "OK");
}

void handleServoOff() {
  servoEnabled = false;
  myServo.write(90);
  server.send(200, "text/plain", "OK");
}

void setupWebServer() {
  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);
  server.on("/music/on", handleMusicOn);
  server.on("/music/off", handleMusicOff);
  server.on("/music/next", handleMusicNext);
  server.on("/ambient/on", handleAmbientOn);
  server.on("/ambient/off", handleAmbientOff);
  server.on("/servo/on", handleServoOn);
  server.on("/servo/off", handleServoOff);
  server.begin();
  Serial.println("Web server started");
}

void setupWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());
}

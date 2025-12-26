#include <Arduino.h>

#define LED 27 // 25 or 26 or 27

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, LOW);
  delay(500);
  digitalWrite(LED, HIGH);
  Serial.println("Hola");
  delay(500);
}

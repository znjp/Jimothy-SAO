// Jimothy SAO v0

#include <Arduino.h>

const int LEFT_EYE = PIN_PB0;
const int RIGHT_EYE = PIN_PB1;
const int RING1 = PIN_PA7;
const int RING2 = PIN_PA6;
const int RING3 = PIN_PA5;
const int RING4 = PIN_PA4;
const int RINGS[] = {RING1, RING2, RING3, RING4};
#define NUM_RINGS 4

//Stare and Blink
const unsigned long stareInterval = 5000;
unsigned long lastBlinkTime = 0; // Store the time when the eyes were last blinked
int blinkCount = 0;

void wink(){
  for(int i = 255; i > 0; i = i - 2){
    analogWrite(RIGHT_EYE, i);
    delay(1);
  }
  digitalWrite(RIGHT_EYE, LOW);
  delay(200);
  for(int i = 0; i < 255; i = i + 2){
    analogWrite(RIGHT_EYE, i);
    delay(1);
  }
}

void tailwag(){
  for(int i = 0; i < NUM_RINGS; i++){
    digitalWrite(RINGS[i], LOW);
    delay(100);
  }
  for(int i = 0; i < NUM_RINGS; i++){
    digitalWrite(RINGS[i], HIGH);
    delay(100);
  }

}

void doubleBlink(){
  digitalWrite(LEFT_EYE, LOW);
  digitalWrite(RIGHT_EYE,LOW);
  delay(100);
  digitalWrite(LEFT_EYE, HIGH);
  digitalWrite(RIGHT_EYE,HIGH);
  delay(300);
  digitalWrite(LEFT_EYE, LOW);
  digitalWrite(RIGHT_EYE,LOW);
  delay(100);
}

void awaken(){
  for(int i = 0; i < 256; i++){
    analogWrite(LEFT_EYE, i);
    analogWrite(RIGHT_EYE, i);
    delay(20);
  }
  doubleBlink();
  digitalWrite(LEFT_EYE,HIGH);
  digitalWrite(RIGHT_EYE,HIGH);  
  for(int i = 0; i < NUM_RINGS; i++){
    digitalWrite(RINGS[i], HIGH);
    delay(100);
  }

  delay(stareInterval);
}


void setup() {

  pinMode(LEFT_EYE, OUTPUT);
  pinMode(RIGHT_EYE, OUTPUT);
  digitalWrite(LEFT_EYE,LOW);
  digitalWrite(RIGHT_EYE,LOW);
  for(int i = 0; i < NUM_RINGS; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  awaken();
}

void loop() {
  unsigned long currentTime = millis();

  digitalWrite(LEFT_EYE, HIGH); //Stare
  digitalWrite(RIGHT_EYE,HIGH);
  // Check if enough time has passed to blink the eyes
  if (currentTime - lastBlinkTime >= stareInterval && blinkCount < 4) {
    // Blink the eyes
    doubleBlink();
    // Update the last blink time
    lastBlinkTime = currentTime;
    blinkCount += 1;
  }
  if (currentTime - lastBlinkTime >= stareInterval && blinkCount == 4) {
    // wink
    wink();
    tailwag();
    // Update the last blink time
    lastBlinkTime = currentTime;
    blinkCount = 0;
  }

}

// [♥️]znjp

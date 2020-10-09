#include "Callbacks.h"
#include <EEPROM.h>

extern volatile unsigned long timerexpire;

String options = " ";

void setup() {
  // initialize the LED pin as an output:
  
  for (int i = 0; i < numButtons; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT);
  }
  //add all buttons interruptions if needed     ≤=========================================================================
  pinMode(InterruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(InterruptPin), Interruption, RISING);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println(Welcome);
  readMemory();
}

void loop() {

  if (Serial.available() > 0) {
    Serial.println(Checking);
    options = Serial.readString();
    options.trim();
    UserRequest(options);
  }
  if (timerexpire <= millis()) {
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(TimeON/2);
  
  //Serial.println("Still alive");
}

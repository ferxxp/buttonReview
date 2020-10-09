#ifndef CALLBACKS // include guard
#define CALLBACKS
#include "Callbacks.h"
#include <EEPROM.h>

volatile unsigned long timerexpire = 0;
volatile unsigned int Values [] =  {0, 0, 0, 0, 0};

void Interruption() {
  const int num = readInputs();
  if (num > 0 && num <= numButtons) {
    Serial.println(buttomPressed + String(num));
    if (timerexpire <= millis()) {
      Values[num - 1]++;
      writeMemory();
      timerexpire = millis() + TimeON;
      digitalWrite(ledPins[num - 1], HIGH);
      String msg=printmem(Values);
      Serial.println(Readstate);
      Serial.println(msg);
    } else
      Serial.println(wait);
  }
}
int readInputs() {
  int returned = -1;
  for (int i = numButtons-1; i >= 0 ; i--) {
    returned = (digitalRead(buttonPins[i]) ? i + 1 : returned);
  }
  return returned;
}
bool readMemory() {
  EEPROM.get(0, Values);
  return true;
}
bool writeMemory() {
  EEPROM.put(0, Values);
  return true;
}
bool wipeMemory() {
  for (int i = 0; i < numButtons; i++) {
    Values[i] = 0;
  }
  EEPROM.put(0, Values);
  return true;
}
String printmem(const int values[]) {
  String response = "";
  for (int i = 0; i < numButtons; i++) {
    response = (response + NameButtons[i] + ": " + Values[i] + ", ");
  }
  return response;
}
void UserRequest(String options){
  if (options.equalsIgnoreCase(Option1)) {
      Serial.println(Readstate);
      Serial.println( printmem(Values));
    }
    else if (options.equalsIgnoreCase(Option2)) {
      wipeMemory();
      Serial.println(Reset);
    }else if (options.equalsIgnoreCase(Option3)) {
      for (int i = 0; i < numButtons; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      timerexpire = millis() + TimeON;
      Serial.println(Onlights);
    }else{
      Serial.println(options+errorRqst);
      }
  }
#endif

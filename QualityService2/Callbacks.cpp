#ifndef CALLBACKS // include guard
#define CALLBACKS
#include "Callbacks.h"
#include <EEPROM.h>

volatile unsigned long timerexpire = 0;
volatile unsigned int Values [] =  {0, 0, 0, 0, 0};

void Interruption() {
  const int num = readInputs();
  if (num > 0 && num <= numButtons) {
    Serial.print(buttomPressed);
    Serial.println(String(num));
    if (timerexpire <= millis()) {
      Values[num - 1]++;
      writeMemory();
      timerexpire = millis() + TimeON;
      digitalWrite(ledPins[num - 1], HIGH);
      printmem(Values);
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
  printmem(Values);
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
void printmem(const int values[]) {
  Serial.println(Readstate);
  for (int i = 0; i < numButtons; i++) {
    Serial.print(String(NameButtons[i]));
    Serial.print(": ");
    Serial.print(String(values[i]));
    Serial.print(", ");
  }
  Serial.println("");
}
void UserRequest(String op){
  if (op.equalsIgnoreCase(Option1)) {
      readMemory();
    }
    else if (op.equalsIgnoreCase(Option2)) {
      wipeMemory();
      Serial.println(Reset);
    }else if (op.equalsIgnoreCase(Option3)) {
      for (int i = 0; i < numButtons; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
      timerexpire = millis() + TimeON;
      Serial.println(Onlights);
    }else{
      Serial.println(op);
      Serial.println(Welcome);
      }
  }
#endif

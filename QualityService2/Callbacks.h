#include "Arduino.h"

const int numButtons = 4;
const int buttonPins [] = {5,7,9,11,13};    // the number of the pushbutton pin
const int ledPins [] =  {4,6,8,10,12};     // the number of the LED pin
const int InterruptPin=2;
const int TimeON=2500;

const String NameButtons []={"Excelente","Bueno","Regular","Mal","Pesimo"};
const String Option1="Estado";
const String Option2="Borrar";
const String Option3="Luces";
const String Welcome=("Bienvenido al control de la plataforma de valoraciones.\n 1.-Para imprimir un informe escriba: "+Option1+"\n 2.-Para borrar la memoria escriba: "+Option2+"\n 3.-Para probar las luces escriba: "+Option3);
const String buttomPressed="Se ha pulsado el boton ";
const String Checking="Procesando";
const String Reset="Memoria borrada";
const String Readstate="Las valoraciones son las siguientes:";
const String wait="Por favor espere para introducir la siguiente opinión.";
const String errorRqst=" no es ninguna de las opciones.\n Por favor compruebe la sintaxis.";
const String Onlights="Luces encendidas.";

void Interruption();
int readInputs();
bool readMemory();
bool writeMemory();
bool wipeMemory();
void printmem(const int values[]);
void UserRequest(String op);

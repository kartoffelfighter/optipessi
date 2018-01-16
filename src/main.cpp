#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <math.h>
#include "conf.h" // header with configs
#include "pins.h" // header with pin information
#include "functions.h"

#define ledPin 13

void setup()
{

  Serial.begin(115200);
  Serial.println("hello");
  pinMode(optimist, INPUT_PULLUP);
  pinMode(pessimist, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(optimist), optimistISR, FALLING);   // optimistISR => runOptimist = true
  attachInterrupt(digitalPinToInterrupt(pessimist), pessimistISR, FALLING); // pessimistISR => runPessimist = true

  pinMode(ledPin, OUTPUT);  // Ausgabe LED festlegen
}

void loop() {

}

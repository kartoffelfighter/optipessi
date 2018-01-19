#include <Arduino.h>
#include <math.h>
#include "conf.h" // header with configs
#include "pins.h" // header with pin information
#include "functions.h"

#define ledPin 13


void setup()
{

  Serial.begin(115200);
  Serial.println("hello");
  pinMode(optimist, 0x2);
  pinMode(pessimist, 0x2); //0x2 -> Input Pullup

  pinMode(dac1, 0x1);
  pinMode(dac2, 0x1);
  pinMode(dac3, 0x1);
  pinMode(mux1, 0x1);
  pinMode(mux2, 0x1);
  pinMode(mux3, 0x1);
  pinMode(mux4, 0x1);

  attachInterrupt(digitalPinToInterrupt(optimist), optimistISR, FALLING);   // optimistISR => runOptimist = true
  attachInterrupt(digitalPinToInterrupt(pessimist), pessimistISR, FALLING); // pessimistISR => runPessimist = true

  pinMode(ledPin, 0x1); // Ausgabe LED festlegen

  resetLight();
}

void loop()
{
  // mux1 attached:
  // dac1 : voll weiß
  // dac2 : voll grün
  // dac3 : voll rot

  // mux2 attached:
  // dac1 : leer weiß
  // dac2 : leer grün
  // dac3 : leer rot

  // mux3 attached:
  // dac1 : oben weiß
  // dac2 : oben grün
  // dac3 : oben rot

  // mux4 attached:
  // dac1 : oben blau
  // dac2 : leer blau
  // dac3 : voll rot (blau, RGB defekt)

  if (runPessimist)
  {
    if(active && firstrun) {
    resetLight();
    firstrun = 0;
    }
    digitalWrite(mux3, 1);  // oben
    digitalWrite(mux1, 0);  // voll resetten
    digitalWrite(mux2, 1);  // leer
    if(firstrun && !active) {
    fadeUp(1);
    firstrun = 0;
    } 
    
    
    if (millis() - counter1 <= stayActive)
    {
      active = 1;
      Serial.println("Pessimist button pressed!");
      analogWrite(dac1, 255);  
      analogWrite(dac3, 255);
    }
    else
    {
      runPessimist = 0;
      fadeDown(1);
      resetLight();
    }
  }


if (runOptimist)
  {
    if(active && firstrun) {
      resetLight();
      firstrun = 0;
    }
    digitalWrite(mux3, 1);  // oben
    digitalWrite(mux2, 0);  // leer resetten
    digitalWrite(mux1, 1);  // voll
    if(firstrun && !active) {
    fadeUp(1);
    firstrun = 0;
    }

    
    if (millis() - counter1 <= stayActive)
    {
      active = 1;
      Serial.println("Optimist button pressed!");
      analogWrite(dac1, 255); 
      analogWrite(dac2, 255);

    }
    else
    {
      runOptimist = 0;
      fadeDown(1);
      resetLight();
    }
  }
}

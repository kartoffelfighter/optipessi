#include <Arduino.h>
#include <math.h>
#include "conf.h" // header with configs
#include "pins.h" // header with pin information
#include "functions.h"

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

  pinMode(ledOpti, 0x1);
  pinMode(ledPessi, 0x1);

  digitalWrite(ledOpti, 0x1);
  digitalWrite(ledOpti, 0x1);
  resetLight();
}

void loop()
{
  if (Serial.available() >= 0)
  {

    byte incomingByte = Serial.read();

    switch (incomingByte)
    {
    case 'o': //  turn off
      resetLight();
      break;
    case 'd': //  show all possible lights (pretty bright)
      lightMeUp();
      break;
    case 'p': // run pessimist routine
      pessimistISR();
      break;
    case 'q': // run optimist routine
      optimistISR();
      Serial.println("set optimist Serial");
      break;
    case 'e':
      while (!runOptimist && !runPessimist)
      {
        Serial.println("party");
        lightMeUp();
        delay(100);
        resetLight();
        delay(100);
      }
      break;
    }
  }

  if (runPessimist)
  {
    Serial.println("running Pessimist");
    if (millis() - counter1 <= stayActive)
    {
      Serial.println("Pessimist time not over");
      if (activeO or firstrun)
      {
        Serial.print("activeO:");
        Serial.println(activeO);
        Serial.print("firstrun:");
        Serial.println(firstrun);
        Serial.println("");
        resetLight();
        firstrun = 0;
        digitalWrite(mux1, 0); // voll resetten
        digitalWrite(mux2, 1); // leer
        digitalWrite(mux3, 1); // oben
        digitalWrite(mux4, 0); // disable blue mux
        fadeUp(1);
        activeP = 1;
        activeO = 0;
      }

      analogWrite(dac1, 255);
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
    Serial.println("running Optimist");
    if (millis() - counter1 <= stayActive)
    {
      Serial.println("optimist time not over");
      if (activeP or firstrun)
      {
        Serial.print("activeP:");
        Serial.println(activeP);
        Serial.print("firstrun:");
        Serial.println(firstrun);
        Serial.println("");
        resetLight();
        firstrun = 0;
        fadeUp(1);
        activeP = 0;
        activeO = 1;
      }

      digitalWrite(mux1, 1); // voll
      digitalWrite(mux2, 0); // leer resetten
      digitalWrite(mux3, 1); // oben
      digitalWrite(mux4, 0); // disable blue mux
      analogWrite(dac1, 255);
    }
    else
    {
      runOptimist = 0;
      fadeDown(1);
      resetLight();
    }
  }

  /*
if(millis() - counter1 + stayActive  <= lightShow) {
      digitalWrite(mux3, 1);
  if(!runPessimist && !runOptimist && !Serial.available()) {
    //analogWrite(dac1, 255);
    analogWrite(dac2, 255);
    analogWrite(dac3, 255);
  }
  //resetLight();
  counter2 = millis();
  }
  */
}

#include <Arduino.h>
#include <math.h>
#include "conf.h" // header with configs
#include "pins.h" // header with pin information
#include "functions.h"

void setup()
{

  Serial.begin(115200);
  serialOpen();
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
  resetLight();
}

void loop()
{
  if (Serial.available() >= 0)
  {

    switch (Serial.read())
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
    case 's':
      serialOpen();
      break;
    case 'a':
      Serial.println("Send value followd by b");
      incomingSettings = Serial.parseInt();
      if (Serial.read() == 'b')
      {
        Serial.print("adjusting stayActive to: ");
        Serial.print(incomingSettings);
        Serial.println("s");
        stayActive = incomingSettings * 1000;
      }
      break;
    case 'l':
      Serial.println("Send value followd by b");
      incomingSettings = Serial.parseInt();
      if (Serial.read() == 'b')
      {
        Serial.print("adjusting lightShow to: ");
        Serial.print(incomingSettings);
        Serial.println("m");
        lightShow = incomingSettings;
      }
      break;
    case 'g':
      Serial.println("Send value followd by b");
      incomingSettings = Serial.parseInt();
      if (Serial.read() == 'b')
      {
        Serial.print("adjusting lightShow to: ");
        Serial.print(incomingSettings);
        Serial.println("ms");
        lightShow = incomingSettings;
      }
      break;
    }
  }

  while (runPessimist)
  {
    digitalWrite(ledPessi, 0x1);
    //Serial.println("running Pessimist");
    if (millis() - counter1 <= stayActive)
    {
      //  Serial.println("Pessimist time not over");
      if (activeO or firstrun)
      {
        // Serial.print("activeO:");
        // Serial.println(activeO);
        //Serial.print("firstrun:");
        //Serial.println(firstrun);
        //Serial.println("");
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
      lastRunning = millis();
    }
  }

  while (runOptimist)
  {
    digitalWrite(ledOpti, 0x1);
    //Serial.println("running Optimist");
    if (millis() - counter1 <= stayActive)
    {
      // Serial.println("Optimist time not over");
      if (activeP or firstrun)
      {
        // Serial.print("activeP:");
        //  Serial.println(activeP);
        //Serial.print("firstrun:");
        // Serial.println(firstrun);
        //  Serial.println("");
        resetLight();
        firstrun = 0;
        digitalWrite(mux1, 1); // voll
        digitalWrite(mux2, 0); // leer resetten
        digitalWrite(mux3, 1); // oben
        digitalWrite(mux4, 0); // disable blue mux
        fadeUp(1);
        activeP = 0;
        activeO = 1;
      }

      analogWrite(dac1, 255);
    }
    else
    {
      runOptimist = 0;
      fadeDown(1);
      resetLight();
      lastRunning = millis();
    }
  }

  if (millis() - lastRunning >= lightShow * 60 * 1000)
  {
    standby();
    lastRunning = millis();
  }
}

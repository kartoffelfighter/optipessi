void pessimistISR()
{
    runPessimist = 0x1;
    runOptimist = 0x0;
    firstrun = 1;
    counter1 = millis();
}

void optimistISR()
{
    runOptimist = 0x1;
    runPessimist = 0x0;
    firstrun = 1;
    counter1 = millis();
}

void resetLight()
{
    digitalWrite(mux1, 0);
    digitalWrite(mux2, 0);
    digitalWrite(mux3, 0);
    digitalWrite(mux4, 0);
    analogWrite(dac1, 0);
    analogWrite(dac2, 0);
    analogWrite(dac3, 0);
    
    digitalWrite(ledOpti, 0x0);
    digitalWrite(ledPessi, 0x0);
}

void fadeUp(int dac)
{
    for (i = 0; i <= 255; i++)
    {
        switch (dac)
        {
        case 1:
            analogWrite(dac1, i);
            break;
        case 2:
            analogWrite(dac2, i);
            break;
        case 3:
            analogWrite(dac3, i);
            break;
        }
    }
    return;
}

void fadeDown(int dac)
{
    for (i = 0; i <= 255; i++)
    {
        switch (dac)
        {
        case 1:
            analogWrite(dac1, (i * -1) + 255);
            break;
        case 2:
            analogWrite(dac2, (i * -1) + 255);
            break;
        case 3:
            analogWrite(dac3, (i * -1) + 255);
            break;
        }
    }
}

void lightMeUp()
{
    digitalWrite(mux1, 1);
    digitalWrite(mux2, 1);
    digitalWrite(mux3, 1);
    digitalWrite(mux4, 1);
    analogWrite(dac1, 255);
    analogWrite(dac2, 255);
    analogWrite(dac3, 255);

    digitalWrite(ledOpti, 0x1);
    digitalWrite(ledPessi, 0x1);
}

void standby() {
        uint32_t beginning = millis();

        digitalWrite(mux1, 0); // voll
        digitalWrite(mux2, 0); // leer resetten
        digitalWrite(mux3, 1); // oben
        digitalWrite(mux4, 0); // disable blue mux
        fadeUp(1);
        digitalWrite(ledOpti, 0x1);
        digitalWrite(ledPessi, 0x1);

        while(millis() - beginning <= 10*1000 && !runOptimist && !runPessimist){
            digitalWrite(mux3, 0);
            digitalWrite(ledOpti, 0);
            digitalWrite(ledPessi, 0);
            delay(delayWhileLightshow);
            digitalWrite(mux3, 1);
            digitalWrite(ledOpti, 1);
            digitalWrite(ledPessi, 1);
            delay(delayWhileLightshow);
        }
        resetLight();
}

void serialOpen() {
  Serial.println("hello - optipessi v1 here!");
  Serial.print("runtime: ");
  Serial.print(millis()/1000/60);
  Serial.println("m");
  Serial.println("--------------------");
  Serial.println("My current Settings:");
  Serial.print("stayActive (time to stay active after a button was pressed): ");
  Serial.print(stayActive / 1000);
  Serial.println("s");
  Serial.print("lightShow (time to start the light show after no button was pressed): ");
  Serial.print(lightShow);
  Serial.println("m");
  Serial.println("--------------------");
  Serial.println("Possible Commands:");
  Serial.println("|send|action|");
  Serial.println("| o  |turns of the lights|");
  Serial.println("| d  |turn on all possible lights|");
  Serial.println("| p  |run pessimist|");
  Serial.println("| q  |run optimist");
  Serial.println("| e  |freak out");
  Serial.println("| s  |reprint this message");
  Serial.println("| a  |adjust stayActive to n seconds");
  Serial.println("| l  |adjust lightShow to n minutes");
  Serial.println("| g  |adjust lightShow flash rate in ms");
  Serial.println("--------------------");
  Serial.println("ready");

}
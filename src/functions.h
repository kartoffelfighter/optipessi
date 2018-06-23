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
            delay(10);
            break;
        case 2:
            analogWrite(dac2, i);
            delay(10);
            break;
        case 3:
            analogWrite(dac3, i);
            delay(10);
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
            delay(10);
            break;
        case 2:
            analogWrite(dac2, (i * -1) + 255);
            delay(10);
            break;
        case 3:
            analogWrite(dac3, (i * -1) + 255);
            delay(10);
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
}
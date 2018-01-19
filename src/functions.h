void pessimistISR() {
    runPessimist = 0x1;
    runOptimist = 0;
    firstrun = 1;
    counter1 = millis();
    i = 255;
}

void optimistISR() {
    firstrun = 1;
    runOptimist = 0x1;
    runPessimist = 0;
    i = 255;
}


void resetLight() {
  digitalWrite(mux1, 0);
  digitalWrite(mux2, 0);
  digitalWrite(mux3, 0);
  digitalWrite(mux4, 0);
  analogWrite(dac1, 0);
  analogWrite(dac2, 0);
  analogWrite(dac3, 0);

}

void fadeUp(int dac){
    for (i = 0; i <= 255; i++){
    switch(dac){
        case 1:
        analogWrite(dac1, i);
        delay(10);
        break;
        case 2:
        analogWrite(dac1, i);
        delay(10);
        break;
        case 3:
        analogWrite(dac1, i);
        delay(10);
        break;
    }
 }
}

void fadeDown(int dac){
    for (i = 0; i <= 255; i++){
    switch(dac){
        case 1:
        analogWrite(dac1, (i*-1)+255);
        delay(10);
        break;
        case 2:
        analogWrite(dac1, (i*-1)+255);
        delay(10);
        break;
        case 3:
        analogWrite(dac1, (i*-1)+255);
        delay(10);
        break;
    }
 }
}
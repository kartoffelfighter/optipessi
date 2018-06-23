bool runOptimist = false;        // this bool is set by optimist isr to run optimist code
bool runPessimist = false;         // this bool is set by pessimist isr to run pessimist code

bool firstrun = false;

uint32_t counter1, counter2, counter3;
uint16_t i = 0;

bool activeP = 0;
bool activeO = 0;


uint32_t stayActive = 30000;  // stay active after triggering ISR
uint32_t lightShow =  5; // start light show after inactivity (Minutes)
uint32_t lastRunning = 0;   // counter for last runtime
uint32_t incomingSettings;      // incoming value from serial
uint32_t delayWhileLightshow = 200;  
bool runOptimist = false;        // this bool is set by optimist isr to run optimist code
bool runPessimist = false;         // this bool is set by pessimist isr to run pessimist code

bool firstrun = false;
int counterOpt = 0;       // counter for runtimes of subroutine optimist
int counterPes = 0;       // counter for runtimes of subroutine pessimist

int sleepAfter = 200;       // sleep after x Seconds

uint32_t counter1, counter2, counter3;
int i = 0;

bool active = 0;


int stayActive = 30000;
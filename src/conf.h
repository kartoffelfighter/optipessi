bool runOptimist = false;        // this bool is set by optimist isr to run optimist code
bool runPessimist = false;         // this bool is set by pessimist isr to run pessimist code

int counterOpt = 0;       // counter for runtimes of subroutine optimist
int counterPes = 0;       // counter for runtimes of subroutine pessimist

int sleepAfter = 200;       // sleep after x Seconds
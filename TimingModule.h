#include <sys/time.h>

#ifndef TIMER_H
#define TIMER_H

class TimingModule
{
timeval now;
double t1, t2;
double totalTime;

public:

TimingModule(){
totalTime = 0.0;
}

void StartTimer(){
gettimeofday(&now, NULL);
t1 = now.tv_sec + (now.tv_usec/1000000.0);
}

void EndTimer(){
gettimeofday(&now, NULL);
t2 = now.tv_sec + (now.tv_usec/1000000.0);
}

double GetElapsedTime(){
double elapsed = t2 - t1;
return elapsed;
}

void AccumulateTotalTime(){
totalTime += GetElapsedTime();
}

double GetTotalTime(){
return totalTime;
}

};

#endif

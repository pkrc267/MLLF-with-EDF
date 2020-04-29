#ifndef SCHEDULER
#define SCHEDULER
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
void    mllfScheduler(job **readyqueue, int njob, int hyperperiod, task **taskset, int *no_of_jobs);
#endif

#ifndef GETTERS
#define GETTERS
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"

int getRandomNumber(int lower, int upper,int counterv) ;

static int getGCD(int num1, int num2);

int getHyperperiod(task **taskset, int no_of_tasks);

float getMinimumLaxity(job **ready_queue, int no_of_tasks);

int getMinimumLaxity_procs(job **ready_queue, int no_of_tasks);

int getNextEDFJob(int minimum_deadline_task, job **readyqueue, int ntask);

float getNextArrival(job **readyqueue, float current_time, int ntask, task **taskset);


#endif

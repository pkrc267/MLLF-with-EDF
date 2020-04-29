#ifndef HELPER
#define HELPER
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
void getTasksfromFile(task ***taskset, int *no_of_tasks, int *no_of_jobs, job ***rq, float *util,FILE *fptr);

void calculateTaskParameters(task **taskset, int no_of_tasks);

static void getARJ(task *t);

static void getRRJ(task *t);

#endif


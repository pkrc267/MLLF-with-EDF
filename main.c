#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
#include "helper.h"
#include "getters.h"
#include "scheduler.h"
#include <time.h>

task **taskset = NULL;
job **ready_queue;
static int no_of_tasks = 0,no_of_jobs=0;
FILE *fptr;


int main(int argc,char const *argv[])
{
    fptr = fopen(argv[1], "r");
    srand(time(0));
    float utilization = 0;
    getTasksfromFile(&taskset, &no_of_tasks, &no_of_jobs, &ready_queue, &utilization,fptr);
    int hyperperiod = getHyperperiod(taskset, no_of_tasks);
    printf("\nUtilization : %f\n", utilization);
    if(utilization > 1)
    {
	printf("\nTask set is not schedulable as Utilization beyond 100 percent\n");
	exit(0);
    }	
    printf("\nHyperperiod for the taskset : %d\n", hyperperiod);
    mllfScheduler(ready_queue, no_of_tasks, hyperperiod, taskset, &no_of_jobs);
    calculateTaskParameters(taskset, no_of_tasks);
    return 0;
}

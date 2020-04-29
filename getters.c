#include "helper.h"
#include "dataStructures.h"
#include "getters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include<limits.h>



int getRandomNumber(int lowerbound, int upperbound,int countervalue) 
{ 
   int i; 
   for (i = 0; i < countervalue; i++)
	{ 
		int randomnum = (rand() % 
		(upperbound - lowerbound + 1)) + lowerbound; 
		return randomnum; 
	} 
} 


int getGCD(int a, int b)
{
    if(b == 0)
        return a;
    return getGCD(b, a%b);
}

int getHyperperiod(task **taskset, int no_of_tasks)
{
    int hyperperiod = 1;
    for(int i = 0; i < no_of_tasks; i++)
    {
        task *temp = taskset[i];
        hyperperiod = (hyperperiod * temp->period)/getGCD(hyperperiod, temp->period);
    }
    return hyperperiod;
}

float getMinimumLaxity(job **ready_queue, int no_of_tasks)
{
    float minimum_laxity =  LONG_MAX;
    for(int i = 0; i < no_of_tasks; i++)
    {
        if(ready_queue[i])
        {
            printf("Laxity : %d = %f ", i, ready_queue[i]->slack);
            minimum_laxity = min(minimum_laxity, ready_queue[i]->slack);
        }
    }
    return minimum_laxity;
}

int getMinimumLaxity_procs(job **ready_queue, int no_of_tasks)
{
    float minimum_laxity = getMinimumLaxity(ready_queue, no_of_tasks);
    int *proc_list = (int*)malloc(no_of_tasks * sizeof(int));
    int minimum_deadline = INT_MAX;
    int minimum_laxity_job = -1;
    for(int i = 0, j = 0; i < no_of_tasks; i++)
    {
        if(ready_queue[i] != NULL && ready_queue[i]->slack == minimum_laxity)
        {

            minimum_deadline = min(minimum_deadline, ready_queue[i]->task_ref->deadline);
            if(minimum_deadline == ready_queue[i]->task_ref->deadline)
                minimum_laxity_job = i;
        }
    }
    if(minimum_laxity_job!=-1)
	printf("\nMin laxity job is %d", minimum_laxity_job);
    return minimum_laxity_job;
}



int getNextEDFJob(int minimum_deadline_task, job **readyqueue, int ntask)
{
    int minimum_laxity = INT_MAX;
    int next_edf_index = -1;
    for(int i = 0; i < ntask; i++)
    {
        if(readyqueue[i] && readyqueue[i]->slack > readyqueue[minimum_deadline_task]->slack)
        {
            if (minimum_laxity > readyqueue[i]->task_ref->deadline)
            {
                minimum_laxity = readyqueue[i]->task_ref->deadline;
                next_edf_index = i;
            }
        }
    }
    return next_edf_index;
}

float getNextArrival(job **readyqueue, float current_time, int ntask, task **taskset)
{
    float next_arrival = LONG_MAX;
    for(int i = 0; i < ntask; i++)
    {
        if(readyqueue[i] == NULL)
        {
            float temp = ceilf((float)current_time/taskset[i]->period);
            temp = temp*taskset[i]->period;
            next_arrival = min(next_arrival, temp);
        }
    }
    return next_arrival;
}



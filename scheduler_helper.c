#include "helper.h"
#include "dataStructures.h"
#include "getters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>


task* initializeTaskAttributes(int task_id, float wcet, int period, int deadline,int arrival)
{
    task *temp = (task*)malloc(sizeof(task));
    temp->task_id = task_id;
    temp->wcet = wcet;
    temp->period = period;
    temp->deadline = deadline+arrival;
    temp->job = NULL;
    temp->job_index = 1;
    temp->arrival[0] = arrival;
    temp->next_release_time = period+arrival;
    
    return temp;
}


job* jobInitialization(int jid_j, float wcet_j, int task_id, task *task_ref)
{
   
    job *temp = (job*)malloc(sizeof(job));
    temp->task_id = task_id;
    temp->jid = jid_j;
    int lower = 50, upper = 100, counterv = 1; 
    int randnum;
    float randfact=0;
    randnum=getRandomNumber(lower, upper, counterv);
    randfact=(float)randnum/(float)100;
    wcet_j=randfact*wcet_j;
    temp->aet=wcet_j;
    temp->wcet = wcet_j;
    temp->ret = wcet_j;
    temp->task_ref = task_ref;
    temp->slack = task_ref->deadline - wcet_j;
    return temp;
}


void slackUpdation(job **readyqueue, int ntask, float current_time)
{
    int previous_slack;
    for(int i = 0; i < ntask; i++)
    {
        job *cur_process = readyqueue[i];
        if(cur_process == NULL)
            continue;
        previous_slack = cur_process->slack;
        cur_process->slack = cur_process->task_ref->deadline - current_time - cur_process->ret;
    }
    printf("\n");
}

void arrivalsCheck(job **ready_queue, task **taskset, float current_time, int ntask, int *no_of_jobs)
{
    for(int i = 0; i < ntask; i++)
    {
        if(ready_queue[i] == NULL && taskset[i]->next_release_time <= current_time)
        {

            taskset[i]->next_release_time += taskset[i]->period ;
            taskset[i]->deadline += taskset[i]->period;
            taskset[i]->job_index += 1;
            taskset[i]->arrival[taskset[i]->job_index-1] = current_time;
            job *j = jobInitialization((*no_of_jobs), taskset[i]->wcet,taskset[i]->task_id, taskset[i]);
            *no_of_jobs +=1;
            j->slack -= current_time;
            ready_queue[i] = j;
        }
    }
}






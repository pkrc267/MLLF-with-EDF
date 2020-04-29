#include "helper.h"
#include "dataStructures.h"
#include "getters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>


void mllfScheduler(job **readyqueue, int nproc, int hyperperiod, task **taskset, int *no_of_jobs)
{

    FILE *fptr3 = fopen("mllf_schedule.txt", "w");
    fclose(fptr3);
    int flagpreemp=0;
    float next_decision=0;
    float next_arrival=0;
    float next_completion=0;
    float in_phase_time=0;
    int flaginphase=1;
    float current_time = 0;
    int prev_task_id = -1;
    int cur_task_id = -1;
    int prev_minimum_deadline_task = -1;
    int preemption_count = 0;
    int prev_jid = -1;
    int context_switch_count = 0;
   
    for (int i = 0; i < nproc; i++)
    {
	if(i==nproc-1)
		break;
        if(taskset[i]->arrival[0]!=taskset[i+1]->arrival[0])
	{
		flaginphase=0;
		if(taskset[i]->arrival[0]!=0)
		{
			if(hyperperiod % ((int)taskset[i]->arrival[0]+taskset[i]->period)==0)
				in_phase_time=hyperperiod;
		}
		else
		{
			if(hyperperiod % ((int)taskset[i+1]->arrival[0]+taskset[i+1]->period)==0)
				in_phase_time=hyperperiod;
		}
			
	}
    }
		
    FILE *fptr = fopen("mllf_schedule.txt", "a+");	
    fprintf(fptr, "***MLLF Schedule***\n");
    fclose(fptr);
    if(flaginphase==0 && in_phase_time>0)    
	printf("\nFirst in phase time : %f \n",in_phase_time);
	
    while(current_time < min(3*hyperperiod,in_phase_time+hyperperiod))
    {
	printf("\nScheduler Invocation at time : %f \n",current_time);

        arrivalsCheck(readyqueue, taskset, current_time, nproc, no_of_jobs);
        int minimum_deadline_task = getMinimumLaxity_procs(readyqueue, nproc);
        if(minimum_deadline_task != -1)
        {
            if(prev_minimum_deadline_task != -1 && readyqueue[prev_minimum_deadline_task] && readyqueue[minimum_deadline_task]->slack == readyqueue[prev_minimum_deadline_task]->slack && readyqueue[minimum_deadline_task]->task_ref->deadline > readyqueue[prev_minimum_deadline_task]->task_ref->deadline )
            {
                minimum_deadline_task = prev_minimum_deadline_task;
            }
        }

        int next_least_deadline_task = getNextEDFJob(minimum_deadline_task, readyqueue, nproc);
	FILE *fptr3 = fopen("mllf_schedule.txt", "a+");
	fprintf(fptr3, "\n%f Decision making overhead : %f to %f", current_time, current_time, current_time+0.1);
	fclose(fptr3);
	current_time=current_time+0.1;
	slackUpdation(readyqueue, nproc, current_time);
        if(minimum_deadline_task != -1) 
        {
		
            int cur_jid = readyqueue[minimum_deadline_task]->jid;
	    
            if(prev_jid != -1 && cur_jid != prev_jid && flagpreemp!=1)
            {
                preemption_count++;
		FILE *fptr3 = fopen("mllf_schedule.txt", "a+");
		fprintf(fptr3 ,"\n%f Preemption Overhead: %f %f", current_time, current_time, current_time+0.2);
		fclose(fptr3);
		current_time=current_time+0.2;
		slackUpdation(readyqueue, nproc, current_time);
            }

            prev_jid = cur_jid;
            cur_task_id = readyqueue[minimum_deadline_task]->task_id;
            FILE *fptr3= fopen("mllf_schedule.txt", "a+");
            fprintf(fptr3, "\n%f Job executing: J%d-%d", current_time, cur_task_id+1, taskset[cur_task_id]->job_index);
            fclose(fptr3);
            float deadline_diff;
	    if(next_least_deadline_task != -1)
            	printf("next edf is task : %d\n", next_least_deadline_task);
            if(next_least_deadline_task != -1)
                deadline_diff = readyqueue[next_least_deadline_task]->slack - readyqueue[minimum_deadline_task]->slack;
            else deadline_diff = 1<<30;
            next_completion = readyqueue[minimum_deadline_task]->ret;
            next_arrival = getNextArrival(readyqueue, current_time, nproc, taskset) -current_time;
            printf("next completion %f", next_completion+current_time);
            printf(" next arrival %f \n", next_arrival+current_time);

            next_decision = min(deadline_diff, min(next_completion, next_arrival));
	    readyqueue[minimum_deadline_task]->ret -= next_decision;

                current_time += next_decision;
            printf("next decision pt: %f ", next_decision);
            if(readyqueue[minimum_deadline_task]->ret == 0) 
	    {
                printf(" Deleting  %d from queue ", minimum_deadline_task);

                int job_index = taskset[cur_task_id]->job_index;
                taskset[cur_task_id]->response_time[job_index-1] = current_time - taskset[cur_task_id]->arrival[job_index-1];
                FILE *fptr3 = fopen("mllf_schedule.txt", "a+");
                fprintf(fptr3, "\nJ%d-%d Completed Actual Execution time %f\n", cur_task_id+1, taskset[cur_task_id]->job_index,readyqueue[minimum_deadline_task]->wcet);
                fclose(fptr3);
                readyqueue[minimum_deadline_task] = NULL;
                context_switch_count++;
		flagpreemp=1;

            }
            else
	    {
			flagpreemp=0;
	    }
        }
        else 
	{
            FILE *fptr3 = fopen("mllf_schedule.txt", "a+");
            fprintf(fptr3, "\n%f Job executing: IDLE", current_time);
            fclose(fptr3);
            next_arrival = getNextArrival(readyqueue, current_time, nproc, taskset) -current_time;
            current_time=current_time+next_arrival;
        }

        prev_task_id = cur_task_id;
        slackUpdation(readyqueue, nproc, current_time);
        prev_minimum_deadline_task = minimum_deadline_task;
    }
    FILE *fptr2 = fopen("schedule_analysis.txt", "w");
    fprintf(fptr2, "Preemptions : %d Context Switches : %d\n", preemption_count, context_switch_count);
    fclose(fptr2);
}


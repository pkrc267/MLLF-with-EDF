#include "helper.h"
#include "getters.h"
#include "dataStructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include<limits.h>


void getTasksfromFile(task ***taskset, int *no_of_tasks, int *no_of_jobs, job ***rq, float *utilization,FILE *fptr)
{
    
    int period, deadline;
    float wcet;
    float arrival;
    int task_no = 0;
    int process_count;
    fscanf(fptr,"%d", &process_count);
    printf("Total Tasks : %d\n", process_count);
    task **tasks = (task**)malloc(process_count * sizeof(task*));
    job **ready_queue = (job **)malloc(process_count * sizeof(job*));
    printf("\nTask Set\n");
    printf("\nArrival,WCET, Period, Deadline\n");
    while(fscanf(fptr, "%f, %f, %d, %d",&arrival, &wcet, &period, &deadline) == 4)
    {
        printf("%f, %f, %d, %d\n",arrival,wcet, period, deadline);
        task *task = initializeTaskAttributes((*no_of_tasks)++, wcet, period, deadline,arrival);
	job *j = jobInitialization((*no_of_jobs)++, wcet, (*no_of_tasks)-1, task);
        task->job = j;
        tasks[(*no_of_tasks)-1] = task;
        ready_queue[(*no_of_tasks)-1] = j;
        *utilization += (float)wcet/(float)period;
    }
    fclose(fptr);
    *taskset = tasks;
    *rq = ready_queue;
}



static void getARJ(task *task)
{
    float max_response_time = task->wcet;
    float min_response_time = INT_MAX;
    float *response_time = task->response_time;
    for(int i = 0; i < task->job_index; i++)
    {
        if(max_response_time < response_time[i])
            max_response_time = response_time[i];
        if(min_response_time > response_time[i])
            min_response_time = response_time[i];
    }
    FILE *fptr2 = fopen("schedule_analysis.txt", "a+");
    fprintf(fptr2, "Task : %d ARJ : %f\n", task->task_id, max_response_time - min_response_time);
    fclose(fptr2);
}

static void getRRJ(task *task)
{
    float *response_time = task->response_time;
    float response_diff=0;
    float max_jitter=0;
     max_jitter= fabs(response_time[0] - response_time[task->job_index - 1]);
    for(int i = 0; i < task->job_index - 1; i++)
    {
        response_diff = fabs(response_time[i]-response_time[i+1]);
        max_jitter = max_jitter < response_diff ? response_diff: max_jitter;
    }
    FILE *fptr2= fopen("schedule_analysis.txt", "a+");
    fprintf(fptr2, "Task : %d RRJ : %f\n", task->task_id, max_jitter);
    fclose(fptr2);
}



void calculateTaskParameters(task **taskset, int no_of_tasks)
{
    for(int i = 0; i < no_of_tasks; i++)
     {
        getARJ(taskset[i]);
        getRRJ(taskset[i]);
    }
}

#ifndef __DS_H_
#define __DS_H_

#define min(n1,n2) (n1<n2?n1:n2)

typedef struct job job;
typedef struct _task task;
struct _task{
    int task_id;
    float wcet;
    int period;
    int deadline;
    int next_release_time;
    int job_index;
    float arrival[100];
    float response_time[100];
    job *job;
    
};


struct job{
    int jid;
    int task_id;
    float wcet;
    float ret;
    float slack;
    float aet;
    task *task_ref;
};



job* jobInitialization(int jid_j, float wcet_j, int task_id, task *task_ref);
task*
initializeTaskAttributes(int task_id, float wcet, int period, int deadline,int arrival);
void    slackUpdation(job **readyqueue, int ntask, float current_time);
void    arrivalsCheck(job **ready_queue, task **taskset, float current_time, int ntask, int *no_of_jobs);

#endif

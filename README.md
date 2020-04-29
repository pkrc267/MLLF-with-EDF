# MLLF-with-EDF
-----------------------------------------------------------------

## Directory structure:
├── README.txt<br>
├── dataStructures.h<br>
├── getters.c<br>
├── getters.h<br>
├── helper.c<br>
├── helper.h<br>
├── main.c<br>
├── makefile<br>
├── mllf<br>
├── mllf_schedule.txt<br>
├── schedule_analysis.txt<br>
├── scheduler.c<br>
├── scheduler.h<br>
├── scheduler_helper.c<br>
└── taskset.txt<br>

-----------------------------------------------------------------

## Instructions to compile:

* navigate to the project directory and type command<br>
    &nbsp;```make```
* this generates executable named 'mllf'
* feed input file as a paramenter while executing the output file<br>
    &nbsp;```./mllf taskset.txt```

* this generates two text files as described below:

*  required schedule is available in file<br>
    >_mllf_schedule.txt_

* parameters can be viewed in file<br>
    > _schedule_analysis.txt_

-----------------------------------------------------------------

Input file is organised as follows:
    
    No of tasks
    Arrival,WCET,period,deadline

-----------------------------------------------------------------

## What has been tried:
(in order mentioned below)

* taskset read
* utilization calculated
* hyper-period calculated
* job-list created
* scheduling performed
* parameter calculations: Absolute Response Jitter, Relative Response Jitter

-----------------------------------------------------------------

## What works:

* hyper-period computation
* utilization computation
* scheduling

## What does not work:

* scheduler not getting invoked when out-of-phase job get's released

-----------------------------------------------------------------

## What approach?

* instead of making a queue of ready jobs, we have tried to simulate the same using:
---- getNextEDFJob()
---- getNextArrival()
 functions in getters.c file.

* job's arrival is checked while on the run, instead of making a list of jobs before hand; and admitted accordingly.

-----------------------------------------------------------------

## Function description:

> scheduler.c<br><br>


**void mllfScheduler()** : It schedules the taskset read and writes it to the mllf_schedule.txt.
                       It calculates number of preemptions and context switches to the schedule_analysis.txt.<br>
                       <br>


> scheduler_helper.c<br><br>

__task* initializeTaskAttributes()__ : ionitializes the tasks and makes a taskset<br><br>

__job* jobInitialization()__ : initializes parameters of the job that arrives in the system<br><br>

**void slackUpdation()** : updates slack time of the ready jobs<br><br>

**arrivalsCheck()**: it adds job that arrives at or before the current time<br><br>

> getters.c<br><br>

**int getRandomNumber()** : It generates random number between given lower_bound and upper_bound. (between 50 to 100)<br><br>
 
**int getGCD()** : It returns Greatest Common Divisor(GCD) of two numbers.<br><br>

**int getHyperperiod()** : It returns Hyper-Period of the taskset read.<br><br>

**float getMinimumLaxity()** : It returns minimum laxity/slack value of the job from the ready queue.<br><br>

**int getMinimumLaxity_procs()** : It returns minimum laxity/slack value job index.<br><br>

**int getNextEDFJob()**: It returns index of job having least deadline.<br><br>

**float getNextArrival()** : It returns the next arrival time of the task i.e. when a new job arrives.<br><br>

> helper.c<br><br>

**void getTasksfromFile()** : It reads taskset from the taskset.txt file.
                          It also initializes task as well as job.<br><br>
 
**static void getARJ()** : It calculates and writes Absolute Response Jitter time in schedule_analysis.txt.<br><br>

**static void getRRJ()** : It writes Relative Response Jitter time in schedule_analysis.txt.<br><br>
 
**void calculateTaskParameters()** : It calls static void getARJ() and getRRJ().   <br><br>

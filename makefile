all:
	gcc -g main.c getters.c helper.c scheduler.c scheduler_helper.c -lm -o mllf

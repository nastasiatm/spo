#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define SHMSZ 4

struct ids {
	pid_t pid;
	uid_t p_uid;
	uid_t p_gid;
};

int main(int argc, char * argv[]) {
	struct ids process;
	key_t key; /*Name of shared memory segment*/
	int shmid;
	time_t timer, stime;
	double load[3];
	double *shm, *data;
	
	stime = time(NULL);
	process.pid = getpid();
	process.p_uid = getuid();
	process.p_gid = getgid();
	key = 666;

	/*Create the segment*/
    	if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        	perror(strerror(errno));
        	exit(1);
    	}

	/*Attach the segment to data space*/
    	if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
        	perror(strerror(errno));
        	exit(1);
    	}

    	/*Put some things into the memory for the other process to read*/

	for(;;) {
		if (getloadavg(load, 3) < 0) {
			perror(strerror(errno));
			exit(1);	
		}
		else {
			double t;
			data = shm;
			printf("Load average:\t1m - %f\t5m - %f\t15m - %f\t\n", load[0], load[1], load[2]);
			*data++ = load[0];
			*data++ = load[1];
			*data++ = load[2];
			timer = time(NULL);
			t = difftime(timer, stime);
			*data++ = t;
			*data = NULL;
			printf("Time:\t%.0f\n", t);
		}
		sleep(1);
	}

}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <time.h>

struct ids {
	pid_t pid;
	uid_t p_uid, p_gid;
	double load[3], t;
};

int main(int argc, char * argv[]) {
	size_t size;
	struct ids process;
	key_t key; /*Name of shared memory segment*/
	int shmid;
	time_t timer, stime;
	double *shm;
	double load[3], t;
	
	size = sizeof(process);
	
	struct ids *data;
	
	stime = time(NULL);
	process.pid = getpid();
	process.p_uid = getuid();
	process.p_gid = getgid();
	key = 6666;

	/*Create the segment*/
    if ((shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666)) < 0) {	
		shmid = shmget(key, size, 0666);
		shmctl(shmid, IPC_RMID, NULL);
		if ((shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666)) < 0) {
			perror(strerror(errno));
			exit(1);
		}       	
    }

	/*Attach the segment to data space*/
    	if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
        	perror(strerror(errno));
        	exit(1);
    	}

    	/*Put some things into the memory for the other process to read*/
				
		printf("PID %d\tP_UID %d\tP_GID %d\t\n", process.pid, process.p_uid, process.p_gid);
		data = (struct ids *) shm;
		data->pid = process.pid;
		data->p_uid = process.p_uid;
		data->p_gid = process.p_gid;
		
	for(;;) {
		if (getloadavg(data->load, 3) < 0) {
			perror(strerror(errno));
			exit(1);	
		}
		else {
			printf("Load average:\t1m - %f\t5m - %f\t15m - %f\t\n", data->load[0], data->load[1], data->load[2]);
			timer = time(NULL);
			t = difftime(timer, stime);
			data->t = t;
			printf("Time:\t%.0f\n", t);
			/*(*data).*/
		}
		sleep(1);
	}
	

}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

struct ids {
	pid_t pid;
	uid_t p_uid, p_gid;
	double load[3], t;
};

int main(int argc, char * argv[]) {
    int shmid;
    key_t key;
    double *shm;
	struct ids transfer;
	struct ids *data;
	size_t size;
	
	size = sizeof(transfer);

    /*We need to get the segment named "6666", created by the server*/
    key = 6666;

    /*Locate the segment*/
    if ((shmid = shmget(key, size, 0666)) < 0) {
        perror(strerror(errno));
        exit(1);
    }

	if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
        	perror(strerror(errno));
        	exit(1);
	}

	/*Read what the server put in the memory*/
	data = (struct ids *)shm;
   	
	printf("PID: %d\t", data->pid);
	printf("P_UID: %d\t", data->p_uid);
	printf("P_GID: %d\t\n", data->p_gid);
	
	printf("Load average:\t1m - %f\t", data->load[0]);
	printf("5m - %f\t", data->load[1]);
	printf("15m - %f\t\n", data->load[2]);
	printf("Time:\t%.0f\n", data->t);


    return 0;
}

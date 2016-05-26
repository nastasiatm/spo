#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define SHMSZ 4

int main(int argc, char * argv[]) {
    int shmid;
    key_t key;
    double *shm, *data;
    int c;

    /*We need to get the segment named "666", created by the server*/
    key = 666;

    /*Locate the segment*/
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror(strerror(errno));
        exit(1);
    }


    if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
            perror(strerror(errno));
            exit(1);
    }

    /*Read what the server put in the memory*/
    data = shm;
    for (c = 0; c < 3; c++) {
            printf("%f\n", *data++);
    }
        printf("%.0f\n", *data++);



    return 0;
}

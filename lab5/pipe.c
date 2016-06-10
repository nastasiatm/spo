#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

char buf[4096], buf2[2048];

int main(int argc, char * argv[]) {
	int fildes[2], n, t;
	pid_t childpid;
	FILE *writeToChild, *dfile;
	
	pipe(fildes);


	if ((childpid = fork()) == -1) {
		perror("fork");
		exit(1);
	}

	if (childpid == 0) {
		close(fildes[1]);
		dup2(fildes[0], 0);
		close(fildes[0]);
		execl("/usr/bin/wc", "wc", (char *)0);
		fprintf(stderr, "Error execl");
	}
	else {
		int i, j;
		close(fildes[0]);
		dfile = fopen(argv[1], "r");

		writeToChild = fdopen(fildes[1], "w");

		if ((writeToChild != NULL) && (dfile !=  NULL)) {
				while (((n = fread(buf, 1, 4096, dfile)) > 0)) {
					for (i = 0, j = 0; i < 4096; i += 2, j++) {
						buf2[j] = buf[i]; // :P
					}
					if ((fwrite(buf2, 1, n/2, writeToChild)) == -1) {
						perror("fwrite");
						exit(1);
					}
				}
				if (n == -1) {
					perror("fread");
					exit(1);
				}
		}
		fclose(dfile);
		fclose(writeToChild);
	}
	int st;
	wait(&st);
	return 0;
}

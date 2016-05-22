#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/uio.h>

#define BUF_SIZE 4096

int readFile(int file) {
	char buf[BUF_SIZE];
	int n, t;
	while (((n = read(file, buf, BUF_SIZE)) > 0) || (n == -1)) {
		if (n < 0) {
			return 1;
		}
       	t = write(1, buf, n);
        if (t < 0) {
	        return 1;
        }
    }
}

/* 1st variant of errors, need to separately write "\n" (writeStderr("\n")) */
/*int writeStderr(char *p) {
	int l;
	char buf[1];
	l = strlen(p);
	if (write(2, p, l) < 0) {
		return 1;
	}
	return 0;
}*/

/* 2nd variant of errors with vector */
int writeStderr(char *p) {
     	static char part2[] = "\n";
     	struct iovec iov[] = {{p, strlen(p)}, {part2, strlen(part2)}};

     	/* 2nd variant of struct's values
	
	iov[0].iov_base = p;
     	iov[0].iov_len = strlen(p);

     	iov[1].iov_base = part2;
     	iov[1].iov_len = strlen(part2);*/

     	if (writev(2, iov, 2) < 0) {
		return 1;
	}

     	return 0;
}

int main(int argc, char * argv[]) {
	int file;
    int i;
	if (argc == 1) {
		if (readFile(0)) {
				char *p = strerror(errno);
                		writeStderr(p);
				/*writeStderr("\n");*/
				return 1;    		
            }
	}
    for ( i = 1; i < argc; i++) {
        if ( strcmp(argv[i], "-" ) == 0 ) {
			if (readFile(0)) {
				char *p = strerror(errno);
                		writeStderr(p);
				continue;    		
            }
        }
        else {
            file = open(argv[i], O_RDONLY | O_LARGEFILE);
            if (file == -1) {
				char *p = strerror(errno);
                		writeStderr(p);
				continue; 
            }
            if ( readFile(file) ) {
		char *p = strerror(errno);
                writeStderr(p);
		continue;
            }
        }
    }
    return 0;
}

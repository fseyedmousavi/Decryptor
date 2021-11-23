#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd1;
	char * myfifo = "/tmp/myfifo";
	char str1[80];
	
    	mkfifo(myfifo, 0666);

        //open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 80);
        close(fd1);

	printf("Hello. I am decoder.\n");
    	printf("str1: %s\n", str1);
	sleep(1);
	return 0;
}


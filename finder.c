#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd2;
	char * myfifo = "/tmp/myfifo";
	char str2[80];  //get this from main
	
    	mkfifo(myfifo, 0666);
        fd2 = open(myfifo,O_RDONLY);
        read(fd2, str2, 80);
        close(fd2);

	printf("Hello. I am finder.\n");
	printf("str2: %s\n", str2);
	
	int fd;
	char * myfifo2 = "/tmp/myfifo2";
	char str_edited[80];  //get this from decoder
	
    	mkfifo(myfifo2, 0666);
        fd = open(myfifo2,O_RDONLY);
        read(fd, str_edited, 80);
        close(fd);

	printf("str: %s\n", str_edited);
	
	strcat(str_edited, "2");
	
	fd = open(myfifo2,O_WRONLY);
        write(fd, str_edited, 80);
        close(fd);	
	
	sleep(1);
	return 0;
}


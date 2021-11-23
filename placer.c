#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd3;
	char * myfifo = "/tmp/myfifo";
	char str3[80];  //get this from main
	
    	mkfifo(myfifo, 0666);
        fd3 = open(myfifo,O_RDONLY);
        read(fd3, str3, 80);
        close(fd3);

	printf("Hello. I am placer.\n");
	printf("str3: %s", str3);
	
	int fd;
	char * myfifo2 = "/tmp/myfifo2";
	char str_edited[80];  //get this from finder
	
    	mkfifo(myfifo2, 0666);
        fd = open(myfifo2,O_RDONLY);
        read(fd, str_edited, 80);
        close(fd);

	printf("str: %s\n", str_edited);
	
	sleep(1);
	return 0;
}


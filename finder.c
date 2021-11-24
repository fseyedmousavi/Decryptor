#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define n 100
int main(){

	int fd2;
	char * myfifo = "/tmp/myfifo";
	char str2[n];  //get this from main
	
    	mkfifo(myfifo, 0666);
        fd2 = open(myfifo,O_RDONLY);
        read(fd2, str2, n);
        close(fd2);

	int fd;
	char * myfifo2 = "/tmp/myfifo2";
	char str_edited[n];  //get this from decoder
	
    	mkfifo(myfifo2, 0666);
        fd = open(myfifo2,O_RDONLY);
        read(fd, str_edited, n);
        close(fd);
	
	int i = 0;

	char output[strlen(str_edited)];
	strcpy(output, "");
	
	while(i < strlen(str2)){
		char ind[3];
		int j = 0;
		int index;
		while(str2[i]!=' ' && i < strlen(str2)) {
			ind[j]=str2[i];
			i++;
			j++;
		}
		index = atoi(ind);
		
		i++;
		char len[10];
		j = 0;
		int length;
		while(str2[i] != '$' && i < strlen(str2)){
			len[j]=str2[i];
			i++;
			j++;
		}
		length = atoi(len);

		i++;
			
		char temp[10]={};
		strncpy(temp, str_edited + index, length);
		char *c = "&";
		strncat(temp, c, 1);
		
		strncat(output, temp, length+1);
	}
	FILE * file;
    	file = fopen("./finder_output.txt", "w");
	
   	 if(file == NULL) {
        	printf("finder was unable to create file.\n");
        	exit(EXIT_FAILURE);
    	}

    	fputs(output, file);

	fclose(file);
	
	fd = open(myfifo2,O_WRONLY);
        write(fd, output, n);
        close(fd);

	
	
	sleep(1);
	return 0;
}


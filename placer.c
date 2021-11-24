#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	int fd3;
	char * myfifo = "/tmp/myfifo";
	char str3[80];  //get this from main
	
    	mkfifo(myfifo, 0666);
        fd3 = open(myfifo,O_RDONLY);
        read(fd3, str3, 80);
        close(fd3);
	
	int fd;
	char * myfifo2 = "/tmp/myfifo2";
	char str_edited[80];  //get this from finder
	
	
    	mkfifo(myfifo2, 0666);
        fd = open(myfifo2,O_RDONLY);
        read(fd, str_edited, 80);
        close(fd);
	
	char output[strlen(str3)+strlen(str_edited)];
	strcpy(output,"");
	int i = 0; //moves on str3
	int k = 0; //moves on str_edited
	while (i < strlen(str3)){
		if (str3[i] == '$'){
		
			int length = 0;
			while (str_edited[k+length]!='&')
				length++;
			
			char temp[10]={};
			strncpy(temp, str_edited + k, length);
			strncat(output, temp, length);
			
			k+=length+1;
			
		} else
			strncat(output, &str3[i], 1);
		i++;
		
	}
	printf("\n%s" , output);
	FILE *placer_output = fopen("placer_output.txt", "w");
	int results = fputs(output, placer_output);
	if (results == EOF){
		//File not created hence exit
        	printf("placer was unable to create file.\n");
        	exit(EXIT_FAILURE);
	}
	
	fclose(placer_output);
	sleep(1);
	return 0;
}


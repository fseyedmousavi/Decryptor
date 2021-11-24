#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

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
	
	int i = 0;

	int output_len = 1;
	char* output = malloc(sizeof(char));
	if (output == NULL){
		//failed to allocate the memory
	}
	
	while(str2[i]!='\0'){
		char ind[2];
		int j = 0;
		int index;
		while(str2[i]!=' ') {
			ind[j]=str2[i];
			i++;
			j++;
		}
		index = atoi(ind);
		
		i++;
		char len[2];
		j = 0;
		int length;
		while(str2[i]!='$'){
			len[j]=str2[i];
			i++;
			j++;
		}
		length = atoi(len);
		i++;
		//resize output for next string and & to seperate them
		output_len += (length + 1);
		output = realloc(output, output_len * sizeof(char));
		memcpy(output, &str2[index], str2[index+length]);
		strcat(output, "&");
	}
	printf("OUTPUT:%s\n",output);
	FILE *finder_output = fopen("finder_output.txt", "w");
	int results = fputs(output, finder_output);
	if (results == EOF){
		//failed to write error
	}
	
	strcat(str_edited, "2");
	
	fd = open(myfifo2,O_WRONLY);
        write(fd, str_edited, 80);
        close(fd);	
	free(output);
	fclose(finder_output);
	
	sleep(1);
	return 0;
}


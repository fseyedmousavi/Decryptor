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
	
	char output[strlen(str3)+strlen(str_edited)];
	int i = -1;
	int j = 0; //moves on output
	int k = 0; //moves on str_edited
	while (str3 != '\0'){
		i++;
		if (str3[i] == '$'){
			while (str_edited[k]!='&'||str_edited[k]!='\0'){
				strcat(output, &str_edited[k]);
				i++;
			}
			
		} else {
			output[j]=str3[i];
			j++;
		}
		
	}
	FILE *placer_output = fopen("placer_output.txt", "w");
	int results = fputs(output, placer_output);
	if (results == EOF){
		//failed to write error
	}
	
	fclose(placer_output);
	sleep(1);
	return 0;
}


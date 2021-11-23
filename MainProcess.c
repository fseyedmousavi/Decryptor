#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
	char str [400];
	char str1[200], str2[100], str3[100];
	int i, j;
	int fd;
    	char * myfifo = "/tmp/myfifo"; 

	printf("please enter the encrypted text:\n");
	fgets(str, 400, stdin);

	for(i=0 ; i < 400 ; i++){
		if(str[i]=='#'){
	    		strncpy(str1, &str[0],i);
    			str1[i] = '\0';
    			
   			// Creating the named file(FIFO)
   			// mkfifo(<pathname>, <permission>)
    			mkfifo(myfifo, 0666);
    	
        		// Open FIFO for write only
        		fd = open(myfifo, O_WRONLY);
	
        		write(fd, str1, strlen(str1)+1);
        		close(fd);
    			break;
		}
	}
	i+=3;
	for(j = i ; j < 400 ; j++){
		if(str[j]=='#'){
    			strncpy(str2, &str[i],j);
    			str2[j-i] = '\0';
    			break;
		}
	}
	j+=3;
	if (strlen(str)!=0) {
		strncpy(str3, &str[j], 400);
		str3[400-j] = '\0';
	}
	
	int decoder, finder, placer;
	decoder = fork();
	
	if (decoder == 0) {
		char *args[]={"decoder", "c", "programs" ,NULL};
        	execvp("./decoder",args);
        	sleep(1);
	} else {
		sleep(1);
		finder = fork();
		if (finder == 0) {
			char *args[]={"finder", "c", "programs" ,NULL};
        		execvp("./finder",args);
		} else {
			sleep(1);
			placer = fork();
			if (placer == 0) {
				char *args[]={"placer", "c", "programs" ,NULL};
        			execvp("./placer",args);
			} else {
				sleep(1);
			}
		}
	}
    

	return 0;
}


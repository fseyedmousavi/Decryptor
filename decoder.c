#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
	int fd1;
	char * myfifo = "/tmp/myfifo";
	char str1[200];  //get this from main
	
    	mkfifo(myfifo, 0666);

        //open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 200);
        
        close(fd1);

    	char decrypted_str1[strlen(str1)];
    	
    	for(int i=0;i< strlen(str1);i++){
    		if(str1[i]<'C'){
    			if(str1[i]=='A'){
    				decrypted_str1[i]='X';
    			}else if(str1[i]=='B'){
    				decrypted_str1[i]='Y';
    			}else if(str1[i]=='C'){
    				decrypted_str1[i]='Z';
    			}
    		}else if(str1[i]<'c'){
    	    		if(str1[i]=='a'){
    				decrypted_str1[i]='x';
    			}else if(str1[i]=='b'){
    				decrypted_str1[i]='y';
    			}else if(str1[i]=='c'){
    				decrypted_str1[i]='z';
    			}
    		}else{
    			decrypted_str1[i]=str1[i]-3;
    		}
    	
    	}
    	
    	//File pointer to hold reference to our file
    	FILE * file;

    	//Open file in w (write) mode. 
    	file = fopen("./decoder_output.txt", "w");
	
   	 if(file == NULL) {
        	//File not created hence exit
        	printf("Unable to create file.\n");
        	exit(EXIT_FAILURE);
    	}

	//Write data to file
    	fputs(decrypted_str1, file);

	fclose(file);
    
    	
    	int fd;
	char * myfifo2 = "/tmp/myfifo2";

    	mkfifo(myfifo2, 0666);
        fd = open(myfifo2,O_WRONLY);
        write(fd, decrypted_str1, strlen(decrypted_str1)+1);
        close(fd1);
        
	sleep(1);
	return 0;
}


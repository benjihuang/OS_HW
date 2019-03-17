#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <fcntl.h> 

int main (int argc, char *argv[]) {


    int pipeFds[2]; 
    int fileBytesLength;
    char buffer[100];
    char childBuffer[100];
    
    if (argc != 3) {
      perror("Filecopy: filecopy.exe [target] [destination]. \n");
      exit(1);
    }
    
    char* input = argv[1];
    char* copy = argv[2];

    if (pipe(pipeFds) < 0) {
      printf("Something went wrong creating the pipe! %s\n", strerror(errno));
      exit(1);
    }
    if(fork() == -1){
		printf("Error forking child process. %s\n", strerror(errno));
        exit(1);
	}
	else if(fork() == 0){
		close(pipeFds[1]);                                                        
        ssize_t num_bytes_child = read(pipeFds[0], childBuffer, sizeof(childBuffer));  
        close(pipeFds[0]);                                                        

        int targetDesc = open(copy, O_CREAT | O_WRONLY);                             
        write(targetDesc, childBuffer, num_bytes_child); 
	}
	else{
		close(pipeFds[0]);                                              
        int fileInDesc = open(input, O_RDONLY);                       
        ssize_t num_bytes = read(fileInDesc, buffer, sizeof(buffer));   
        write(pipeFds[1], buffer, num_bytes);                           
        close(pipeFds[1]);                                              
	}
    

    return 0;
}

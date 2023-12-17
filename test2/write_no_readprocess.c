#include <stdio.h>    
#include <unistd.h>    
#include <signal.h>
#include <errno.h>    
     
void Handler(int sig) {                                                                                                     
    printf("Received signal: %d\n", sig);   
}    
     
int main() {
    signal(SIGPIPE, Handler);    
     
    int pipefd[2];    
    if(pipe(pipefd) < 0) {    
        perror("pipe error");    
        return -1;    
    }    
     
    int pid = fork();    
    if(pid < 0 ) {    
        perror("fork error");    
        return -1;    
    }    
    else if(pid == 0) {    
        close(pipefd[0]); 
    }    
    else {    
        close(pipefd[0]);
        sleep(1);   
        int ret = write(pipefd[1], "Hello pipe", 10);    
        if(ret == -1) {   
            perror("write error");
        }    
    }    
 
    return 0;
} 


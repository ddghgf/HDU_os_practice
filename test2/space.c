#include <stdio.h>    
#include <unistd.h>    
     
int main() {    
    int pipefd[2];    
    if(pipe(pipefd) < 0) {    
        perror("pipe error");    
        return -1;    
    }    
     
    int count = 0;    
    while(1) {    
        write(pipefd[1], "a", 1);    
        count++;   
        printf("count：%d\n", count);    
    }    
     
    return 0;    
}


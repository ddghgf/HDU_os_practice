#include <stdio.h>
#include <unistd.h>

int main() {
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
        write(pipefd[1], "Hello", 5);
    }
    else {
        char buf[5];
 while(1) {
            int n = read(pipefd[0], buf, 5);
            printf("n: %d\n", n);
            if(n == 0) {
                break;
            }
        }
    }

    return 0;
}



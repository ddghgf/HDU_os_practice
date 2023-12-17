#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
sem_t *parent_send;
sem_t *child_receive;
sem_t *mutex;
int main(){
        pid_t pid;
        int  shm_id,x;
        char *shm_addr;
        char buff [256];
        parent_send=sem_open("parent_send",O_CREAT,0666,0);
        child_receive=sem_open("child_receive",O_CREAT,0666,0);
        mutex=sem_open("mutex",O_CREAT,0666,1);
        shm_id=shmget(IPC_PRIVATE,256,0666);
 if(shm_id<0){
                perror("shmget error");
                exit(1);
        }
        pid=fork();
        if(pid<0){
                perror("fork error");
                exit(1);
        }
        else if(pid==0){
                       // sleep(1);
                        shm_addr=shmat(shm_id,NULL,0);
                        sem_wait(mutex);
                        sem_wait(parent_send);
                        strcpy(buff,shm_addr);
                        printf("child receive:%s",buff );
                        strcpy(shm_addr,"over");
                        printf("child send over\n");
                        sem_post(mutex);
                        sem_post(child_receive);
                        shmdt(shm_addr);
                        shmctl(shm_id,IPC_RMID,NULL);
                }
        else {
                sem_wait(mutex);
                printf("parent send:");
                shm_addr=shmat(shm_id,(void *)0,0);
                fgets(buff,256,stdin);
                strncpy(shm_addr,buff,strlen(buff));
                sem_post(mutex);
                sem_post(parent_send);
                sem_wait(child_receive);
                strcpy(buff,shm_addr);
                printf("parent receive: %s\n",buff);
                shmdt(shm_addr);
                shmctl(shm_id,IPC_RMID,NULL);
                }
        return 0;
}



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
static void childpro( char *cmd, char *argv[],char *env[]){
        int pid=fork();
        if(pid<0){
                printf("fork err\n");
        }
        else if(pid==0){
                execve(cmd,argv,env);

        }
}

int main(int argc,char *argv[],char *env[]){
        char cmd[10];
        while(1){
                scanf("%s",cmd);
                if(strcmp(cmd,"exit")==0){
                        break;
                }
                else if(strcmp(cmd,"cmd1")==0){
   childpro("cmd1",argv,env);
                }
               else if(strcmp(cmd,"cmd2")==0){
                        childpro("cmd2",argv,env);

                }
               else if(strcmp(cmd,"cmd3")==0){
                        childpro("cmd3",argv,env);
                }
                else{
                        printf("invalid commond\n");
                        continue;
                }
        }
}


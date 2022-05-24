#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int status = 0;
    int wpid;
    char *argv[2];
    argv[0] = "./create";
    argv[1] = NULL;
    char *arr[2];
    arr[0] = "./copy";
    arr[1] = NULL;
    int first_child = fork();
    if (first_child == 0){
        printf("Successfully forked first child process.\n");
        if((execv(argv[0], argv)) < 0){
           printf("Error. Failed to execute command for process_p1\n.");
        }
        else{
            printf("Executing process_p1\n");
        }
    }
    else if(first_child < 0){
         printf("Creation of first child process unsuccessful\n");
    }
    else{
        waitpid(first_child, &status, 0);
        int second_child = fork();
        if(second_child == 0){
            printf("Successfully forked second child process.\n");
            if((execv(arr[0], arr)) < 0){
                printf("Error. Failed to execute command for process_p2.\n");
            }
            else{
                printf("Executing process_p2\n");
            }
        }
        else if(second_child < 0){
        printf("Creation of second child process unsuccessful\n");
        }
        else{
           wpid = wait(&status);
           if (status == 0){
               printf("The child processes terminated successfully.\n");    
           }
           else{
               printf("The child processes terminated with error.\n");    
           } 
        }
    }
    return 0;  
}
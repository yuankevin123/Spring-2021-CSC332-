#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int status = 0;
    int wpid;
    int first_child = fork();
    if (first_child == 0){
        printf("I am first child, my pid is %d\n", getpid());
    }
    else if(first_child < 0){
         printf("Creation of first child process unsuccessful");
    }
    else{
        int second_child = fork();
        if(second_child == 0){
            printf("I am second child, my pid is %d\n", getpid());
        }
        else if(first_child < 0){
         printf("Creation of second child process unsuccessful");
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
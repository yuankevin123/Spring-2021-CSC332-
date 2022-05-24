#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    char *argv[3];
    int pid, status;
    int child = fork();

    if (child == 0){
        printf("\nSuccessfully forked the child process. Its PID = %d \n", getpid());
        argv[0] = "ls";
        argv[1] = "-la";
        argv[2] = NULL;
        printf("\n");
        if (execvp(argv[0], argv) < 0){
            printf("Error. Failed to execute command.");
        }
        else{
            printf("Displaying all files in directory and their information:\n");
        }
    }
    else if(child < 0){
        printf("Error in forking the child process.\n");
    }
    else{
        waitpid(child, &status, 0);
    }
    return 0;
}
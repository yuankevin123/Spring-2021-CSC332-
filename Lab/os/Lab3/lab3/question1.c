#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    int pid, status;
    int child = fork();

    if (child == 0){
        printf("Successfully forked the child process. Its PID = %d \n", getpid());
        printf("Displaying the date and time:\n ");
        execl("/bin/date", "date", 0, (char*) NULL);
    }
    else if(child < 0){
        printf("Error in forking the child process.\n");
    }
    else{
        waitpid(child, &status, 0);
    }
    return 0;
}
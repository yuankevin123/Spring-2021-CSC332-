#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char *argv[]){
    pid_t child;
    char command[100];
    char* ptr;
    int index = 0, status;
    printf("Enter commands (quit to exit): \n");
    while(strcmp(command, "quit") != 0){
        index = 0;
        fgets(command, sizeof command, stdin);
        command[strcspn(command, "\n")] = 0;
        ptr = strtok(command, " "); 
        while (ptr != NULL){
            argv[index] = ptr;
            ptr = strtok(NULL, " ");
            index += 1;
        }
        argv[index] = NULL;
        child = fork();
        if(child == 0){
            if(execvp(argv[0], &argv[0]) < 0){
                if(strcmp(command, "quit") != 0){
                    printf("Failed to execute execvp\n");
                }
            }
            return 0;
        }
        else if (child < 0){
            perror("error");
            return 1;
        }
        else{
            waitpid(child, &status, 0);
        }
    }
    
    return 0;
}
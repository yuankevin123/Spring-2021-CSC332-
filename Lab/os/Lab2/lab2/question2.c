#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int a = 10, b = 25, fq = 0, fr = 0;
    // int wpid, status=0;
    printf("Initial Values: a = %d, b = %d, pid = %d, ppid = %d\n", a, b, getpid(), getppid());
    fq = fork();
    if (fq == 0){  //check if child process Q is forked successfully
        a = a + b;
        printf("a = %d, b = %d, Child Process Q = %d, Parent Process = %d\n", a, b, getpid(), getppid());
        fr = fork(); //fork for child process R
        if (fr != 0){ //checking parent process of R
            b = b + 15;
            printf("a = %d, b = %d, Parent Process of R = %d, Parent Process = %d\n", a, b, getpid(), getppid());
            // wpid=wait(&status);
        }
        else{ //child process R 
            a = (a * b) + 20;
            printf("a = %d, b = %d, Child Process R = %d, Parent Process = %d\n", a, b, getpid(), getppid());
        }
    }
    else{ //parent process Q
        b = a + b - 5;
        printf("a = %d, b = %d, Parent Process Q = %d, Parent Process P = %d\n", a, b, getpid(), getppid());
        // wpid=wait(&status);
    }
}
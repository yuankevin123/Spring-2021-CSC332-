#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "sem.h"

int main(){
    int tobacco, paper, match; //three ingredients
    int agent, lock; 
    int smoker; //child process
    int status;

    //create semaphores
    tobacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    paper = semget(IPC_PRIVATE, 1, 0666| IPC_CREAT);
    match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

    //failed to create semaphore
    if(tobacco == -1 || paper == -1 || match == -1 || agent == -1 || lock == -1){
        perror("semget");
        exit(1);
    }

    //initialize semaphores (all except lock is initialized to 0)
    sem_create(tobacco, 0);
    sem_create(paper, 0);
    sem_create(match, 0);
    sem_create(agent, 0);
    sem_create(lock, 1); //mutex variable 

    srand(time(0));

    //fork child process
    smoker = fork();

    if (smoker == -1){
        perror("fork");
        return -1;
    }
    else if(smoker == 0){
        for(int i = 0; i < 10; i ++){
        //intialize random generation for 10 runs
            P(lock);
            int randNum = rand() % 3 + 1; 
            if(randNum == 1){
                printf("Put tobacco on table\n");
                printf("Put paper on table\n");
                sleep(1);
                V(match); //wake up smoker with match
            }
            else if(randNum == 2){
                printf("Put tobacco on table\n");
                printf("Put match on table\n");
                sleep(1);
                V(paper); //wake up smoker with paper
            }
            else if(randNum == 3){
                printf("Put match on table\n");
                printf("Put paper on table\n");
                sleep(1);
                V(tobacco); //wake up smoker with tobacco
            }
            V(lock);
            P(agent); //put agent to sleep
        }
    }
    else{
        //smoker with match
        smoker = fork();
        if (smoker == -1){
            perror("fork");
            return -1;
        }
        if(smoker == 0){
            while(1){
                P(match);
                P(lock);
                printf("Somker with match picks up tobacco\n");
                printf("smoker with match picks up paper\n");
                V(agent);
                V(lock);
                printf("Smoker with match is smoking\n\n");
            }
        }
        else{
            //smoker with paper
            smoker = fork();
            if(smoker == -1){
                perror("fork");
                return -1;
            }
            if(smoker == 0){
                while(1){
                    P(paper);
                    P(lock);
                    printf("Smoker with paper picks up match\n");
                    printf("Smoker with paper picks up tobacco\n");
                    V(agent);
                    V(lock);
                    printf("Smoker with paper is smoking\n\n");
                }
            }
            else{
                //smoker with tobacco
                smoker = fork();
                if(smoker == -1){
                    perror("fork");
                    return -1;
                }
                if(smoker == 0){
                    while(1){
                        P(tobacco);
                        P(lock);
                        printf("Smoker with tobacco picks up match\n");
                        printf("Smoker with tobacco picks up paper\n");
                        V(agent);
                        V(lock);
                        printf("Smoker with tobacco is smoking\n\n");
                    }
                }
                else{
                    smoker = wait(&status);
                    printf("Process completed! Agent is out of ingredients\n\n");

                    // semkill(match);
                    // semkill(paper);
                    // semkill(tobacco);
                    // semkill(agent);
                    // semkill(lock);
                }
            }
        }
    }
    exit(0);
}

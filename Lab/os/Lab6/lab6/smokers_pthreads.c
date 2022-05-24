#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>

pthread_mutex_t tobacco = PTHREAD_COND_INITIALIZER;
pthread_mutex_t match = PTHREAD_COND_INITIALIZER;
pthread_mutex_t paper = PTHREAD_COND_INITIALIZER;
pthread_mutex_t agent = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_COND_INITIALIZER;

int count = 10; 

void *agent_func(){
    srand(time(0));
    for (int i = 0; i < count; i++){
        pthread_mutex_lock(&lock);
        int randNum = rand() % 3 + 1;
        if(randNum == 1){
                printf("Put tobacco on table\n");
                printf("Put paper on table\n");
                sleep(1);
                pthread_mutex_unlock(&match); //wake up smoker with match
            }
            else if(randNum == 2){
                printf("Put tobacco on table\n");
                printf("Put match on table\n");
                sleep(1);
                pthread_mutex_unlock(&paper); //wake up smoker with paper
            }
            else if(randNum == 3){
                printf("Put match on table\n");
                printf("Put paper on table\n");
                sleep(1);
                pthread_mutex_unlock(&tobacco); //wake up smoker with tobacco
            }
            pthread_mutex_unlock(&lock);
            pthread_mutex_lock(&agent); //put agent to sleep
    }
}

void *smoker_func(void *ptr){
    int randNum = (long)ptr;
    if(randNum == 1){//smoker with match
        while(1){
                pthread_mutex_lock(&match);
                pthread_mutex_lock(&lock);
                printf("Somker with match picks up tobacco\n");
                printf("smoker with match picks up paper\n");
                pthread_mutex_unlock(&agent);
                pthread_mutex_unlock(&lock);
                printf("Smoker with match is smoking\n\n");
        }
    }
    else if(randNum == 2){//smoker with paper
        while(1){
                pthread_mutex_lock(&paper);
                pthread_mutex_lock(&lock);
                printf("Smoker with paper picks up match\n");
                printf("Smoker with paper picks up tobacco\n");
                pthread_mutex_unlock(&agent);
                pthread_mutex_unlock(&lock);
                printf("Smoker with paper is smoking\n\n");
        }   
    }
    else if(randNum == 3){//smoker with tobacco
        while(1){
            pthread_mutex_lock(&tobacco);
            pthread_mutex_lock(&lock);
            printf("Smoker with tobacco picks up match\n");
            printf("Smoker with tobacco picks up paper\n");
            pthread_mutex_unlock(&agent);
            pthread_mutex_unlock(&lock);
            printf("Smoker with tobacco is smoking\n\n");
        }
    }
}

int main(){
    pthread_t agent_proc, match_proc, paper_proc, tobacco_proc;

    //intialize mutexes
    pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&agent, NULL);
	pthread_mutex_init(&tobacco, NULL);
	pthread_mutex_init(&match, NULL);
	pthread_mutex_init(&paper, NULL);

    // intialize locks (lock is unlocked)
    pthread_mutex_lock(&tobacco);
    pthread_mutex_lock(&match);
    pthread_mutex_lock(&paper);
    pthread_mutex_lock(&agent);
    pthread_mutex_unlock(&lock);

    // create threads
    pthread_create(&agent_proc, NULL, &agent_func, NULL);
    pthread_create(&match_proc, NULL, &smoker_func, (void *)1);
    pthread_create(&paper_proc, NULL, &smoker_func, (void *)2);
    pthread_create(&tobacco_proc, NULL, &smoker_func, (void *)3);

    // join thread with agent as other threads depends on this 
    pthread_join(agent_proc, NULL);

    //terminate threads
    pthread_kill(tobacco_proc, SIGTERM);
    pthread_kill(match_proc, SIGTERM);
    pthread_kill(paper_proc, SIGTERM);

    printf("Process completed! Agent is out of ingredients\n\n");
    exit(0);
}
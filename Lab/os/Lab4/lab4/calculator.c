#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int x = 5; //chapters
    int y = 2; //homeworks
    int total = 0;
    int status = 0;
    pid_t manager, worker;
    int grade[10][x*y];
    FILE* file = fopen("quiz_grades.txt", "r");
    FILE* average = fopen("averages.txt", "w");
    //store the values from text into array
    for (int rows = 0; rows < 10; rows++){
        for (int cols = 0; cols < 10; cols++){
            fscanf(file, "%d", &grade[rows][cols]);
        }
    }
    //create x number of manager processes
    for(int i = 0; i < x; i++){
        manager = fork();
        if(manager == 0){
            //create y number of worker proccesses
            for(int j = 0; j < y; j++){
                worker = fork();
                if(worker == 0){
                    //calculate average of each homework
                    for(int row = 0; row < 10; row++){
                        total += grade[row][i * y + j];
                    }
                    printf("\nAverage grade of homework is: %.1f\n", (float)total/10);
                    fprintf(average, "%.1f\n", (float)total/10);
                    return 0;
                }
                else if(worker < 0){
                    perror("error");
                    return -1;
                }
                else{
                    waitpid(worker, &status, 0);
                    printf("Worker #%d finished\n", i*2+j+1);
                }
            }
            return 0;
        }
        else if(manager < 0){
            perror("error");
            return -1;
        }
        else{
            waitpid(manager, &status, 0);
            printf("Manager #%d finished", i+1);
            printf("\n");
        }
    }
    fclose(file);
    fclose(average);
    return 0;
}

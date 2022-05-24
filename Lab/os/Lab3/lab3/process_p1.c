#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd, dest; 
    int total, count;
    int bytes;
    char buffer[3000];
    fd = open("destination1.txt", O_WRONLY | O_CREAT , 0777);

    if (fd < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpened destination1.txt Successfully\n");
    }

    dest = open("destination2.txt", O_WRONLY | O_CREAT , 0777);
    if (dest < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpened destination2.txt Successfully\n");
    }

    close(fd);
    close(dest);
    return 0;
}
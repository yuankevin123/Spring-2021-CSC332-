#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd, dest, dest2; 
    int count = 0;
    int bytes;
    char buffer[3000];
    fd = open("source.txt", O_RDONLY);

    if (fd < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpened source.txt Successfully\n");
    }

    dest = open("destination1.txt", O_RDWR);
    dest2 = open("destination2.txt", O_RDWR);
    
    if (dest < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpened destination1.txt Successfully\n");
    }

    if (dest2 < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpened destination2.txt Successfully\n");
    }

    
    while((bytes = read(fd, buffer, 53)) > 0){
        if (bytes < 0){
            perror("read");
        }
        else{
            write(dest, buffer, bytes);
            if((bytes = read(fd, buffer, 102)) > 0){
                write(dest2, buffer, bytes);
            }
            else{
                perror("read");
            }
        }
    }
    printf("\nContents Written Successfully\n\n");
    close(fd);
    close(dest);
    close(dest2);
    return bytes < 0;
}
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd, dest; 
    int total, count;
    int bytes;
    char buffer[3000];
    fd = open(argv[1], O_RDONLY);

    if (fd < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpen() First File Successfully\n");
    }

    dest = open(argv[2], O_WRONLY | O_CREAT);
    if (dest < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpen() Second File Successfully\n");
    }


    bytes = read(fd, buffer, sizeof(buffer));
    if (bytes < 0){
        perror("read");
    }
    else{
        printf("\n");
        write(dest, buffer, bytes);
        printf("Contents Copied Successfully\n\n");
    }
    close(fd);
    close(dest);
    return bytes < 0;
}
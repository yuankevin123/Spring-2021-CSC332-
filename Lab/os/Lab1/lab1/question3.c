#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd, dest; 
    int count = 0;
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

    dest = open(argv[2], O_RDWR | O_CREAT);
    if (dest < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpen() Second File Successfully\n");
    }

    
    while((bytes = read(fd, buffer, 53)) > 0){
        if (bytes < 0){
            perror("read");
        }
        else{
            for (int i = 0; i < bytes; i++){
                // printf("%c\n", buffer[i]);
                if (buffer[i] == '5'){
                    buffer[i] = 'A';
                    // write(dest, buffer, 0);
                }
                // count += 1;
                // printf("%d\n", i);
            }
            write(dest, buffer, bytes);
            write(dest, "XYZ", 3);
        }
    }
    printf("\nContents Replaced Successfully\n\n");
    close(fd);
    close(dest);
    return bytes < 0;
}
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd; 
    int total, count;
    int bytes;
    char buffer[100];
    fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        printf("\nOpen failed with error \n");
        perror("open");
    }
    else{
        printf("\nOpen() Successful\nDisplaying Content of File \n");
    }
    bytes = read(fd, buffer, sizeof(buffer));
    if (bytes < 0){
        perror("read");
    }
    else{
        // for (total = 0; bytes > total; total++){
        //     count = total;
        // }
        printf("\n");
        write(1, buffer, bytes);
        printf("\n\n");
        // printf("\n%d", count);

    }
    close(fd);
    // printf("\nRead Successful\n");
    return bytes < 0;
}
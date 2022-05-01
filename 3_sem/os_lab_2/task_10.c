#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int file_status;
    file_status = open("z.txt", O_RDWR);
    if(file_status == -1) {
        printf("ERR: cannot open a file in read and write mode\n");
        return 0;
    }
    printf("File was openned in read and write mode\n");
    return 1;
}


/*
----------------------------------------------------------
Program: consumer.c
Date: October 31, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This (reader) program should respond to receiving 
the data over the FIFO. Keep both programs compiling to see 
the output and allow the programs to close together.
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "FIFOval"

int main() {
    int fd;
    char received[256];

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) 
    {
        perror("open for read");
        exit(EXIT_FAILURE);
    }

    if (read(fd, received, sizeof(received)) == -1) 
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("consumer: %s", received);

    close(fd);

    return 0;
}

/*
----------------------------------------------------------
Program: producer.c
Date: October 31, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This (writer) program transfers string data 
entered to another program over a FIFO. The program should 
prompt the user to enter words in a manner. Keep both programs 
compiling to see the output and allow the programs to close 
together.
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define FIFO_NAME "FIFOval"

int main() 
{
    int fd;
    char input[256];

    if (mkfifo(FIFO_NAME, S_IRUSR | S_IWUSR) == -1) 
    {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("Please enter text at the producer: \n");
    printf("producer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) 
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) 
    {
        perror("open for write");
        exit(EXIT_FAILURE);
    }

    if (write(fd, input, strlen(input)) == -1) 
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}

/*
----------------------------------------------------------
Program: prog9_1.c
Date: October 31, 2023
Student Name & NetID: Kennedy Keyes kfk38
Description: This is a program that transfers string data 
entered in the parent to the child over a pipe. The parent 
should prompt the user to enter words in a manner. The child 
should then respond to receiving the data over the pipe. Then 
it closes.
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STRING_LENGTH 100

int main() 
{
    int fd[2];
    pid_t pid;
    char input[MAX_STRING_LENGTH];
    char received[MAX_STRING_LENGTH];

    if (pipe(fd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // this is the child process
    {
        close(fd[1]); // this closes the write end of the pipe

        ssize_t bytesRead = read(fd[0], received, sizeof(received));
        if (bytesRead == -1) 
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        received[bytesRead] = '\0';
        printf("\nchild: %s\n", received);

        close(fd[0]); // this closes the read end of the pipe
    } else // parent process
    {
        close(fd[0]); // this closes the read end of the pipe (like before)

        printf("Please enter text at the parent: \n");
        printf("parent: ");
        if (fgets(input, sizeof(input), stdin) == NULL) 
        {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        ssize_t bytesWritten = write(fd[1], input, strlen(input));
        if (bytesWritten == -1) 
        {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(fd[1]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> // add this for open()

/*
Question:
Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?

The program can write to the file simultaneously/concurrently. There 
is no issue with accessing the same file. 
*/

int writeMessage(int __fd, char* message){
    int bytesWritten = write(__fd, message, strlen(message));
    if(bytesWritten == -1){
        fprintf(stderr, "failed to write");
    }
    return bytesWritten;
}

int main(int argc, char *argv[])
{    
    printf("hello world (pid:%d)\n", (int) getpid());
    int fd = open("example.txt", O_APPEND | O_RDWR);
    if(fd == -1){
        fprintf(stderr, "file open failed\n");
    }
    
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        char* message = "This is the child process\n";
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        writeMessage(fd, message);
    } else {
        // parent goes down this path (original process)
        char* message = "This is the parent process\n";
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        writeMessage(fd, message);
    }
    close(fd);
    return 0;
}

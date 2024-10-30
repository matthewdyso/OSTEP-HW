#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Question: Now write a program that uses wait()to wait for the child process 
to finish in the parent. What does wait() return? What happens if you 
use wait() in the child?

Answer: The wait process returns the PID process of the child process. 
When the child has called the wait process, wait() returns -1 as the child has no 
child processes to wait for. As such, there is an error and returns -1. 
*/
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        int wc = wait(NULL);
        printf("\nThe value of wc is: %d\n", wc);

    } else {
        // int wc = wait(NULL);
        // printf("\nThe value of wc is: %d\n", wc);

        // parent goes down this path (original process)
        printf("Goodbye, I am parent of %d (pid:%d)\n", rc, (int) getpid());

    
    }
    return 0;
}


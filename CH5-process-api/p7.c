#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>


/*
Question: Write a program that creates a child process, and then in the
child closes standardoutput(STDOUT FILENO).What happens if the child calls 
printf() to print some output after closing the descriptor?

Answer: Nothing is printed. printf() is reliant on stdout and the output
can be be redirected to a different file or descriptor in order to be printed. 
*/
int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO); 
        printf("random output\n");
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
	    assert(wc >= 0);
    }
    return 0;
}

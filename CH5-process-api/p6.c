#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Question: Write a slight modification of the previous program, 
this time using waitpid() instead of wait(). When would waitpid() be useful?

Answer: WaitPID gives more control and if there are multiple child processes for one parent
it can make it so that the parent only needs to wait for one child to complete. It also has more
options for returning with WUNTRACED and WNOHANG.
*/
int main(int argc, char *argv[])
{
    int status = NULL;
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());

    } else {
        int wc = waitpid(rc, &status, WUNTRACED);
        printf("\nThe value of wc is: %d\n", wc);

        // parent goes down this path (original process)
        printf("Goodbye, I am parent of %d (pid:%d)\n", rc, (int) getpid());

        
    }
    return 0;
}


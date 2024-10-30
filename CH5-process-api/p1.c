#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 
Question:
Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to something
(e.g., 100). What value is the variable in the child process?
What happens to the variablewhen both the child and parent change
the value of x?

Answer:
The parent and child both make a copy of the variable x that is private
to both processes. They independently modify the value and do not affect each other. 
*/

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int x = 10;
    printf("The variable value is %d\n", x);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        x += 5;
        printf("the value of the variable x in the child proc is: %d\n", x);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
        x += 9;
        printf("the value of the variable x in the parent proc is: %d\n", x);
    }

    printf("This is the final value of x: %d\n", x);
    return 0;
}


#define _GNU_SOURCE // for execvpe() and has to be above unistd.h
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
Question: Write a program that calls fork() and then calls some form of 
exec() to run the program /bin/ls. See if you can try all of the variants of 
exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), 
and execvpe(). Why do you think there are so many variants of the same basic call?

Answer: There are multiple variants of exec() due to the different scenarios
that a parent and child process can be in. V and L seem to be mainly for convenience, as 
having multiple inputs to run a program can be tedious to do with execl() but simpler
with execv(). Different environments make use of E and using P makes it easy to run child
processes outside of the current directory as it will search for the file by itself.
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

        // Only one exec() can run at a time

        printf("Running execl()\n");
        // file path, argv[0] aka program name, cmd line arguments for executable
        execl("/bin/ls", "ls", NULL);//  all arguments list or vector must terminate in NULL

        // Searches for the directory with the executable instead
        // needing the file path
        printf("Running execlp()\n");
        // file name, argv[0], arguments;
        execlp("ls", "ls", NULL);
        
        printf("Running execle()\n");
        // file path, argv[0], envp, arguments;
        execle("/bin/ls", "ls", NULL, NULL);

        //execv takes inputs in the form of an array instead of multiple arguments that form a list
        char* args[3] = {"ls", NULL};
        printf("\nRunning execv()\n");
        execv("/bin/ls", args);

        printf("\nRunning execvp()\n");
        execvp("ls", args);

        printf("\nRunning execvpe()\n");
        execvpe("ls", args, NULL);


    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	       rc, wc, (int) getpid());
    }
    return 0;
}

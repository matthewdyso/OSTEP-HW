#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) == -1) { // Create the pipe before forking
        perror("pipe failed");
        exit(1);
    }

    int rc1 = fork();
    if (rc1 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // First child process
        close(fd[0]);                  // Close unused read end
        dup2(fd[1], STDOUT_FILENO);     // Redirect stdout to pipe write end

        char *message = "random message";
        write(fd[1], message, strlen(message)); // Write message to pipe
        close(fd[1]);                  // Close the write end after writing

        exit(0);
    }

    // Second child process
    int rc2 = fork();
    if (rc2 < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc2 == 0) {
        // Second child
        close(fd[1]);                  // Close unused write end
        dup2(fd[0], STDIN_FILENO);     // Redirect stdin to pipe read end

        char buffer[20] = {0};
        read(fd[0], buffer, sizeof(buffer) - 1); // Read from pipe into buffer
        printf("received: %s\n", buffer);

        close(fd[0]);                  // Close read end after reading
        exit(0);
    }

    // Parent process
    close(fd[0]);                       // Close both ends of the pipe in parent
    close(fd[1]);

    int wc1 = waitpid(rc1, NULL, WUNTRACED);
    int wc2 = waitpid(rc2, NULL, WUNTRACED);
    assert(wc1 >= 0 && wc2 >= 0);

    printf("goodbye\n");
    return 0;
}

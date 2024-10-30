## Chapter 5

### Q1  
**Prompt:**  
Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., `x`) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of `x`?

**Answer:**  
The parent and child both make a copy of the variable `x` that is private to each process. They independently modify the value and do not affect each other.

---

### Q2  
**Prompt:**  
Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

**Answer:**  
The program can write to the file simultaneously/concurrently. There is no issue with accessing the same file.

---

### Q3  
**Prompt:**  
Write another program using `fork()`. The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

**Answer:**  
One way of achieving this is by putting the parent process to sleep briefly, giving time for the child process to complete before the parent process prints.

---

### Q4  
**Prompt:**  
Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. Try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

**Answer:**  
There are multiple variants of `exec()` to handle different scenarios. `V` and `L` variations offer convenience, allowing either a vector of arguments or a list of arguments for the executable. The `E` variants allow custom environments, and the `P` variants facilitate running child processes outside the current directory by automatically searching for the executable.

---

### Q5  
**Prompt:**  
Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

**Answer:**  
The `wait()` function returns the PID of the terminated child process. If `wait()` is called in the child, it returns -1, as the child has no child processes of its own, resulting in an error.

---

### Q6  
**Prompt:**  
Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

**Answer:**  
`waitpid()` provides more control, especially useful if a parent process has multiple child processes, allowing it to wait for a specific child. It also supports options like `WUNTRACED` and `WNOHANG`, providing more flexibility.

---

### Q7  
**Prompt:**  
Write a program that creates a child process, and then in the child closes `STDOUT_FILENO`. What happens if the child calls `printf()` to print some output after closing the descriptor?

**Answer:**  
Nothing is printed because `printf()` relies on `stdout`, which has been closed. Output can still be redirected to another file or descriptor to ensure it is printed.

---

### Q8  
**Prompt:**  
Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

**Answer:**  
The `pipe()` is initially called in the parent process so both child processes can access it. The first child process sets its standard output to the pipe's writing end (`fd[1]`). It then uses `write()` to send a message and closes the writing end, allowing the other child to read. The second child process sets its standard input to the pipe's reading end (`fd[0]`) and calls `read()`. After both children have exited, the parent closes both ends of the pipe.

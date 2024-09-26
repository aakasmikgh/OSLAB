Lab 7
 
 
//1. Write a program to create new process using fork system call.
 
#include <stdio.h>
#include <unistd.h>
 
int main() {
    pid_t pid;
 
    pid = fork(); // Create a new process
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("This is the child process\n");
    } else {
        printf("This is the parent process\n");
    }
 
    return 0;
}
 
 
//2. Write a program to take two numbers as input and perform addition by parent process whereas subtraction by child process
 
#include <stdio.h>
#include <unistd.h>
 
int main() {
    int a, b;
    pid_t pid;
 
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
 
    pid = fork();
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: Subtraction of %d and %d is %d\n", a, b, a - b);
    } else {
        printf("Parent Process: Addition of %d and %d is %d\n", a, b, a + b);
    }
 
    return 0;
}
 
 
//3. Write a program to illustrate zombie and orphan process
 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int main() {
    pid_t pid = fork();
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(5); // Sleep to create orphan
        printf("Child Process: After sleep, PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        printf("Parent Process: PID = %d\n", getpid());
        sleep(2); // Parent exits before child
        printf("Parent Process exiting...\n");
    }
 
    return 0;
}
 
//4. Write a program to illustrate wait() system call
 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
    pid_t pid = fork();
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: PID = %d\n", getpid());
        sleep(2);
        printf("Child Process exiting...\n");
    } else {
        printf("Parent Process: Waiting for child to finish...\n");
        wait(NULL); // Parent waits for child to finish
        printf("Parent Process: Child finished, now exiting...\n");
    }
 
    return 0;
}
 
//5. Write a program to illustrate exec() system call
 
#include <stdio.h>
#include <unistd.h>
 
int main() {
    pid_t pid = fork();
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (pid == 0) {
        printf("Child Process: About to replace with new program\n");
        execlp("/bin/ls", "ls", NULL); // Replace child process with ls command
    } else {
        printf("Parent Process: PID = %d\n", getpid());
    }
 
    return 0;
}

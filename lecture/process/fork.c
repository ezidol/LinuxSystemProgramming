#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
void test_function(void) {
    printf("This is a test function\n");
}

int main(void) {
    pid_t pid;

    printf("This is origin process %d\n", getpid());
    pid = fork();
        
    if (pid == 0) {
        printf("This is child process %d\n", getpid());
    } else if (pid > 0) {
        printf("This is parent process %d, child process %d\n", getpid(), pid);
    } else {
        perror("fork error");
        return -1;
    }
    return 0;
}

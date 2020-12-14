#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int write_file(void) {
    int fd;
    fd = open("datafile", O_WRONLY | O_CREAT, 0644);
    printf("%d\n", fd);
    if (fd == -1) {
        perror("open error");
        return -1;
    }
    dprintf(fd, "Hello World %d", 230);
    close(fd);

    return 0;
}
static int trunc_file(void) {
    int fd;
    fd = open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    printf("%d\n", fd);
    if (fd == -1) {
        perror("open error");
        return -1;
    }
    dprintf(fd, "Bye %d", 8282);
    close(fd);

    return 0;
} 
int main(void) {
    if (write_file()) {
        printf("write_file error\n");
        return -1;
    }
    if (trunc_file()) {
        printf("trunc_file error\n");
        return -1;
    }
    return 0;
}


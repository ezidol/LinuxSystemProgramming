#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int write_memo(char *memo) {
    int fd;

    fd = open("note", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("wrtie_memo open error");
        return -1;
    }
    dprintf(fd, "%s\n", memo);

    return 0;
}

int read_memo(void) {
    int fd;
    char buf[1024];

    fd = open("note", O_RDONLY, 0644);
    if (fd == -1) {
        perror("read_memo open error");
        return -1;
    }
    read(fd, buf, sizeof(buf));
    if (fd == -1) {
        perror("read_memo read error");
        return -1;
    }
    printf("%s \n", buf);

    return 0;
}

int main(int argc, char **argv) {
    
    if (argc == 0) {
        if (read_memo()) {
            printf("read_memo() fail");
            return -1;
        }
    }
    if (write_memo(argv[1])) {
        printf("write_memo() fail");
        return -1;
    }
    if (read_memo()) {
        printf("read_memo() fail");
        return -1;
    }

    return 0;
}

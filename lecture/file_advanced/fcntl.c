#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int ret, flag;
    int fd = STDIN_FILENO;
    char buf[128];

    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    if (ret == -1) {
        perror("read fail");
        return -1;
    }
    printf("buf: %s bytes: %d\n", buf, ret);
    
    flag = fcntl(fd, F_GETFL);
    if (flag == -1) {
        perror("fcntl [F_GETFL] fail");
        return -1;
    }
    ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if (ret == -1) {
        perror("fcntl [F_SETFL] fail");
        return -1;
    }
    printf("trying to read...\n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    if (ret == -1) {
        perror("read fail");
        return -1;
    }
    printf("buf: %s bytes: %d\n", buf, ret);

    return 0;
}

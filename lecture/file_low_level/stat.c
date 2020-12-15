#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    struct stat statbuf;
    if (argc < 2) {
        printf("%s\n", argv[0]);
        return -1;
    }
    if (stat(argv[1], &statbuf)) {
        printf("stat error\n");
        return -1;
    }
    printf("filename: %s\n", argv[1]);
    printf("%lu\n", statbuf.st_size);
    if (S_ISDIR(statbuf.st_mode)) {
        printf("directory\n");
        return -1;
    } else if (S_ISREG(statbuf.st_mode)) {
        printf("reguler file\n");
        return -1;
    } else {
        printf("???");
    }

    return 0;
}


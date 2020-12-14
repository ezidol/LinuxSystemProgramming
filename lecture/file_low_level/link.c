#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
#define TARGET_FILE "Hello"
    if (link(TARGET_FILE, "Hello_by_hardlink")) {
        printf("link error\n");
        return -1;
    }
    if (symlink(TARGET_FILE, "Hello_by_symlink")) {
        printf("symlink error\n");
        return -1;
    }
    return 0;
}

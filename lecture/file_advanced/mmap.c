#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>

struct person {
    char name[16];
    int age;
};

static int write_info(struct person *p) {
    int fd;
    ssize_t ret;
    fd = open("data_info", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        printf("open error\n");
        return -1;
    }
    ret = write(fd, p, sizeof(struct person));
    if (ret == -1) {
        printf("write error\n");
        return -1;
    } else if (ret != sizeof(struct person)){
        printf("write partial write error");
        return -1;
    }
    close(fd);

    return 0;
}

static int dump_info(void) {
    int fd;
    struct stat statbuf;
    struct person *p;
    fd = open("data_info", O_RDONLY);
    if (fd == -1) {
        printf("open error\n");
        return -1;
    }
    fstat(fd, &statbuf);
    p = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    for (int i = 0; i <statbuf.st_size / sizeof(struct person); i++) {
       printf("name: %s, age: %d\n", p[i].name, p[i].age);
    }
    close(fd);

    return 0;
}

int main(void) {
    struct person persons[] = {
        {"jack", 40},
        {"peter", 50}
    };
    write_info(&persons[0]);
    write_info(&persons[1]);
    dump_info();
    
    return 0;
}

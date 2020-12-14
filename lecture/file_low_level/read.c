#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    ssize_t ret;
    struct person p;
    fd = open("data_info", O_RDONLY);
    if (fd == -1) {
        printf("open error\n");
        return -1;
    }
    do {
        ret = read(fd, &p, sizeof(struct person));
        if (ret == -1) {
            printf("read error\n");
            return -1;
        } else if (ret == 0) {
            FILE *fp;
            fp = fdopen(fd, "r");
            if (fp == NULL) {
                printf("fdopen error\n");
                return -1;
            }
            printf("file position = %ld\n", ftell(fp));
            fclose(fp);
            break;
        } else if (ret != sizeof(struct person)){
            printf("read partial error");
            return -1;
        }
        printf("%s, %d \n", p.name, p.age);
    } while(1);
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

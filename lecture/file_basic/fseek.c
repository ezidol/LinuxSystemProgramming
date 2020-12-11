#include <stdio.h>
#include <string.h>

static int create_file(void) {
    FILE *fp;
    if (!(fp = fopen("datafile", "w"))) {
        perror("fopen error\n");
        return -1;
    }

    printf("after fopen(), offset=%ld\n", ftell(fp));
    fputs("Hello world!\n", fp);
    fputs("I am Peter\n", fp);
    fputs("What do you do?\n", fp);
    printf("before fclose(); offset=%ld\n", ftell(fp));
    printf("----------------------------\n");
    fclose(fp);

    return 0;
}
static int read_file(void) {
    FILE *fp;
    char buf[1024];
    if (!(fp = fopen("datafile", "r+"))) {
        perror("fopen error\n");
        return -1;
    }
    memset(buf, 0, sizeof(buf));
    printf("after fopen(), offset=%ld\n", ftell(fp));
    fgets(buf, sizeof(buf), fp);
    printf("after fgets(); offset=%ld\n", ftell(fp));
    fseek(fp, 0, SEEK_END);
    printf("after fseek(); offset=%ld\n", ftell(fp));
    fputs("Final\n", fp);
    printf("before fclose(); offset=%ld\n", ftell(fp));
    printf("----------------------------\n");
    fclose(fp);

    return 0;
}


int main(void) {

    create_file();
    read_file();

    return 0;
}

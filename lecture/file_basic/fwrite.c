#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct person {
    char name[20];
    int age;
};

static int wrtie_to_file(void) {
    FILE *fp = NULL;
    struct person jack = {
        .name = "jack",
        .age = 30
    };
    
    struct person peter = {
        .name = "peter",
        .age = 50
    };


    if (!(fp = fopen("persons", "w"))) {
        perror("fopen error");
        return -1;
    }

    if (fwrite(&jack, sizeof(struct person), 1, fp) != 1) {
        goto err;
    }
    if (fwrite(&peter, sizeof(struct person), 1, fp) != 1) {
        goto err;
    }

    fclose(fp);

    return 0;

err:
    if (fp) {
        fclose(fp);
    }
    return -1;
}
static int read_from_file(void) {
    FILE *fp = NULL;
    struct person persons[2];

    if (!(fp = fopen("persons", "r"))) {
        perror("fopen error");
        return -1;
    }
    if ((fread(persons, sizeof(struct person), 2, fp)) != 2) {
        fclose(fp);
        return -1;
    }

    fclose(fp);

    for (int i = 0; i < 2; i++) {
        printf("name: %s, age: %d\n", persons[i].name, persons[i].age);
    }
    return 0;
    
}
int main(void) {

    if (wrtie_to_file()) {
        printf("wrtie_to_file error\n");
        return -1;
    };
    if (read_from_file()) {
        printf("read_from_file error\n");
        return -1;
    }

    return 0;
}

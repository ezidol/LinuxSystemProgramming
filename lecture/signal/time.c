#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

static void print_cur_time(void) {
    time_t now;
    struct tm *now_tm;

    now = time(NULL);

    printf("current: %ld ", now);
    now_tm = localtime(&now);

    if (!now_tm) {
        perror("localtime() fail");
        return;
    }
    printf("%d/%d/%d %d-%d-%d\n", 
            now_tm->tm_year + 1900,
            now_tm->tm_mon + 1,
            now_tm->tm_mday,
            now_tm->tm_hour,
            now_tm->tm_min,
            now_tm->tm_sec);

}

static void sigalarm_handler(int signum) {

    printf("got SIGALRM\n");
    print_cur_time();
}

int main(int argc, char **argv) {
    struct itimerval ival;
    signal(SIGALRM, sigalarm_handler);
    print_cur_time();

    //alarm(5);
    ival.it_value.tv_sec = 5;
    ival.it_value.tv_usec = 0;
    ival.it_interval.tv_sec = 1;
    ival.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &ival, NULL) != 0) {
        perror("setitimer() error");
        return -1;
    }

    while(1) {
        sleep(1);
    }

    return 0;
}

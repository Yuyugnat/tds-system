#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int pv;

void handler(int sig) {
    if (sig == 10) {
        sigset_t set;
        sigemptyset(&set);
        sigfillset(&set);
        sigprocmask(SIG_SETMASK, &set, NULL);
        int i = 0;
        while (i < 10) {
            printf("Je suis invincible !\n");
            i++;
            sleep(1);
        }
        sigset_t empty;
        sigemptyset(&empty);
        sigprocmask(SIG_SETMASK, &empty, NULL);
    } else {
        pv -= sig;
    }
}

int main(int argc, char **argv) {

    for (int i = 1; i <= 10; i++)
        signal(i, &handler);

    pv = atoi(argv[1]);



    while (pv > 0) {
        printf("[PV: %i] \"C'est injuste!\" - Kenny\n", pv);
        sleep(3);
    }

    printf("Kenny est mort.\n");
}
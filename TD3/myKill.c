#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        exit(1);
    }
    int pid = atoi(argv[1]);
    int signal = atoi(argv[2]);
    kill(pid, signal);
    return 0;
}
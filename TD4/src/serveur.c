
#include "message.h"

#include <sys/types.h> 
#include <unistd.h>

#include <sys/stat.h>
#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


void creation_tube_nomme() {
    mkfifo(FIFO_SERVEUR, 0666);
}

int fifo_me;
struct requete_client_serveur requete;

void recevoir_requete(){
    fifo_me = open(FIFO_SERVEUR, O_RDONLY);
    int readChars = read(fifo_me, &requete, sizeof(struct requete_client_serveur));
    close(fifo_me);
}

void envoyer_resultat(){
    char cmd[BUFFER_SIZE];
    sprintf(cmd, TEMPLATE_CMD, requete.expression);
    FILE *fp = popen(cmd, "r");
    fgets(requete.resultat, BUFFER_SIZE, fp);
    pclose(fp);

    char pathname[80];
    sprintf(pathname, PATH_FORMAT, requete.client_pid);
    int fifo_client = open(pathname, O_WRONLY);
    write(fifo_client, &requete, sizeof(struct requete_client_serveur));
    close(fifo_client);
}

void terminer(){
    remove(FIFO_SERVEUR);
}

int main(int argc, char** argv){

    creation_tube_nomme();
    
    while(1){
        recevoir_requete();
        envoyer_resultat();
    }

    terminer();
    
}

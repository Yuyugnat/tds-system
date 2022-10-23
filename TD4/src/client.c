#include "message.h"
#include <sys/types.h> 
#include <unistd.h>

#include <sys/stat.h>
#include<stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


pid_t pid ;
char pathname[80];
int fifo_serveur_fd;
int fifo_me_fd;
struct requete_client_serveur requete;

void creation_tube_nomme() {
    pid = getpid(); 
    sprintf(pathname,PATH_FORMAT,pid);
    mkfifo(pathname, 0666);
}

void envoyer_expression(){
    printf("Veuillez rentrer une expression\n");
    scanf("%s", requete.expression);
    requete.client_pid = getpid();
    fifo_serveur_fd = open(FIFO_SERVEUR, O_WRONLY);
    write(fifo_serveur_fd, &requete, sizeof(struct requete_client_serveur));
    close(fifo_serveur_fd);
}

void recevoir_resultat(){
    fifo_me_fd = open(pathname, O_RDONLY);
    read(fifo_me_fd, &requete, sizeof(struct requete_client_serveur));
    close(fifo_me_fd);

    printf("Le résultat de l'epxressin arithémtique est %s", requete.resultat);
};
    
void terminer()
{
    remove( pathname );
}

int main(int argc, char** argv){

    creation_tube_nomme();
    envoyer_expression();
    recevoir_resultat();
    terminer();   
    return 0;
}

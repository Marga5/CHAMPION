#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int tempo_campeonato;
int tempo_espera;

#define FIFO_CLI "cli"
#define FIFO_SRV "serv"

typedef struct{
    char ordem[20];
    char resposta[20];
    int pid;
}PEDIDO;

void Jogo();
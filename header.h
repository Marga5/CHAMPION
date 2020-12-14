#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int tempo_campeonato;
int tempo_espera;

#define FIFO_CLI "cli"
#define FIFO_SRV "serv"

typedef struct{
    char ordem[20];
    char resposta[20];
    int pid;
    char user[50];
}PEDIDO;

typedef struct {
	int pidJ;           //ID do Jogo
        char nomeJogo[50];  //Nome do jogo
	char gameDir[100];  //Directoria do jogo
	int nJogo;          // nº do jogo para sortear
        
}Jogos;

Jogos jogo[30];

void Jogo1();
void Jogo2();
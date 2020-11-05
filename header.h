 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int tempo_campeonato;
int tempo_espera;
int MAXPLAYERS;

typedef struct  { 
	int pidC;      
}Campeonatos;

typedef struct {
	int pidJ;
        char nomeJogo[50];
	char gameDir[100];
	int maxplayers;
        
}Jogos;

typedef struct {
	int pidP;
	char username[50];
	int pontuacao;
}Jogadores;

Jogos jogo;

void Jogo();


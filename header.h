int tempo_campeonato;
int tempo_espera;

typedef struct Campeonatos { 
	int id;
        int MAXPLAYERS;
}campeonato;

typedef struct Jogos {
	int id;
        char nomeJogo[50];
}jogo;

typedef struct Jogadores {
	int id;
	char username[50];
	int pontuacao;
}jogador;

void Jogo();
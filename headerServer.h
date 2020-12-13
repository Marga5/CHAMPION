
typedef struct  { 
	int pidC;           //ID do campeonato
        int maxplayers;     //maximo de jogadores no campeonato
}Campeonatos;


typedef struct {
	int pidJ;           //ID do Jogo
        char nomeJogo[50];  //Nome do jogo
	char gameDir[100];  //Directoria do jogo
	int nJogo;          // nº do jogo para sortear
        
}Jogos;

typedef struct {
	int pidP;           //Id do jogador
	char username[50];  //Nome do Jogador
	int pontuacao;      //pontuação do jogador obtida no ultimo torneio
        int inGame;         //variavel de controlo [0 - não está em nenhum jogo | 1 - já tem jogo atribuido]
}Jogadores;


Jogos jogo[30];
Jogadores jogador[30];
Campeonatos campeonato;


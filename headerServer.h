
typedef struct  { 
	int pidC;           //ID do campeonato
        int maxplayers;     //maximo de jogadores no campeonato
}Campeonatos;



typedef struct {
	int pidP;           //Id do jogador
	char username[50];  //Nome do Jogador
	int pontuacao;      //pontuação do jogador obtida no ultimo torneio
        int pidJogoAtribuido; //Id do jogo atribuido
        int inGame;         //variavel de controlo [0 - não está em nenhum jogo | 1 - já tem jogo atribuido]
        int comunicacao;    //0 - false, 1- true
}Jogadores;



Jogadores jogador[30];
Campeonatos campeonato;


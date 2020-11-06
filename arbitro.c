#include "header.h"
#include <string.h>


//Leitura de Variaveis de ambiente
//export MAXPLAYER="..."
//export GAMEDIR="..."
void inicializaVariaveis(){

    char * directory;
    char * Mplayers;

    directory = getenv("GAMEDIR");
    if(directory != NULL)
        strcpy(jogo.gameDir, directory);
    Mplayers = getenv("MAXPLAYER");
    if(Mplayers != NULL)
        campeonato.maxplayers = atoi(Mplayers);


    if(campeonato.maxplayers <= 0 || campeonato.maxplayers >= 30){
        campeonato.maxplayers = 20;
    }

    printf("Directoria: %s\n", jogo.gameDir);
    printf("MaxPlayers: %d\n", campeonato.maxplayers);
    

}


void main(int argc, char *argv[]) {
   int option;
   
   inicializaVariaveis();
   
   //leitura dos argumentos passados por linha de comandos
   while((option = getopt(argc, argv, ":if:t:d:")) != -1){ 
      switch(option){  
         case 't':
             tempo_espera = atoi(optarg);
            printf("Tempo de Espera definido para: %d\n", tempo_espera);           
            break;
            
         case 'd':           
            tempo_campeonato = atoi(optarg);
            printf("Duracao do campeonato definido para: %d\n", tempo_campeonato);
            break;
            
          case ':':
            printf("Opcao precisa de um valor\n");
            break;

         case '?': //usado para opçoes desconhecidas
            printf("Opcao desconhecida: %c\n", optopt);
            break;
      }
   }
   for(; optind < argc; optind++){ //Quando sao passados argumentos extra
      printf("Argumentos Extra: %s\n", argv[optind]);
   }
   
   printf("SERVIDOR LANCADO!!!\n");
   
   Jogo();
}
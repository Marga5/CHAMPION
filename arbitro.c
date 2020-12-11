#include "headerServer.h"
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
   PEDIDO p;
   int option;
   int fd, fdr, bytes;
   char fifo[40];
   
   //criar named pipe do servidor
    if(access(FIFO_SRV, F_OK) != 0){ //caso o fifo/servidor ainda nao exista
        mkfifo(FIFO_SRV, 0600);
    }
   printf("SERVIDOR LANCADO!!!\n FIFO CRIADO\n");
   
   
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
   
   
   
   fd = open(FIFO_SRV, O_RDWR); // -1 = ERRO
   printf("Abri o FIFO\n");
   
   do{
       bytes = read(fd, &p, sizeof(PEDIDO));
       printf("Recebi -> %s : cliente -> %d [%d bytes]", p.ordem,p.pid, bytes);
       strcpy(p.resposta, "confirmado");
       
       sprintf(fifo, FIFO_CLI, p.pid);
       fdr = open(FIFO_CLI, O_WRONLY);
       bytes = write(fdr, &p, sizeof(PEDIDO));
       close(fdr);
       printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
               
       
   }while(1);
   
   close(fd);
   unlink(FIFO_SRV);
   
   exit(5);
   
   //Jogo();
}
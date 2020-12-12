#include "headerServer.h"
#include "header.h"
#include <string.h>
#include <pthread.h>


//Leitura de Variaveis de ambiente
//export MAXPLAYER="..."
//export GAMEDIR="..."

void * ThreadComandosCliente(void * arg){

  PEDIDO p;
  int fd,fdr, bytes;
  char fifo[40];

  fd = open(FIFO_SRV, O_RDWR); // -1 = ERRO
  printf("Abri o FIFO\n");

  do {
       bytes = read(fd, &p, sizeof(PEDIDO));
       if(strcmp(p.ordem,"#game") == 0){
         printf("Recebi comando -> %s : cliente -> %d [%d bytes]", p.ordem,p.pid, bytes);
         strcpy(p.resposta, "Comando enviado com sucesso");
       
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         // print da informação do jogo atribuido
         
       }else if(strcmp(p.ordem,"#quit") == 0){
         printf("Recebi comando -> %s : cliente -> %d [%d bytes]", p.ordem,p.pid, bytes);
         strcpy(p.resposta, "Comando enviado com sucesso");
       
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         // sai do jogo , possivelmente dando unlink do fifo ao qual está conectado
       }
       else{
         printf("Recebi -> %s : cliente -> %d [%d bytes]", p.ordem,p.pid, bytes);
         strcpy(p.resposta, "Comando desconhecido");
       
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         }      
  
  }while(1);
  
  close(fd);
  unlink(FIFO_SRV);
}
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

void encerra(){
    printf("A encerrar o arbitro...\n");
            
    for(int i=0; i<30; i++){
      kill(jogador[i].pidP, SIGINT);
    }
    
    unlink(FIFO_SRV);

    exit(0);
}


void main(int argc, char *argv[]) {
   PEDIDO p;
   int option;
   int fd, fdr, bytes;
   char fifo[40], strtmp[40], str[3][40];
   pthread_t tComandos;
   
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
   
   
   //Thread para enviar campo
    pthread_create(&tComandos, NULL, &ThreadComandosCliente, NULL);
   
   do{
   	printf("\nComando: ");

       scanf("%s",&strtmp);

    	if (strncmp(strtmp,"k",1) == 0){
    		memcpy(str, strtmp+1,sizeof(strtmp));
        	for(int i=0; i<30; i++){
                if(strcmp(str, jogador[i].username)==0){
                    kill(jogador[i].pidP, SIGUSR1);
                }
            }
        }
    	else if (strcmp(strtmp,"players") == 0){
        	for(int i=0; i<30; i++)
                {
                if(strlen(jogador[i].username)>0)
                    printf("%s %d\n", jogador[i].username, jogador[i].pidP);
                }
        }
        else if (strcmp(strtmp,"games") == 0){
        	// lista jogo
        }
        else if (strcmp(strtmp,"exit") == 0){
        	encerra();
        }
        
   }while(1);
   
   exit(5);
   
   //Jogo();
}

#include "headerServer.h"
#include "header.h"
#include <string.h>
#include <pthread.h>


//Leitura de Variaveis de ambiente
//export MAXPLAYER="..."
//export GAMEDIR="..."

int nJ;
char directory;
char Mplayers;

void * ThreadAtribuirJogo(){
    PEDIDO p;
    int continua = 1;
    char fifo[40];
    int fd,fdr, bytes;
    srand(time(NULL));
    do{
    if(nJ >= 3){
            printf("Jogos serão atribuidos em 15 seg\n");
            sleep(5); // irá mudar para tempo_espera
            for(int i = 0; i < nJ ; i++){
                    jogo[i].nJogo = (rand() % 3)+1;
                    jogo[i].pidJ = i;
                    jogador[i].pidJogoAtribuido = jogo[i].nJogo;

                    if(jogo[i].nJogo == 1){
                            strcpy(jogo[i].nomeJogo,"JOGO DE ADIVINHAR O NUMERO");
                    }
                    else if(jogo[i].nJogo == 2){
                            strcpy(jogo[i].nomeJogo,"JOGO DE ACERTAR A CONTA");
                    }
                    else if(jogo[i].nJogo == 3){
                            strcpy(jogo[i].nomeJogo,"JOGO DE QUIZ");
                    }

                    printf("Jogo %s atribuido ao jogador: %s\n", jogo[i].nomeJogo, jogador[i].username);
                    fflush(stdout);

            }
            continua = 0;
        }
    }while(continua);
}

void * ThreadComandosCliente(void * arg){

  PEDIDO p;
  int fd,fdr, bytes;
  char fifo[40];
  int i, flag=0;
  pthread_t tAtribuir;

  fd = open(FIFO_SRV, O_RDWR); // -1 = ERRO
  printf("Abri o FIFO\n");

  do {
       bytes = read(fd, &p, sizeof(PEDIDO));
       
       //COMANDO #GAME
       if(strcmp(p.ordem,"#mygame") == 0){
         printf("Recebi comando -> %s : cliente -> %d [%d bytes]\n", p.ordem,p.pid, bytes);
         strcpy(p.resposta, "Comando enviado com sucesso.");
       
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         // print da informação do jogo atribuido
         
         
         //COMANDO #QUIT
       }else if(strcmp(p.ordem,"#quit") == 0){
         printf("Recebi comando -> %s : cliente -> %d [%d bytes]\n", p.ordem,p.pid, bytes);
         strcpy(p.resposta, "Comando enviado com sucesso");
       
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         // sai do jogo , possivelmente dando unlink do fifo ao qual está conectado
       }
       
       //COMANDO LOGIN
       else if(strcmp(p.ordem,"login") == 0) {
         printf("Recebi comando -> %s : cliente -> %d [%d bytes]\n", p.ordem,p.pid, bytes);
         if(nJ != 0){
            for(i=0;i<nJ;i++){
                if(strcmp(jogador[i].username, p.user)==0){
                    printf("%s = %s", jogador[i].username, p.user);
                    strcpy(p.resposta, "ERRO");
                    flag=1;
                    break;
                }
               
            }
         }

        if(flag != 1) {
            strcpy(p.resposta, "Sucesso no Login!");
            jogador[nJ].pidP = p.pid;
            strcpy(jogador[nJ].username,p.user);
            jogador[nJ].pontuacao = 0;
            jogador[nJ].inGame=0;        
            nJ++;
        }
         
         sprintf(fifo, FIFO_CLI, p.pid);
         fdr = open(FIFO_CLI, O_WRONLY);
         bytes = write(fdr, &p, sizeof(PEDIDO));
         close(fdr);
         printf("Enviei... %s [%d bytes]\n", p.resposta, bytes);
         flag=0;
         // sai do jogo , possivelmente dando unlink do fifo ao qual está conectado
       }
            
       
       //COMANDO DESCONHECIDO
       else{
         printf("Recebi -> %s : cliente -> %d [%d bytes]\n", p.ordem,p.pid, bytes);
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

    directory = getenv("GAMEDIR");
    if(directory != NULL)
    for (int i =0 ; i < 30 ; i++){
          strcpy(jogo[i].gameDir, directory);
        }
    Mplayers = getenv("MAXPLAYER");
    if(Mplayers != NULL)
        campeonato.maxplayers = atoi(Mplayers);


    if(campeonato.maxplayers <= 0 || campeonato.maxplayers >= 30){
        campeonato.maxplayers = 20;
    }

    printf("Directoria: %s\n", jogo[0].gameDir);
    printf("MaxPlayers: %d\n", campeonato.maxplayers);
    

}

void encerra(){
    printf("A encerrar o arbitro...\n");
            
    for(int i=0; i<30; i++){
      kill(jogador[i].pidP, SIGINT);
    }
    
    unlink(FIFO_SRV);
    
    sleep(5);
    exit(0);
}


void main(int argc, char *argv[]) {
   PEDIDO p;
   int option;
   int fd, fdr, bytes;
   char fifo[40], strtmp[40], str[3][40];
   pthread_t tComandos, tAtribuir;
   
   //criar named pipe do servidor
    if(access(FIFO_SRV, F_OK) != 0){ //caso o fifo/servidor ainda nao exista
        mkfifo(FIFO_SRV, 0600);
    }
   printf("SERVIDOR LANCADO!!!\nFIFO CRIADO\n");
   
   
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
   
   
   
   //Thread para receber comandos
    pthread_create(&tComandos, NULL, ThreadComandosCliente, NULL);
    
    //Thread para esperar os jogadores e atribuir jogos
    pthread_create(&tAtribuir, NULL, ThreadAtribuirJogo, NULL);
    
    
    
   do{
   	printf("\nComando: ");
        fflush(stdout);
        scanf("%s",&strtmp);

    	if (strncmp(strtmp,"k",1) == 0){
    		memcpy(str, strtmp+1,sizeof(strtmp));
        	for(int i=0; i<30; i++){
                if(strcmp(str, jogador[i].username)==0){
                    kill(jogador[i].pidP, SIGUSR1);
                    printf("Kick: %s", str);
                }
            }
        }
    	else if (strcmp(strtmp,"players") == 0){
        	for(int i=0; i<30; i++)
                {
                if(strlen(jogador[i].username)>0)
                    printf("%s %d - Jogo: %d\n", jogador[i].username, jogador[i].pidP, jogador[i].pidJogoAtribuido);
                }
        }
        else if (strcmp(strtmp,"games") == 0){
        	// listar os jogos disponiveis
        }
        else if (strcmp(strtmp,"exit") == 0){
        	encerra();
        }
        else if (strncmp(strtmp,"s",1) == 0){
        	//encerra comunicaçao entre arbitro e cliente em questao
        }
        else if (strncmp(strtmp,"r",1) == 0){
        	//retoma comunicaçao entre arbitro e cliente em questao
        }
        else if (strcmp(strtmp,"end") == 0){
        	//encerra campeonato imediatamente
        }
        
   }while(1);
   
   exit(5);
   
   //Jogo();
}

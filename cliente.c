#include "headerCliente.h"
#include "header.h"

void Sinal(int sig){

	if( sig == SIGUSR1){
		// unlink do fifo do jogo
	}
	
	if( sig == SIGINT){
		printf("Conexão ao arbitro irá encerrar!\n");
		sleep(3);
		char fifoClienteTmp[40];
		sprintf(fifoClienteTmp , FIFO_CLI, getpid());
		unlink(fifoClienteTmp);
		exit(0);
	}

}

void main() {   
    PEDIDO p;
    char username[25];
    char str[40], fifo[40];
    int fd, fdr, num;
    int bytes;
    
    signal(SIGUSR1, Sinal);
    signal(SIGINT, Sinal);

    if(access(FIFO_SRV, F_OK) != 0){ //caso o fifo/servidor ainda nao exista
        fprintf(stderr, "[ERRO] O servidor nao esta a funcionar\n");
        exit(5);
    }

    printf("Insira o Username: ");
    scanf("%s", username);

    printf("[%s|%d]] Eu sou o Cliente!\n", username, getpid());
    
    p.pid = getpid();
    sprintf(fifo, FIFO_CLI, p.pid);
    
    mkfifo(fifo,0600);  /* FIFO_CLI --> fifo  */
    printf("Criei o meu FIFO (cliente)...\n");
    
    fd = open(FIFO_SRV, O_WRONLY);
    printf("Abri o FIFO do servidor...\n");
    
    do{
        //Pede ordens ao cliente
        printf("Ordem: ");
        fflush(stdout);
        scanf("%s", &p.ordem);
        
        bytes = write(fd, &p, sizeof(PEDIDO));
        printf("Enviei... %s [%d bytes]\n", p.ordem, bytes);
        
        fdr = open(FIFO_CLI, O_RDONLY);
        bytes = read(fdr, &p,sizeof(PEDIDO));
        close(fdr);
        printf("Recebi %s [%d bytes]\n", p.resposta, bytes);
    }while(strcmp(p.ordem, "sair"));
        
    close(fd);
    unlink (fifo);
    exit(5);
}

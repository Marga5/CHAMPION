#include "headerCliente.h"
#include "header.h"

void Sinal(int sig){

	PEDIDO p;

	char fifo[40];
    	int fd, fdr;
    	int bytes;

	if( sig == SIGUSR1){
		printf("Foste Kickado do jogo.\n");
	}
	
	if( sig == SIGINT){
		printf("Conexão ao arbitro irá encerrar!\n");
		sleep(3);
		char fifoClienteTmp[40];
		sprintf(fifoClienteTmp , FIFO_CLI, getpid());
		unlink(fifoClienteTmp);
		exit(0);
	}
	
	if ( sig == SIGUSR2){
	
		p.pid = getpid();
    		sprintf(fifo, FIFO_CLI, p.pid);
    
    		mkfifo(fifo,0600);  /* FIFO_CLI --> fifo  */
    		
		fd = open(FIFO_SRV, O_WRONLY);
		strcpy(p.ordem, "#mygame");
		bytes = write(fd, &p, sizeof(PEDIDO));
        
        	fdr = open(FIFO_CLI, O_RDONLY);
       	 bytes = read(fdr, &p,sizeof(PEDIDO));
        	close(fdr);
        	printf("Recebi %s [%d bytes]\n", p.resposta, bytes);
	
	}

}

void main() {   
    PEDIDO p;
    
    char username[25];
    char str[40], fifo[40];
    int fd, fdr, num ;
    int bytes;
    
    signal(SIGUSR1, Sinal);
    signal(SIGINT, Sinal);
    signal(SIGUSR2, Sinal);

    if(access(FIFO_SRV, F_OK) != 0){ //caso o fifo/servidor ainda nao exista
        fprintf(stderr, "[ERRO] O servidor nao esta a funcionar\n");
        exit(5);
    }

        
    sprintf(fifo, FIFO_CLI, p.pid);
    
    mkfifo(fifo,0600);  /* FIFO_CLI --> fifo  */
    printf("Criei o meu FIFO (cliente)...\n");
    
    fd = open(FIFO_SRV, O_WRONLY);
    printf("Abri o FIFO do servidor...\n");
    
    printf("Insira o Username: ");
    fflush(stdout);
    scanf("%s", username);
    strcpy(p.ordem, "login");
    p.pid = getpid();
    strcpy(p.user, username);
    bytes = write(fd, &p, sizeof(PEDIDO));
    
    fdr = open(FIFO_CLI, O_RDONLY);
    bytes=read(fdr, &p, sizeof(PEDIDO));
    close(fdr);
    printf("Recebi [%s] - [%d bytes]\n", p.resposta, bytes);
    if(strcmp(p.resposta, "ERRO")==0){
        printf("Nome de utilizador já existe\n");
        exit(0);
    }

    printf("[%s|%d] Eu sou o Cliente!\n", username, getpid());
    
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

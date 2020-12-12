#include "header.h"

void main(){
    int num1, num2, resultado, resposta, pontuacao=0;
    time_t diff;
    time_t start = time(NULL);
    int tempo_campeonato = 20;
    printf("\n-------------------------------------\n");
    printf(" JOGO DE ACERTAR A CONTA! ");
    printf("\n-------------------------------------\n\n");
    
    printf("Neste jogo o jogador terá que responder correctamente \no resultado da expressão que irá aparecer.\nPor cada resposta certa recebe um ponto! \n\nBoa Sorte\n\n");
    
    do{
        srand (time(NULL));
        
        num1 = rand()%15 + 1;
        num2 = rand()%15 + 1;
        resultado = num1 + num2;
        
        printf("%d + %d = ", num1, num2);
        scanf("%d", &resposta);
        
        if(resposta == resultado){
            printf("Acertou! +1 ponto\n\n");
            pontuacao++;
        }
        else
            printf("Resposta Errada\n\n");
        
        diff = time(NULL)-start;
    }while(diff < tempo_campeonato);
       
    printf("Fim do Jogo! \nConseguiu %d Pontos\nParabens!\n\n", pontuacao);
    
    exit(pontuacao);
       
}
#include "header.h"


void Jogo()
{
    time_t start = time(NULL);
    int pont=0;
    int randNum;
    int num;
    int resposta = 1;
    time_t diff;
    printf("\n-------------------------------------\n");
    printf(" JOGO DE ADIVINHAR O NUMERO! ");
       printf("\n-------------------------------------\n\n");
    
    do{
        srand (time(NULL));
        printf("Adivinha um numero de 1 a 5! - ");
        scanf("%d",&num);
        while(num < 1 || num > 5){
            printf("--> Numero inválido!\n--> Escolha entre o 1 e o 5\n");
            scanf("%d",&num);             
        }

        randNum = rand()%5 + 1;

        if(num != randNum){
            printf("Erraste! O numero certo era o %d\n",randNum);
            resposta = -1;
        }else{
            printf("--> Acertaste! Numero dado: %d , Numero gerado: %d <--\n", num,randNum);
            pont++;
        }
        diff = time(NULL)-start;
        printf("Tempo: %d\n", diff);

    }while ( diff < tempo_campeonato);
    
    exit(pont);

}

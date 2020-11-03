#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream
=======

int main(int argc, char *argv[])
{
	int randNum;
	int num;
	int resposta = 1;

	do{
        srand (time(NULL));
        printf("Adivinha um numero de 1 a 5! - ");
        scanf("%d",&num);

        randNum = rand()%5 + 1;

        if(num != randNum){
            printf("Erraste! O numero certo era o %d\n",randNum);
            resposta = -1;
        }else
            printf("Acertaste! Numero dado: %d , Numero gerado: %d\n", num,randNum);

	}while (resposta == 1);

    return 0;
}
>>>>>>> Stashed changes

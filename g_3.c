#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#include "header.h"

#define NUM_STRING 4
#define MAX_STRING_SIZE 60

void main (){
    time_t start = time(NULL);
    time_t diff;
    int pont=0, i=0;
    
    char perg1 [NUM_STRING][MAX_STRING_SIZE] = {"Quem foi o segundo homem a pisar a lua?", "Neil Armstrong", "Alan Shepard", "Buzz aldrin"}; //Buzz Aldrin
    char perg2 [NUM_STRING][MAX_STRING_SIZE] = {"Quem pintou o quadro 'Guernica'?", "Salvador Dali", "Pablo Picasso", "Edgar Degas"}; //Pablo Picasso
    char perg3 [NUM_STRING][MAX_STRING_SIZE] = {"Onde nasceu Almada Negreiros?", "Angola", "Cabo Verde", "Sao Tome e Principe"}; //Sao Tome e Principe
    char perg4 [NUM_STRING][MAX_STRING_SIZE] = {"Quem foi o primeiro portugues a ganhar um Nobel?", "Jose Saramago", "Egas Moniz", "Miguel Torga"}; //Egas Moniz
    char perg5 [NUM_STRING][MAX_STRING_SIZE] = {"Quantos fusos horários tem a Rússia?","Um", "Cinco", "Onze"}; //Onze
    char perg6 [NUM_STRING][MAX_STRING_SIZE] = {"De que cidade são os Beatles?", "Londres", "Liverpool", "Manchester"}; //Liverpool
    char perg7 [NUM_STRING][MAX_STRING_SIZE] = {"Quando foi fundada a Netflix?", "2009", "1997", "2001"}; //1997
    char perg8 [NUM_STRING][MAX_STRING_SIZE] = {"Qual o número minimo de jogadores numa partida de futebol?", "Sete", "Nove", "Cinco"}; //Sete
    char perg9 [NUM_STRING][MAX_STRING_SIZE] = {"Qual o maior animal terrestre?", "Dinossauro", "Elefante Africano", "Girafa"}; //Elefante Aficano
    char perg10 [NUM_STRING][MAX_STRING_SIZE] = {"Em que oceano fica Madagascar?", "Índico", "Pacífico", "Ártico"}; //Índico
    
    
    
    printf("\n-------------------------------------\n");
    printf(" JOGO DE TRIVIA! ");
    printf("\n-------------------------------------\n\n");
    
    printf("Neste jogo o jogador tera que acertar ao maior numero de respostas as perguntas feitas! \n\nBoa Sorte\n");
    
    do{
        int resp;
        if(i==0){
            printf("\n%s\n",  perg1[0]);
            printf("1- %s\n", perg1[1]);
            printf("2- %s\n", perg1[2]);
            printf("3- %s\n", perg1[3]);
            scanf("%d", &resp);
            if(resp == 3)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        
        else if (i==1){
            printf("\n%s\n",  perg2[0]);
            printf("1- %s\n", perg2[1]);
            printf("2- %s\n", perg2[2]);
            printf("3- %s\n", perg2[3]);
            scanf("%d", &resp);
            if(resp == 2)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        
        else if (i==2){
            printf("\n%s\n",  perg3[0]);
            printf("1- %s\n", perg3[1]);
            printf("2- %s\n", perg3[2]);
            printf("3- %s\n", perg3[3]);
            scanf("%d", &resp);
            if(resp == 3)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        
        else if (i==3){
            printf("\n%s\n",  perg4[0]);
            printf("1- %s\n", perg4[1]);
            printf("2- %s\n", perg4[2]);
            printf("3- %s\n", perg4[3]);
            scanf("%d", &resp);
            if(resp == 2)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==4){
            printf("\n%s\n",  perg5[0]);
            printf("1- %s\n", perg5[1]);
            printf("2- %s\n", perg5[2]);
            printf("3- %s\n", perg5[3]);
            scanf("%d", &resp);
            if(resp == 3)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==5){
            printf("\n%s\n",  perg6[0]);
            printf("1- %s\n", perg6[1]);
            printf("2- %s\n", perg6[2]);
            printf("3- %s\n", perg6[3]);
            scanf("%d", &resp);
            if(resp == 2)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==6){
            printf("\n%s\n",  perg7[0]);
            printf("1- %s\n", perg7[1]);
            printf("2- %s\n", perg7[2]);
            printf("3- %s\n", perg7[3]);
            scanf("%d", &resp);
            if(resp == 2)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==7){
            printf("\n%s\n",  perg8[0]);
            printf("1- %s\n", perg8[1]);
            printf("2- %s\n", perg8[2]);
            printf("3- %s\n", perg8[3]);
            scanf("%d", &resp);
            if(resp == 1)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==8){
            printf("\n%s\n",  perg9[0]);
            printf("1- %s\n", perg9[1]);
            printf("2- %s\n", perg9[2]);
            printf("3- %s\n", perg9[3]);
            scanf("%d", &resp);
            if(resp == 2)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
        else if (i==9){
            printf("\n%s\n",  perg10[0]);
            printf("1- %s\n", perg10[1]);
            printf("2- %s\n", perg10[2]);
            printf("3- %s\n", perg10[3]);
            scanf("%d", &resp);
            if(resp == 1)
            {
                printf("Correcto!!!\n");
                pont++;
            }
            else
                printf("Errado!\n");
        }
      
        i++;
        
        diff = time(NULL)-start;
        printf("Tempo: %d\n", diff);
    }while(i != 10 || diff < tempo_campeonato);
    printf("Fim do Jogo! \nConseguiu %d Pontos\nParabens!\n\n", pont);
    exit(pont);
    
}
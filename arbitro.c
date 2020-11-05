#include "header.h"

void main(int argc, char *argv[]) {
   int option;
   // put ':' at the starting of the string so compiler can distinguish between '?' and ':'
   while((option = getopt(argc, argv, ":if:t:d:")) != -1){ //get option from the getopt() method
      switch(option){  
         case 't':
             tempo_espera = atoi(optarg);
            printf("Tempo de Espera definido para: %d\n", tempo_espera);
            
            break;
         case 'd': //here f is used for some file name
            
            tempo_campeonato = atoi(optarg);
            printf("Duracao do campeonato definido para: %d\n", tempo_campeonato);
            break;
          case ':':
            printf("Opcao precisa de um valor\n");
            break;

         case '?': //used for some unknown options
            printf("unknown option: %c\n", optopt);
            break;
      }
   }
   for(; optind < argc; optind++){ //when some extra arguments are passed
      printf("Given extra arguments: %s\n", argv[optind]);
   }
   
   printf("SERVIDOR LANCADO!!!\n");
   
   Jogo();
}
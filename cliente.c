#include <stdio.h>
#include <stdlib.h>

#include "header.h"

void main() {   
    char username[25];
        printf("Insira o Username: ");
	scanf("%s", username);

	printf("[%s|%d]] Eu sou o Cliente!\n", username, getpid());
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i, numero, tamanho = 200;
    printf("intervalo da rand: [0,%d]\n", RAND_MAX);
    srand((unsigned) time(NULL));//USAR NA MAIN

    for(i=1 ; i <= 100 ; i++){
        //srand((unsigned) time(NULL));
        numero = 1+(rand() % tamanho); //gera um número entre 1 e tamanho, que nesse caso é 200
        printf("Numero %d: %d\n",i, numero);
}
}

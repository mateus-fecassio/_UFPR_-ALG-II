#include <stdio.h>
#include <stdlib.h>

int main(){
   int i;
   system("clear"); // Limpar a tela
   printf("Loading"); // Exibir a Palavra Loading na tela em branco

   for(i=0;i < 10; i++){ // abrir um laço de repetição com for
   system("sleep 01"); // pausa de 1 segundo
   printf("."); // escrever 1 "." na tela
   fflush(stdout); // atualizar a tela
   }
}

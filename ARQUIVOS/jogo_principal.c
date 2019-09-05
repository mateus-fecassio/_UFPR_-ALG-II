#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mochila.h"
#include "funcoes.h"
//----------------------------------------------------------- FUNÇÃO PRINCIPAL ----------------------------------------------------------------//
int main (int argc, char *argv[]){
	char labirinto [20][30];
	mochila *mochilha_de_pokemons = (mochila *) malloc (sizeof (mochila));
	//pilha *coordenadas = (pilha *) malloc (sizeof (pilha));

	short entrada, saida, resolucao;
	int linha, coluna;
  	int *lin = (int *) malloc (sizeof(int));
  	int *col = (int *) malloc (sizeof(int));
	

	//argv[1] contém o nome do arquivo .txt de labirinto
	//argv[2] contém o nome do arquivo .txt do banco de dados de pokemons que será utilizado
	if (argv[1] == NULL || argv[2] == NULL){
		printf("ERRO! o formato correto para o funcionamento desde programa é: ./nome_do_programa nome_do_labirinto.txt banco_de_pokemons.txt \n");
		exit (0);
	}


	inicializar_mochila (mochilha_de_pokemons);
	colocar_pokemons_lista (argv[2], mochilha_de_pokemons);
	
	//verifica a quantidade de pokemons (se o número de pokemons na mochila for inferior a 4, o jogo não pode funcionar!)
	if (mochilha_de_pokemons->tamanho < 4){
		printf("ERRO! Para o programa funcionar corretamente, é preciso de um banco de dados de Pokemons maior do que este. \n");
	}

	
	colocar_mapa_matriz (argv[1], labirinto);
	entrada = insere_entrada (labirinto, lin, col);
  	saida = insere_saida (labirinto);
	

	srand ((unsigned) time(NULL)); //passa diferentes sementes para a função aleatório
	//batalha (mochilha_de_pokemons); //apenas para teste
	
	colocar_itens_restauracao (labirinto);
	colocar_inimigos (labirinto);
	linha = *lin;
	coluna = *col;
	resolucao = resolver_labirinto (labirinto, 20, 30, linha, coluna, mochilha_de_pokemons);
	if (resolucao == 0)
		printf("\nEITA! ESSE LABIRINTO NÃO TEM SAÍDA!\n");
	else
		printf("\n[USUÁRIO] UFA! SAÍ DO LABIRINTO!!\n");
}//end int main (int argc, char *argv[])
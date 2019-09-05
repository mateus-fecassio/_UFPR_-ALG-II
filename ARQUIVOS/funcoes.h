#ifndef __FUNCOES__
#define __FUNCOES__

void inicializar_mochila (mochila *M);
void colocar_mapa_matriz (char *nome, char labirinto[20][30]);
void imprimir_matriz (char labirinto[20][30]);
void colocar_pokemons_lista (char *pokemos, mochila *M);
noh * busca (mochila *m, int x);
noh *escolha_do_pokemon (mochila *M, noh *POC);
int sorteio (int tamanho);
void restaura_vida (mochila *M);
void colocar_itens_restauracao (char labirinto[20][30]);
void colocar_inimigos (char labirinto[20][30]);
double calcular_probabilidade ();
short insere_entrada (char labirinto[20][30], int *lin, int *col);
short insere_saida(char labirinto[20][30]);
void batalha (mochila *M);
short resolver_labirinto (char labirinto[20][30], int numl, int numc, int l, int c, mochila *M);

#endif
#ifndef __MOCHILA__
#define __MOCHILA__

typedef struct pokemon {
	int identificador;
	char nome[20];
	double HP;
	double backup_HP;
	double peso;
	double altura;
} pokemon;

typedef struct noh { //contém os nós em particular
	pokemon P;
	struct noh *proximo;
} noh;

typedef struct mochila { //contém o CONJUNTO de nós
	int tamanho; //tamanho da mochila de pokemons
	struct noh *cabeca;
	struct noh *cauda;
} mochila;
#endif
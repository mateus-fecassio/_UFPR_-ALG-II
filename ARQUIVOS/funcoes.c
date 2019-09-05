#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mochila.h"
#include "funcoes.h"

void inicializar_mochila (mochila *M) {
	M->tamanho = 0;
	M->cabeca = NULL;
	M->cauda = NULL;
} //TERMINADO


void colocar_mapa_matriz (char *nome, char labirinto[20][30]){
    short linha, coluna;
    char ch;

    FILE *file; //ponteiro para o tipo arquivo
    file = fopen (nome, "r"); //função que retorna um PONTEIRO para o ponteiro file

    for (linha = 0; linha < 20; linha ++){
        for (coluna = 0; coluna < 30; coluna ++){
        do {
            ch = fgetc(file);
            } while(ch == '\n' || ch == '\r');
                labirinto[linha][coluna] = ch;
        }
    }
        fclose (file);
} //TERMINADO


void imprimir_matriz (char labirinto[20][30]){
	short linha, coluna;

	system("clear");
	//fflush(stdout); // atualizar a tela
	system("sleep 0.20"); // pausa de 0.2 segundos para imprimir o pŕóximo labirinto
	for (linha=0; linha<20; linha++){
	  for (coluna=0; coluna<30; coluna++){
	        printf("%c", labirinto[linha][coluna]);
		}
		printf("\n");
	}
	//system("clear");
	fflush(stdout); // atualizar a tela
} //TERMINADO(?)

void colocar_pokemons_lista (char *pokemons, mochila *M){
	char linha [50];
	char *toklinha;

	int identificador;
	char nome[20];
	double HP;
	double peso;
	double altura;


	FILE *arquivo;
	arquivo = fopen (pokemons, "r");

	if (arquivo == NULL){
		printf("NÃO FOI POSSÍVEL ABRIR O ARQUIVO! TENTE NOVAMENTE.");
		exit(0);
	}

	while (fscanf (arquivo, "%s", linha) != EOF){
		//CRIAR NOVO NÓ
		noh *novo = (noh *) malloc (sizeof(noh));
		if (novo == NULL){
			printf("NÃO FOI POSSÍVEL ALOCAR O NOVO NÓ! ERRO NA FUNÇÃO OU ESPAÇO INSIFICIENTE.\n");
			exit (0);
		}
		novo->proximo = NULL;
		
		//INSERIR ESSE NOVO NÓ NA MOCHILA
		if (M->cabeca == NULL) {
			M->cabeca = novo;
			M->cauda = novo;
		} else {
			M->cauda->proximo = novo;
			M->cauda = novo;
		}
		M->tamanho ++;

		toklinha = strtok (linha, ",");
		sscanf (toklinha, "%i", &identificador);
		novo->P.identificador = identificador;
		//printf("IDENTIFICADOR: %i\n", novo->P.identificador);


		toklinha = strtok (NULL, ",");
		sscanf (toklinha, "%s", nome);
		strcpy (novo->P.nome, nome);
		//printf("NOME: %s\n", novo->P.nome);


		toklinha = strtok (NULL, ",");
		sscanf (toklinha, "%lf", &HP);
		novo->P.HP = HP;
		novo->P.backup_HP = HP;
		//printf("HP: %i\n", novo->P.HP);


		toklinha = strtok (NULL, ",");
		sscanf (toklinha, "%lf", &peso);
		novo->P.peso = peso;
		//printf ("PESO: %i \n", novo->P.peso);


		toklinha = strtok (NULL, ",");
		sscanf (toklinha, "%lf", &altura); //antes estava lf
		novo->P.altura = altura;
		//printf("ALTURA: %.0lf\n", novo->P.altura);

		//printf("\n");
	}

	fclose (arquivo);;
}//TERMINADO


noh *busca (mochila *m, int x){

	noh *aux;
	int cont = 1;
	aux = m->cabeca;
	while (cont != x){
		aux= aux->proximo;
		cont ++;
	}
	return aux;	
} //TERMINADO

int sorteio (int tamanho){
	int num;
	num = rand() % tamanho;
	//printf("SORTEADO: %i \n", num);
	
	return num;
} //TERMINADO

noh *escolha_do_pokemon (mochila *M, noh *POC){
	int sort;
	sort = 1 + sorteio (M->tamanho); //sorteia um númeoro entre 1 e o tamanho da lista (mochila) de pokemons

	POC = busca (M, sort);
	return POC;
} //TEMRINADO

void restaura_vida (mochila *M){
	int i;
	noh *auxiliar;
	auxiliar = M->cabeca;

	while (auxiliar != NULL){
		auxiliar->P.HP = auxiliar->P.backup_HP;
		auxiliar = auxiliar->proximo;
	}
	//system("clear");
	fflush(stdout);
   	printf("RESTAURANDO A VIDA DE SEUS PERSONAGENS"); 

   	for (i = 0; i < 4; i++){ 
   		system("sleep 1");
   		printf("."); 
   		fflush(stdout); //atualiza a tela
   	}
   	system("sleep 0.8");
   	printf ("\nRESTAURADO COM SUCESSO! \n");
   	system("sleep 1");
   	system("clear");
   	//fflush(stdout);
   	return;
} //TERMINADO (?) TESTAR!


double calcular_probabilidade (){
	double numero;
	numero = (double)rand() / (double)RAND_MAX;

	//printf("PROBABILIDADE: %g \n", numero);
	return numero;
} //TERMINADO


void batalha (mochila *M){
	pokemon personagem, adversario;
	noh *PERSONAGEM = (noh *) malloc (sizeof (noh));
	noh *ADVERSARIO = (noh *) malloc (sizeof (noh));

	double limite, probabilidade, poder_de_ataque;
	int mortos = 0;

	//VERIFICAR SE HÁ POKEMONS VIVOS
	noh *auxiliar;
	auxiliar = M->cabeca;
	while (auxiliar != NULL){
		if (auxiliar->P.HP == 0)
			mortos ++;
		auxiliar = auxiliar->proximo;
	}

	//system("clear");
	if (mortos == M->tamanho){
		printf("[USUÁRIO] OH, NÃO! TODOS OS POKEMONS ESTÃO MORTOS!  CORREEEE \n");
		system("sleep 2");
		return;
	}
	


	//ESCOLHA DO ADVERSÁRIO
	ADVERSARIO = escolha_do_pokemon (M, ADVERSARIO); //PONTEIRO PARA POKEMON
	adversario = ADVERSARIO->P;//POKEMON
	if (adversario.HP == 0)
		adversario.HP = ADVERSARIO->P.backup_HP;

	//ESCOLHA DO PERSONAGEM DIFERENTE DO ADVERSÁRIO
	PERSONAGEM = escolha_do_pokemon (M, PERSONAGEM);
	while (PERSONAGEM->P.HP == 0 || PERSONAGEM->P.identificador == ADVERSARIO->P.identificador){
		PERSONAGEM = escolha_do_pokemon (M, PERSONAGEM);
	}
	personagem = PERSONAGEM->P;
	//system("clear");
	//fflush(stdout); // atualizar a tela

	printf("[USUÁRIO] OH, NÃO! UM INIMIGO! \n");
	system("sleep 2");
	printf("[USUÁRIO] %s, EU ESCOLHO VOCÊ! \n",personagem.nome);
	system("sleep 2");
	printf("[%s] AHAHAHAHA, VOCÊ NÃO É PÁREO PARA MIM, %s, EU SOU %s, O MAIOR DE TODOS OS POKEMONS!!\n", adversario.nome, personagem.nome, adversario.nome);
	system("sleep 2");
	printf("[%s] É O QUE VEREMOS :D \n", personagem.nome);
	system("sleep 2");
	printf("A BATALHA VAI COMEÇAR!\n");
	system("sleep 1");
	printf("3 ");
	system("sleep 2");
	fflush(stdout);
	printf("2 ");
	system("sleep 2");
	fflush(stdout);
	printf("1 \n");
	system("sleep 2");
	fflush(stdout);
	printf("GO GO GO GO GO \n");
	system("sleep 0.5");

	while ((personagem.HP > 0) && (adversario.HP > 0)){
		//PRIMEIRO ATAQUE: PERSONAGEM
		limite = 0.1 * personagem.HP;
		probabilidade = calcular_probabilidade();
		
		if (limite >= probabilidade){
			poder_de_ataque = personagem.peso / personagem.altura;
			adversario.HP = adversario.HP - poder_de_ataque;
		
		printf ("____________________________________________________________________\n");
		printf ("+++ %s ATACOU!                                               \n", personagem.nome);
		printf ("+++ ATAQUE: %g                                               \n", poder_de_ataque);
		printf ("_____________________________xxxxxxxxxx_____________________________\n");
		printf ("        			--- %s FOI ATINGIDO! \n", adversario.nome);
		if (adversario.HP > 0)
			printf ("        			---  PONTOS DE VIDA RESTANTE: %g\n", adversario.HP);
		else
			printf ("        			---  PONTOS DE VIDA RESTANTE: 0\n");
		printf ("____________________________________________________________________\n");
		}



		printf("\n \n \n \n \n \n ");
		system("sleep 0.01");

		//SEGUNDO ATAQUE: ADVERSÁRIO
		limite = 0.1 * adversario.HP;
		probabilidade = calcular_probabilidade();
		if (limite >= probabilidade){
			poder_de_ataque = adversario.peso / adversario.altura;	
			personagem.HP = personagem.HP - poder_de_ataque;

		printf ("____________________________________________________________________\n");
		printf ("+++ %s ATACOU!                                               \n", adversario.nome);
		printf ("+++ ATAQUE: %g                                               \n", poder_de_ataque);
		printf ("_____________________________xxxxxxxxxx_____________________________\n");
		printf ("        			--- %s FOI ATINGIDO! \n", personagem.nome);
		if (personagem.HP > 0)
			printf ("        			---  PONTOS DE VIDA RESTANTE: %g\n", personagem.HP);
		else
			printf ("        			---  PONTOS DE VIDA RESTANTE: 0\n");
		printf ("____________________________________________________________________\n");
		}
		
		printf("\n \n \n");
		system("sleep 0.01");
	}

	if (adversario.HP <= 0){
		printf("[%s] HAHAHAHAHA QUEIME NO FOGO DO INFERNO, %s! \n", personagem.nome, adversario.nome);
		system("sleep 2");
		printf ("SEU PERSONAGEM GANHOU! \n");
	}
	
	if (personagem.HP <= 0){
		printf("[%s] HAHAHAHAH EU DISSE QUE VOCÊ NÃO SERIA PÁREO PARA O GRANDE %s, PEQUENO %s!\n", adversario.nome, adversario.nome, personagem.nome);
		system("sleep 2");
		printf ("O ADVERSÁRIO GANHOU! \n");
	}
	
	if (personagem.HP < 0)
		personagem.HP = 0;
	
	system("sleep 2");
	fflush(stdout); // atualizar a tela
	PERSONAGEM->P = personagem; //ATUALIZA A LISTA DE POKEMON PARA O NOVO HP DO PERSONAGEM AO FINAL DA BATALHA
	return;
} //TERMINADO


void colocar_itens_restauracao (char labirinto[20][30]){
	int total, x, y, contador, verificador;

	total = 2 + sorteio (8); //total de itens de restauração entre 2 e 10 no máximo
	
	contador = 0;
	while (contador < total){
		verificador = 0;
		while (verificador == 0){
			x = sorteio (20);
			y = sorteio (30);

			if (labirinto[x][y] == ' ')
				verificador = 1;
		}
		labirinto[x][y] = '?';
		contador ++;
	}
} //TERMINADO


void colocar_inimigos (char labirinto[20][30]){
	int total, x, y, contador, verificador;
	
	contador = 0;
	while (contador < 3){
		verificador = 0;
		while (verificador == 0){
			x = sorteio (20);
			y = sorteio (30);

			if (labirinto[x][y] == ' ')
				verificador = 1;
		}
		labirinto[x][y] = 'X';
		contador ++;
	}
} //TERMINADO

short insere_entrada (char labirinto[20][30], int * lin, int * col){
	short linha, coluna;
		for (linha = 0; linha < 20; linha ++){//percorre o labirinto no topo
        	for (coluna = 0; coluna < 30; coluna ++){
        		if (labirinto[linha][coluna] == ' '){
					labirinto[linha][coluna]= '8';
    				*lin = linha;//guarda a linha
    				*col = coluna;//guarda a coluna
    				return 1;  
				}
			}
		}
	printf("[função] AS COORDENADAS DO INÍCIO SÃO: (X = %d;Y = %d) \n", *lin, *col);
} //TERMINADO (?)

short insere_saida (char labirinto[20][30]){
	short linha, coluna;
    for (linha = 19; linha >= 0; linha --)//percorre o labirinto embaixo
    	for (coluna = 29; coluna >= 0; coluna --)
    		if (labirinto[linha][coluna] == ' ' || labirinto[linha][coluna] == '='){
				labirinto[linha][coluna]= '=';
				return 1;
    		}
} //TERMINADO (?)


short resolver_labirinto (char labirinto[20][30], int numl, int numc, int l, int c, mochila *M) {
  if (labirinto[l][c] == '=')
    return 1;
  
  if (labirinto[l][c] == 'X')
  		batalha (M);
  	else
  		if (labirinto[l][c] == '?')
  		restaura_vida (M);

  labirinto[l][c] = '8';
  imprimir_matriz(labirinto);

  if (labirinto[l+1][c] == ' ' || labirinto[l+1][c] == '=' || labirinto[l+1][c] == 'X' || labirinto[l+1][c] == '?')
    if (resolver_labirinto(labirinto, numl, numc, l+1, c, M))
      	return 1;
 

  if (labirinto[l][c+1] == ' ' || labirinto[l][c+1] == '=' || labirinto[l][c+1] == 'X' || labirinto[l][c+1] == '?')
    if (resolver_labirinto(labirinto, numl, numc, l, c+1, M))
      return 1;

  
  if (labirinto[l-1][c] == ' ' || labirinto[l-1][c] == '=' || labirinto[l-1][c] == 'X' || labirinto[l-1][c] == '?')
    if (resolver_labirinto(labirinto, numl, numc, l-1, c, M))
      return 1;

  
  if (labirinto[l][c-1] == ' ' || labirinto[l][c-1] == '=' || labirinto[l][c-1] == 'X' || labirinto[l][c-1] == '?')
    if (resolver_labirinto(labirinto, numl, numc, l, c-1, M))
      return 1;
  
  return 0;
}

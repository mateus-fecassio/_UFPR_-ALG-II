#include <stdio.h>

#define MAX 20
#define FMAX 100

typedef struct {
  int x[FMAX];
  int y[FMAX];
  int inicio;
  int fim;
} tfila;

void inicia(tfila *f) {
  f->inicio = 0;
  f->fim = 0;
}

int vazia(tfila *f) {
  if(f->inicio == f->fim)
    return 1;
  return 0;
}

int enfilera(tfila *f, int l, int c) {
  if((f->fim + 1) % FMAX == f->inicio)
    return 0;
  f->x[f->fim] = l;
  f->y[f->fim] = c;
  f->fim = (f->fim + 1) % FMAX;
  return 1;
}

int desenfilera(tfila *f, int *l, int *c) {
  if(vazia(f))
    return 0;
  *l = f->x[f->inicio];
  *c = f->y[f->inicio];
  f->inicio = (f->inicio + 1) % FMAX;
  return 1;
}
   
void carrega_labirinto(char lab[][MAX], int *l, int *c) {
  int i, j;

  scanf("%d", l);
  scanf("%d\n", c);

  for(i = 0; i < *l; i++)
    for(j = 0; j <= *c; j++)
      scanf("%c", &lab[i][j]);
}

void mostra_labirinto(char lab[][MAX], int l, int c) {
  int i, j;

  for(i = 0; i < l; i++)
    for(j = 0; j <= c; j++)
      printf("%c", lab[i][j]);
}

void main() {
  char lab[MAX][MAX];
  int l, c, i, j;
  tfila f;

  carrega_labirinto(lab, &l, &c);
  mostra_labirinto(lab, l, c);
  inicia(&f);
  i = 1;
  j = 1;
  while(lab[i][j] != 'X') {
    lab[i][j] = '.';
    if(lab[i][j-1] == ' ' || lab[i][j-1] == 'X') {
      if(lab[i][j-1] == ' ')
        lab[i][j-1] = '?';
      enfilera(&f, i, j-1); 
    }
    if(lab[i-1][j] == ' ' || lab[i-1][j] == 'X') {
      if(lab[i-1][j] == ' ')
        lab[i-1][j] = '?';
      enfilera(&f, i-1, j); 
    }
    if(lab[i][j+1] == ' ' || lab[i][j+1] == 'X') {
      if(lab[i][j+1] == ' ')
        lab[i][j+1] = '?';
      enfilera(&f, i, j+1); 
    }
    if(lab[i+1][j] == ' ' || lab[i+1][j] == 'X') {
      if(lab[i+1][j] == ' ')
        lab[i+1][j] = '?';
      enfilera(&f, i+1, j); 
    }
    mostra_labirinto(lab, l, c);
    if(!desenfilera(&f, &i, &j)) {
      printf("labirinto sem saida!\n");
      return;
    }
  }
}

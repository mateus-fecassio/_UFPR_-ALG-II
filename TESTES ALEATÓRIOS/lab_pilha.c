#include <stdio.h>

#define MAX 20
#define PMAX 100

typedef struct {
  int x[PMAX];
  int y[PMAX];
  int topo;
} tpilha;

void inicia(tpilha *p) {
  p->topo = -1;
}

int vazia(tpilha *p) {
  if(p->topo == -1)
    return 1;
  return 0;
}

int empilha(tpilha *p, int l, int c) {
  if(p->topo == PMAX-1)
    return 0;
  p->topo++;
  p->x[p->topo] = l;
  p->y[p->topo] = c;
  return 1;
}

int desempilha(tpilha *p, int *l, int *c) {
  if(p->topo == -1)
    return 0;
  *l = p->x[p->topo];
  *c = p->y[p->topo];
  p->topo--;
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
  tpilha p;

  carrega_labirinto(lab, &l, &c);
  mostra_labirinto(lab, l, c);
  inicia(&p);
  i = 1;
  j = 1;
  while(lab[i][j] != 'X') {
    lab[i][j] = '.';
    mostra_labirinto(lab, l, c);
    if(lab[i+1][j] == ' ' || lab[i+1][j] == 'X')
      empilha(&p, i+1, j); 
    if(lab[i][j+1] == ' ' || lab[i][j+1] == 'X')
      empilha(&p, i, j+1); 
    if(lab[i-1][j] == ' ' || lab[i-1][j] == 'X')
      empilha(&p, i-1, j); 
    if(lab[i][j-1] == ' ' || lab[i][j-1] == 'X')
      empilha(&p, i, j-1); 
    if(!desempilha(&p, &i, &j)) {
      printf("labirinto sem saida!\n");
      return;
    }
  }
}

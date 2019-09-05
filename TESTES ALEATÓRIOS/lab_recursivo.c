#include <stdio.h>

#define MAX 20

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

int sai(char lab[][MAX], int numl, int numc, int l, int c) {
  if(lab[l][c] == 'X')
    return 1;
  lab[l][c] = '.';
  mostra_labirinto(lab, numl, numc);
  if(lab[l+1][c] == ' ' || lab[l+1][c] == 'X')
    if(sai(lab, numl, numc, l+1, c))
      return 1;
  if(lab[l][c+1] == ' ' || lab[l][c+1] == 'X')
    if(sai(lab, numl, numc, l, c+1))
      return 1;
  if(lab[l-1][c] == ' ' || lab[l-1][c] == 'X')
    if(sai(lab, numl, numc, l-1, c))
      return 1;
  if(lab[l][c-1] == ' ' || lab[l][c-1] == 'X')
    if(sai(lab, numl, numc, l, c-1))
      return 1;
  return 0;
}

void main() {
  char lab[MAX][MAX];
  int l, c;

  carrega_labirinto(lab, &l, &c);
  mostra_labirinto(lab, l, c);

  sai(lab, l, c, 1, 1);  
}

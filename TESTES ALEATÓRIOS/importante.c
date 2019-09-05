#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//SEPARAÇÃO DOS POKEMONS PARA COLOCAR NA LISTA (MODELO)
typedef struct /* Anonymous */ { 
	int converted_1;
	double converted_2;
	char converted_3[128];
} my_struct_t;

int main() {
	char *line;
	char *token;
	FILE *file;
	my_struct_t my_struct;

	file = fopen("./example.txt", "r");

	if (file == NULL) {
		perror("unable to open file");
		return -1;
	}

	while (fscanf(stdin, "%ms", &line) != EOF) {
		token = strtok(line, ",");
		sscanf(token, "%i", &my_struct.converted_1);
		token = strtok(NULL, ",");
		sscanf(token, "%lf", &my_struct.converted_2);
		token = strtok(NULL, ",");
		sscanf(token, "%s", my_struct.converted_3);

		printf("<%i,%lf,%s>\n", my_struct.converted_1, my_struct.converted_2, my_struct.converted_3);

		free(line);
	}

	return 0;
}

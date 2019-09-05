


void insere_entrada_e_saida(char labirinto[20][30], int * lin, int * col){
	short linha, coluna;
		for (linha = 0; linha < 20; linha ++){//percorre o labirinto no topo
        	for (coluna = 0; coluna < 30; coluna ++){
        		if (labirinto[linha][coluna] == ' '){
					labirinto[linha][coluna]= '8';
    				*lin = linha;//guarda a linha
    				*col = coluna;//guarda a coluna  
				}
			}
		}


    	for (linha = 19; linha >= 0; linha --)//percorre o labirinto embaixo
    		for (coluna = 29; coluna >= 0; coluna --)
    			if (labirinto[linha][coluna] == ' ')
					labirinto[linha][coluna]= '=';
  
}


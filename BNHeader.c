#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BNHeader.h"

int menu() {
	int escolha;
	
	printf("\t### WARSHIPS ###\n\n\t Batalha Naval\n\n");
	printf(" (1) Solo\n (2) Contra I.A.\n (3) Sair\n\n > ");

	scanf(" %d", &escolha);
	
	switch (escolha) {
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		default:
			exit(0);		
	}
}

int verificaDisponibilidade(Ponto **matriz, int x, int y, int n, int direcao, int num) {

	if(direcao == NORTE) {
		if(matriz[x][y].y + n >= num) {
			return 1;
		} else if(n >= 5 && matriz[x][y+4].ocupado == 1) {
			return 1;
		} else if(n >= 4 && matriz[x][y+3].ocupado == 1) {
			return 1;
		} else if(n >= 3 && matriz[x][y+2].ocupado == 1) {
			return 1;
		} else if(n >= 2 && matriz[x][y+1].ocupado == 1) {
			return 1;
		} else if(n >= 1 && matriz[x][y].ocupado == 1) {
			return 1;
		}
	} else if(direcao == SUL) {
		if(matriz[x][y].y - n < 0) {
			return 1;
		} else if(n >= 5 && matriz[x][y-4].ocupado == 1) {
			return 1;
		} else if(n >= 4 && matriz[x][y-3].ocupado == 1) {
			return 1;
		} else if(n >= 3 && matriz[x][y-2].ocupado == 1) {
			return 1;
		} else if(n >= 2 && matriz[x][y-1].ocupado == 1) {
			return 1;
		} else if(n >= 1 && matriz[x][y].ocupado == 1) {
			return 1;
		}
	} else if(direcao == LESTE) {
		if(matriz[x][y].x + n >= num) {
			return 1;
		} else if(n == 5 && matriz[x+4][y].ocupado == 1) {
			return 1;
		} else if(n >= 4 && matriz[x+3][y].ocupado == 1) {
			return 1;
		} else if(n >= 3 && matriz[x+2][y].ocupado == 1) {
			return 1;
		} else if(n >= 2 && matriz[x+1][y].ocupado == 1) {
			return 1;
		} else if(n >= 1 && matriz[x][y].ocupado == 1) {
			return 1;
		}
	} else if(direcao == OESTE) {
		if(matriz[x][y].x - n <= 0) {
			return 1;
		} else if(n >= 5 && matriz[x-4][y].ocupado == 1) {
			return 1;
		} else if(n >= 4 && matriz[x-3][y].ocupado == 1) {
			return 1;
		} else if(n >= 3 && matriz[x-2][y].ocupado == 1) {
			return 1;
		} else if(n >= 2 && matriz[x-1][y].ocupado == 1) {
			return 1;
		} else if(n >= 1 && matriz[x][y].ocupado == 1) {
			return 1;
		}
	}
	
	return 0;
}

void extendeBarco(Ponto **matriz, int x, int y, int tamanho, int direcao) {
	
	if(direcao == NORTE) {
		if(tamanho >= 5) {
			matriz[x][y+4].ocupado = 1;
			matriz[x][y+4].tamanho = tamanho;
		}
		if(tamanho >= 4) {
			matriz[x][y+3].ocupado = 1;
			matriz[x][y+3].tamanho = tamanho;
		}
		if(tamanho >= 3) {
			matriz[x][y+2].ocupado = 1;
			matriz[x][y+2].tamanho = tamanho;
		}
		if(tamanho >= 2) {
			matriz[x][y+1].ocupado = 1;
			matriz[x][y+1].tamanho = tamanho;
		}
	} else if(direcao == SUL) {
		if(tamanho >= 5) {
			matriz[x][y-4].ocupado = 1;
			matriz[x][y-4].tamanho = tamanho;
		}
		if(tamanho >= 4) {
			matriz[x][y-3].ocupado = 1;
			matriz[x][y-3].tamanho = tamanho;
		}
		if(tamanho >= 3) {
			matriz[x][y-2].ocupado = 1;
			matriz[x][y-2].tamanho = tamanho;
		}
		if(tamanho >= 2) {
			matriz[x][y-1].ocupado = 1;
			matriz[x][y-1].tamanho = tamanho;
		}
	} else if(direcao == LESTE) {
		if(tamanho >= 5) {
			matriz[x+4][y].ocupado = 1;
			matriz[x+4][y].tamanho = tamanho;
		}
		if(tamanho >= 4) {
			matriz[x+3][y].ocupado = 1;
			matriz[x+3][y].tamanho = tamanho;
		}
		if(tamanho >= 3) {
			matriz[x+2][y].ocupado = 1;
			matriz[x+2][y].tamanho = tamanho;
		}
		if(tamanho >= 2) {
			matriz[x+1][y].ocupado = 1;
			matriz[x+1][y].tamanho = tamanho;
		}
	} else if(direcao == OESTE) {
		if(tamanho >= 5) {
			matriz[x-4][y].ocupado = 1;
			matriz[x-4][y].tamanho = tamanho;
		}
		if(tamanho >= 4) {
			matriz[x-3][y].ocupado = 1;
			matriz[x-3][y].tamanho = tamanho;
		}
		if(tamanho >= 3) {
			matriz[x-2][y].ocupado = 1;
			matriz[x-2][y].tamanho = tamanho;
		} 
		if(tamanho >= 2) {
			matriz[x-1][y].ocupado = 1;
			matriz[x-1][y].tamanho = tamanho;
		}
	}
}

void defineBarcos(Ponto **matriz, int num) {	
	srand(time(NULL));
	
	int i, j, x, y, a, tamanho = 0, tamanhos[4] = {0,0,0,0}, direcao;
	
	//Gera 10 barcos
	
	for(i = 0; i < 10; i++) {
		x = rand() % num;
		y = rand() % num;
		direcao = 1 + rand() % 4;

		//Tamnho dos barcos (maior -> menor)
		if(i == 0) {
			tamanho = 5;
		} else if(i > 0 && i <= 2) {
			tamanho = 4;
		} else if(i > 2 && i <= 5) {
			tamanho = 3;
		} else if(i > 5) {
			tamanho = 2;
		}
		
		//Teste de tamanhos
		if(tamanho == 2 && tamanhos[0] >= 4 ) {
			i--;
			continue;
		} else if(tamanho == 3 && tamanhos[1] >= 3) {
			i--;
			continue;
		} else if(tamanho == 4 && tamanhos[2] >= 2) {
			i--;
			continue;
		} else if(tamanho == 5 && tamanhos[3] >= 1) {
			i--;
			continue;
		}
		
		if(tamanho == 2) {
			if(verificaDisponibilidade(matriz, x, y, tamanho, direcao, num) == 1) {
				i--;
				continue;	
			}
			tamanhos[0] = tamanhos[0] + 1;
		} else if(tamanho == 3) {
			if(verificaDisponibilidade(matriz, x, y, tamanho, direcao, num) == 1) {
				i--;
				continue;
			}
			tamanhos[1] = tamanhos[1] + 1;
		} else if(tamanho == 4) {
			if(verificaDisponibilidade(matriz, x, y, tamanho, direcao, num) == 1) {
				i--;
				continue;	
			}
			tamanhos[2] = tamanhos[2] + 1;
		} else if(tamanho == 5) {
			if(verificaDisponibilidade(matriz, x, y, tamanho, direcao, num) == 1) {
				i--;
				continue;	
			}
			tamanhos[3] = tamanhos[3] + 1;
		}
				
		matriz[x][y].x = x;
		matriz[x][y].y = y;
		matriz[x][y].ocupado = 1;
		matriz[x][y].atingido = 0;
		matriz[x][y].tamanho = tamanho;
		extendeBarco(matriz, x, y, tamanho, direcao);
	}	
}

Ponto** alocaMatriz(int num) {
	int i;
	Ponto** matriz = (Ponto**) malloc(num * sizeof(Ponto*));
	for(i = 0; i < num; i++) matriz[i] = (Ponto*) malloc(num * sizeof(Ponto));
	return matriz;
}

void defineEspacos(Ponto **matriz, int num) {
	int i, j;
	
	for(i = 0; i < num; i++) {
		for(j = 0; j < num; j++) {
			matriz[i][j].x = i;
			matriz[i][j].y = j;
			matriz[i][j].atingido = 0;
			matriz[i][j].ocupado = 0;
			matriz[i][j].tamanho = 0;
		}
	}
}

void printaMatriz(Ponto **matriz, int num) {
	char letras[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int i, j, a;

	printf("   ");
	for(a = 0; a < num; a++) {
		printf("%.2d ", a+1);
	}
	printf("\n");
	
	for(i = 0; i < num; i++) {
		printf(" %c ", letras[i]);
		
		for(j = 0; j < num; j++) {
			if (matriz[i][j].atingido == 0 && matriz[i][j].ocupado == 0) printf("[] ");
			else if (matriz[i][j].atingido == 1 && matriz[i][j].ocupado == 0) printf("~~ ");
			else if (matriz[i][j].atingido == 0 && matriz[i][j].ocupado == 1) printf("<%d ", matriz[i][j].tamanho);
			else if (matriz[i][j].atingido == 1 && matriz[i][j].ocupado == 1) printf("XX ");
		}
		
		printf("\n");
	}
}

int selecionaCoordenada(Ponto **matriz, int num, int pontos) {
	int numero, x, y;
	char letra;
	
	printf("Selecione a coordenada que deseja atingir:\nLetra: ");
	scanf(" %c", &letra);
	printf("Numero: ");
	scanf("%d", &numero);
	
	if(letra == 'A' || letra == 'a') x = 1;
	if(letra == 'B' || letra == 'b') x = 2;
	if(letra == 'C' || letra == 'c') x = 3;
	if(letra == 'D' || letra == 'd') x = 4;
	if(letra == 'E' || letra == 'e') x = 5;
	if(letra == 'F' || letra == 'f') x = 6;
	if(letra == 'G' || letra == 'g') x = 7;
	if(letra == 'H' || letra == 'h') x = 8;
	if(letra == 'I' || letra == 'i') x = 9;
	if(letra == 'J' || letra == 'j') x = 10;
	if(letra == 'K' || letra == 'k') x = 11;
	if(letra == 'L' || letra == 'l') x = 12;
	if(letra == 'M' || letra == 'm') x = 13;
	if(letra == 'N' || letra == 'n') x = 14;
	if(letra == 'O' || letra == 'o') x = 15;
	if(letra == 'P' || letra == 'p') x = 16;
	if(letra == 'Q' || letra == 'q') x = 17;
	if(letra == 'R' || letra == 'r') x = 18;
	if(letra == 'S' || letra == 's') x = 19;
	if(letra == 'T' || letra == 't') x = 20;
	if(letra == 'U' || letra == 'u') x = 21;
	if(letra == 'V' || letra == 'v') x = 22;
	if(letra == 'W' || letra == 'w') x = 23;
	if(letra == 'X' || letra == 'x') x = 24;
	if(letra == 'Y' || letra == 'y') x = 25;
	if(letra == 'Z' || letra == 'z') x = 26;
	
	y = numero;
	
	matriz[x-1][y-1].atingido = 1;
	
	if(matriz[x-1][y-1].ocupado == 1) {
		pontos++;
	}
	
	return pontos;
}

int checkWinCondition(Ponto **matriz, int tamanho) {
	int i, j, counter = 0;
	
	for(i = 0; i < tamanho; i++) {
		for(j = 0; j < tamanho; j++) {
			if(matriz[i][j].ocupado == 1 && matriz[i][j].atingido == 1) {
				counter++;
			}
		}
	}
	
	if(counter >= 30) {
		return 1;
	}
	return 0;
}

int jogadaIA(Ponto **matriz, int num, int pontos) {
	srand(time(NULL));
	
	int x, y, i = 0;
	
	do {
		x = rand() % num;
		y = rand() % num;
	
		if(matriz[x][y].atingido == 1) {
			i = 0;
			continue;
		}
		i++;
	} while(i < 2);
	
	matriz[x][y].atingido = 1;
	
	if(matriz[x][y].ocupado == 1) {
		pontos++;
	}
	
	return pontos;
}







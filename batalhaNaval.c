#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BNHeader.h"

int main()
{
	int menuChoice;
	menuChoice = menu();
		
	Ponto **matriz;
	clock_t start;
	int timer, contador = 0, pontosJ = 0, pontosIA = 0;
	
	start = clock();
	
	int num;
	
	printf("Defina o tamanho da matriz:\n(10 a 26)\n");
	scanf("%d", &num);
	
	
	if(num > 26 || num < 10) {
		printf("Valor(es) invalido(s).");
		exit(0);
	}
	
	system("cls");
	matriz = alocaMatriz(num);
	
	defineEspacos(matriz, num);
	defineBarcos(matriz, num);
	
	for(;;) {
	//	clock_t current = clock() - start;
	//	timer = current * 1000 / CLOCKS_PER_SEC;
	//	printf("Timer: %lf\n", timer);
		if(menuChoice == 1) {
			printaMatriz(matriz, num);
			selecionaCoordenada(matriz, num, pontosJ);
			system("cls");
			if(checkWinCondition(matriz, num) == 1) {
				break;
			}
		} else if(menuChoice == 2) {
			printaMatriz(matriz, num);
			if(contador % 2) {
				selecionaCoordenada(matriz, num, pontosJ);
			} else {
				jogadaIA(matriz, num, pontosIA);
			}
			contador++;
			system("cls");
			if(checkWinCondition(matriz, num) == 1) {
				break;
			}
		}
	}
	
	printf("Victory!\n");
	
	return 0;
}

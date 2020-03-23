#ifndef BNHeader
#define BNHeader

#define NORTE 1
#define SUL   2
#define LESTE 3
#define OESTE 4

typedef struct ponto {
	int x;
	int y;
	int atingido;
	int ocupado;
	int tamanho;
} Ponto;

typedef struct barco {
	int x;
	int y;
	int tamanho;
} Barco;

int menu();

Ponto** alocaMatriz(int num);

void defineEspacos(Ponto **matriz, int num);

void defineBarcos(Ponto **matriz, int num);

void printaMatriz(Ponto **matriz, int num);

int selecionaCoordenada(Ponto **matriz, int num, int pontos);

int checkWinCondition(Ponto **matriz, int tamanho);

int jogadaIA(Ponto **matriz, int num, int pontos);

#endif

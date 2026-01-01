#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Armazena Valores
struct Matriz {
	int somaSubQuad1;
	int somaSubQuad2;
	int somaSubQuad3;
	int somaSubQuad4;
	int somaTotal;
};

typedef struct Matriz somas;

// Soluções Retornadas
#define N_SOLUCOES 3

int solucoes_encontradas = 0;

void inicializaMatriz(int matriz[10][10]);
int verificarCriterio1(int matriz[10][10], int linha, int coluna, int numero);
// int verificarCriterio2(somas* ArmazenaMatriz);
int verificarCriterio3(int matriz[10][10], int linha, int coluna, int numero);
int verificarCriterio4(double k, somas* ArmazenaMatriz);
int verificaTudo(int matriz[10][10], int linha, int coluna, int numero);
void resolveProblema(int matriz[10][10], double k, somas* ArmazenaSomas);
int resolveProblemaRecursivo(int matriz[10][10], int linha, int coluna, double k, somas* ArmazenaSomas);
void printMatriz(int matriz[10][10]);

void inicializaMatriz(int matriz[10][10]) {

	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			matriz[i][j] = 0;
		}
	}
}

// Regras:

// 1 - Não podem haver mais de duas repetições em uma mesma diagonal. Por exemplo, se o número 1 ocorre duas vezes na diagonal principal, e também o 3, então outro outro número qualquer não pode mais repetir-se nessa diagonal.

int verificarCriterio1(int matriz[10][10], int linha, int coluna, int numero) {

	// Vê quantas vezes os números se repetem
	int repeticoes[9] = {0,0,0,0,0,0,0,0,0};

	// Vê quantas vezes um número repetiu mais de 2 vezes
	int repetidos = 0;

	int aux;

	// Volta na Matriz
	while(linha > 1 && coluna > 1) {

		linha--;
		coluna--;
	}

	int a = linha - 1;
	int b = coluna - 1;

	// Avanço até a diagonal terminar
	while (a < 10 && b < 10) {

		aux = matriz[a][b];
		if(aux != 0) repeticoes[aux - 1]++;
		a++;
		b++;
	}

	for(int i = 0; i < 9; i++) {

		if(repeticoes[i] >= 2) repetidos++;
	}

	if(repeticoes[numero - 1] >= 1 && repetidos >= 2) return 0;

	return 1;
}

/*

// DESCONSIDERADO 2 - A soma dos números de um mesmo subquadrante 5x5 não pode exceder a de outro subquadrante em mais de 20%.

int verificarCriterio2(somas* ArmazenaMatriz) {

	int valores[5] = {ArmazenaMatriz->somaSubQuad1, ArmazenaMatriz->somaSubQuad2, ArmazenaMatriz->somaSubQuad3, ArmazenaMatriz->somaSubQuad4, ArmazenaMatriz->somaTotal};

	for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            if (i == j) continue;

            if (valores[i] > valores[j] * 1.20) {

                return 0;
            }
        }
    }

	return 1;
}

*/

// 3 - Nenhum número pode repetir-se em sua vizinhança, ou seja, na figura abaixo, nenhuma célula vazia pode ser preenchida com o número 5 novamente.

// - - -
// - 5 -
// - - -

int verificarCriterio3(int matriz[10][10], int linha, int coluna, int numero) {

	int sequencia_linha = linha - 2;
	int sequencia_coluna = coluna - 2;

	for(int i = 0; i < 8; i++) {

		if(sequencia_coluna == -1) sequencia_coluna ++;
		if(sequencia_linha == -1) sequencia_linha ++;

		if(sequencia_linha == linha - 1 && sequencia_coluna == coluna - 1) {

			continue;
		}

		if(matriz[sequencia_linha][sequencia_coluna] == numero) return 0;

		sequencia_coluna ++;
		if(sequencia_coluna == coluna + 1) {

			sequencia_linha ++;
			sequencia_coluna = coluna - 2;
		}
	}

	return 1;
}

// 4 - Seja a soma dos elementos do sub quadrante i, 5x5, igual a Si, e a soma de todos os elementos da matriz geral igual a St. Então | Si - Sj | / St < k, para algum k entre zero e um, dado como parâmetro.

int verificarCriterio4(double k, somas* ArmazenaMatriz) {

	int valores[5] = {ArmazenaMatriz->somaSubQuad1, ArmazenaMatriz->somaSubQuad2, ArmazenaMatriz->somaSubQuad3, ArmazenaMatriz->somaSubQuad4, ArmazenaMatriz->somaTotal};

	// Nenhum valor
	if (valores[4] == 0)
    	return 1;

	for(int i = 0; i < 4; i++) {

		for(int j = 0; j < 4; j++) {

			if(i == j) continue;

			double dif = fabs((double)valores[i] - valores[j]);
            double razao = dif / (double)valores[4];

            if (razao >= k) {

                return 0;
            }
		}
	}

	return 1;
}

int verificaTudo(int matriz[10][10], int linha, int coluna, int numero) {

	int ver1, ver3;

	ver1 = verificarCriterio1(matriz, linha, coluna, numero);
	if(ver1 == 0) return 0;

	ver3 = verificarCriterio3(matriz,linha,coluna,numero);
	if(ver3 == 0) return 0;

	return 1;
}

void printMatriz(int matriz[10][10]) {

	printf("\n");
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			printf("[%d] ",matriz[i][j]);
		}
		printf("\n");
	}
}

void resolveProblema(int matriz[10][10], double k, somas* ArmazenaSomas) {

	resolveProblemaRecursivo(matriz, 1, 1, k, ArmazenaSomas);

	if (solucoes_encontradas == 0)
		printf("\nSem solução.\n");
	else
		printf("\nTotal de soluções encontradas: %d\n", solucoes_encontradas);
}

int resolveProblemaRecursivo(int matriz[10][10], int linha, int coluna, double k, somas* ArmazenaSomas) {

	int soma = 5;
	int aux;

    if (coluna == 6) {
        coluna = 1;
        linha++;
    }

    if (linha == 6) {

		solucoes_encontradas++;

		printf("\n=== Solução %d ===\n", solucoes_encontradas);
		printMatriz(matriz);

		if (solucoes_encontradas >= N_SOLUCOES)
			return 1;

		return 0;
	}

	for (int num = 1; num <= 9; num++) {

		if (verificaTudo(matriz, linha, coluna, num) == 1) {
			matriz[linha - 1][coluna - 1] = num;
			ArmazenaSomas->somaSubQuad1 += num;
			ArmazenaSomas->somaTotal += num;

			for (int num2 = 1; num2 <= 9; num2++) {

				if (verificaTudo(matriz, linha, coluna + soma, num2) == 1) {
					matriz[linha - 1][coluna - 1 + soma] = num2;
					ArmazenaSomas->somaSubQuad2 += num2;
					ArmazenaSomas->somaTotal += num2;

					for (int num3 = 1; num3 <= 9; num3++) {

						if (verificaTudo(matriz, linha + soma, coluna, num3) == 1) {
							matriz[linha - 1 + soma][coluna - 1] = num3;
							ArmazenaSomas->somaSubQuad3 += num3;
							ArmazenaSomas->somaTotal += num3;

							for (int num4 = 1; num4 <= 9; num4++) {

								if (verificaTudo(matriz, linha + soma, coluna + soma, num4) == 1) {
									matriz[linha - 1 + soma][coluna - 1 + soma] = num4;
									ArmazenaSomas->somaSubQuad4 += num4;
									ArmazenaSomas->somaTotal += num4;

									aux = verificarCriterio4(k, ArmazenaSomas);

									if(aux == 1) {

										if (resolveProblemaRecursivo(matriz, linha, coluna + 1, k, ArmazenaSomas) == 1)
											return 1;
									}

									matriz[linha - 1 + soma][coluna - 1 + soma] = 0;
									ArmazenaSomas->somaSubQuad4 -= num4;
									ArmazenaSomas->somaTotal -= num4;
								}

							}

							matriz[linha - 1 + soma][coluna - 1] = 0;
							ArmazenaSomas->somaSubQuad3 -= num3;
							ArmazenaSomas->somaTotal -= num3;
						}

					}

					matriz[linha - 1][coluna - 1 + soma] = 0;
					ArmazenaSomas->somaSubQuad2 -= num2;
					ArmazenaSomas->somaTotal -= num2;
				}

			}

			matriz[linha - 1][coluna - 1] = 0;
			ArmazenaSomas->somaSubQuad1 -= num;
			ArmazenaSomas->somaTotal -= num;
		}
	}

	return 0;
}

int main() {

	int matriz[10][10];
	float k;
	somas ArmazenaSomas = {0,0,0,0,0};

	printf("Valor k: ");
	scanf("%f",&k);

	inicializaMatriz(matriz);

	printMatriz(matriz);

	resolveProblema(matriz, k, &ArmazenaSomas);

	printf("%d\n%d\n%d\n%d\n%d",ArmazenaSomas.somaSubQuad1,ArmazenaSomas.somaSubQuad2,ArmazenaSomas.somaSubQuad3, ArmazenaSomas.somaSubQuad4, ArmazenaSomas.somaTotal);

	return 0;
}

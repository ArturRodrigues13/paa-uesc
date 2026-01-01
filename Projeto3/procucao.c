#include <stdio.h>
#include <limits.h>

#define LINHAS 3
#define COLUNAS 30
#define INF 1000000000

int custoEntrada[LINHAS] = {1, 3, 5};
int custoSaida[LINHAS]   = {2, 4, 6};

int custoProducao[LINHAS][COLUNAS] = {

	// Custo Linha 1
    {7,5,4,8,3,12,1,4,5,8,2,7,9,6,14,3,10,11,2,15,4,8,13,7,1,12,5,9,6,14},

	// Custo Linha 2
    {5,5,9,3,8,2,14,6,11,4,7,15,1,9,5,12,3,10,6,8,14,2,11,7,4,13,1,9,15,1},

	// Custo Linha 3
    {7,3,12,5,9,1,14,6,8,4,15,2,11,10,13,5,7,9,3,12,6,14,1,8,4,11,2,10,15,13}
};

int transporteMesmaLinha[LINHAS][COLUNAS-1] = {

	// Custo Transporte 1
    {1,2,1,5,3,7,2,6,4,1,7,5,3,6,2,4,1,5,7,3,6,2,4,1,5,7,3,6,2},

	// Custo Transporte 2
    {1,2,1,5,3,7,2,6,4,1,7,5,3,6,2,4,1,5,7,3,6,2,4,1,5,7,3,6,2},

	// Custo Transporte 3
    {2,1,3,6,4,7,1,5,2,6,3,7,4,1,5,2,6,3,7,4,1,5,2,6,3,7,4,1,2}
};

int transporteOutraLinha[LINHAS][LINHAS][COLUNAS-1] = {

	// Linha 1 pra outra Linha
    {
		// Não tem Custo trocar para ele mesmo
        {0},

		// Custo Transportar para Linha 2
        {3,6,2,7,1,5,4,2,6,3,5,1,7,4,2,6,3,5,1,7,4,2,6,3,5,1,7,4,2},

		// Custo Transportar para Linha 3
        {4,1,7,3,6,2,5,7,1,4,2,6,3,5,7,1,4,2,6,3,5,7,1,4,2,6,3,5,7}
    },

	// Linha 2 pra outra Linha
    {
		// Custo Transportar para Linha 1
        {5,2,7,4,1,6,3,7,2,5,6,4,1,3,7,2,5,6,4,1,3,7,2,5,6,4,1,3,7},

		// Não tem Custo trocar para ele mesmo
        {0},

		// Custo Transportar para Linha 3
        {4,7,1,6,3,2,5,1,4,7,2,6,3,5,1,4,7,2,6,3,5,1,4,7,2,6,3,5,1}
    },

	// Linha 3 pra outra Linha
    {
		// Custo Transportar para Linha 1
        {6,3,5,1,7,4,2,5,6,3,1,7,4,2,5,6,3,1,7,4,2,5,6,3,1,7,4,2,5},

		// Custo Transportar para Linha 2
        {7,4,2,5,1,6,3,2,7,4,5,1,6,3,2,7,4,5,1,6,3,2,7,4,5,1,6,3,2},

		// Não tem Custo trocar para ele mesmo
        {0}
    }
};

int f[LINHAS][COLUNAS];
int l[LINHAS][COLUNAS];
int caminho[COLUNAS];

int main() {

    // Transportando Do Começo Para a Primeira Etapa
    for (int i = 0; i < LINHAS; i++) {
        f[i][0] = custoEntrada[i] + custoProducao[i][0];
        l[i][0] = -1;
    }

    // Loops Principais
	for (int etapaAtual = 1; etapaAtual < COLUNAS; etapaAtual++) {

		// Para cada linha possível onde posso terminar essa etapa
		for (int linhaDestino = 0; linhaDestino < LINHAS; linhaDestino++) {

			int melhorCusto = INF;
			int melhorLinhaOrigem = -1;

			// Testa de qual linha eu vim na etapa anterior
			for (int linhaOrigem = 0; linhaOrigem < LINHAS; linhaOrigem++) {

				int tempoTotal;

				// Caso 1: continuei na mesma linha
				if (linhaOrigem == linhaDestino) {
					tempoTotal =
						f[linhaOrigem][etapaAtual - 1] +
						transporteMesmaLinha[linhaDestino][etapaAtual - 1] +
						custoProducao[linhaDestino][etapaAtual];
				}

				// Caso 2: troquei de linha
				else {
					tempoTotal =
						f[linhaOrigem][etapaAtual - 1] +
						transporteOutraLinha[linhaOrigem][linhaDestino][etapaAtual - 1] +
						custoProducao[linhaDestino][etapaAtual];
				}

				// Verifica se encontrou um valor menor
				if (tempoTotal < melhorCusto) {
					melhorCusto = tempoTotal;
					melhorLinhaOrigem = linhaOrigem;
				}
			}

			// Salva o melhor custo e de onde ele veio
			f[linhaDestino][etapaAtual] = melhorCusto;
			l[linhaDestino][etapaAtual] = melhorLinhaOrigem;
		}
	}


    // Tabela F
    printf("\nTabela F (custos acumulados):\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            printf(" (%d,%d) = %4d |", i+1, j+1, f[i][j]);
        printf("\n\n");
    }

    // Tabela L
    printf("\nTabela L (predecessores):\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 1; j < COLUNAS; j++)
            printf("(%d,%d)<-(%d,%d)  ", i+1, j+1, l[i][j]+1, j);
        printf("\n\n");
    }

    // Resultado final
    int melhorTempo = INF;
    int melhorLinha = -1;
    for (int i = 0; i < LINHAS; i++) {
        int total = f[i][COLUNAS-1] + custoSaida[i];
        if (total < melhorTempo) {
            melhorTempo = total;
            melhorLinha = i;
        }
    }

    printf("\nTempo mínimo total = %d (linha final %d)\n", melhorTempo, melhorLinha+1);

	// Reconstrução do caminho ótimo
	caminho[COLUNAS - 1] = melhorLinha;

	for (int etapa = COLUNAS - 1; etapa > 0; etapa--) {
		caminho[etapa - 1] = l[caminho[etapa]][etapa];
	}

	printf("\nCaminho ótimo (linha, etapa):\n");
	for (int j = 0; j < COLUNAS; j++) {
		printf("(%d,%d) ", caminho[j] + 1, j + 1);
	}
	printf("\n");

    return 0;
}

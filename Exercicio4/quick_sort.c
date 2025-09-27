#include <stdio.h>
#include <stdlib.h>

int particiona(int* vetor, int inicio, int final);

void quick_sort(int* vetor, int inicio, int final);

void print_vetor(int* vetor, int tamanho);

int main() {

	int	vetor[10] = {10,24,8,21,6,54,4,3,9999,7};

	print_vetor(vetor, 10);

	quick_sort(vetor, 0, 9);

	print_vetor(vetor,10);
}

int particiona(int* vetor, int inicio, int final) {

	int pivo = vetor[inicio];
	int aux;

	int E = inicio + 1;
	int D = final;

	while (1 < 2) {
		while (E < final && vetor[E] < pivo) E++;

		while (D > inicio && vetor[D] >= pivo) D--;

		if(E >= D) break;

		aux = vetor[E];
		vetor[E] = vetor[D];
		vetor[D] = aux;
	}

	vetor[inicio] = vetor[D];

	vetor[D] = pivo;

	return D;
}

void quick_sort(int* vetor, int inicio, int final) {

	if(inicio < final) {

		int p = particiona(vetor,inicio,final);
		quick_sort(vetor, inicio, p-1);
		quick_sort(vetor, p+1, final);
	}
}

void print_vetor(int* vetor, int tamanho) {

	printf("Vetor: ");

	for (int i = 0; i < tamanho; i++) {

		printf("[%d] ",vetor[i]);
	}

	printf("\n");
}

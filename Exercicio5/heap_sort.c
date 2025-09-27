#include <stdio.h>
#include <stdlib.h>

void sift(int* vetor, int i, int n);

void build(int *vetor, int n);

void heap_sort(int* vetor, int n);

void print_vetor(int* vetor, int tamanho);

int main() {

	int	vetor[10] = {10,24,8,21,6,54,4,3,9999,7};

	print_vetor(vetor, 10);

	heap_sort(vetor, 9);

	print_vetor(vetor,10);
}

void sift(int* vetor, int i, int n) {

	int esq = 2 * i + 1;
	int dir = 2 * i + 2;
	int aux;
	int maior = i;

	if(esq <= n && vetor[esq] > vetor[maior]) maior = esq;

	if(dir <= n && vetor[dir] > vetor[maior]) maior = dir;

	if(maior != i) {

		aux = vetor[i];
		vetor[i] = vetor[maior];
		vetor[maior] = aux;

		sift(vetor,maior,n);
	}
}

void build(int* vetor, int n) {

	for(int i = n / 2; i >= 0; i--) {
		sift(vetor, i, n);
	}
}

void heap_sort(int* vetor, int n) {

	build(vetor, n);

	for(int i = n;i > 0; i--) {
		int aux = vetor[i];
		vetor[i] = vetor[0];
		vetor[0] = aux;
		sift(vetor,0 , i - 1);
	}
}

void print_vetor(int* vetor, int tamanho) {

	printf("Vetor: ");

	for (int i = 0; i < tamanho; i++) {

		printf("[%d] ",vetor[i]);
	}

	printf("\n");
}

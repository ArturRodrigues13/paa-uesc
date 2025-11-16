#include <stdio.h>
#include <stdlib.h>

void merge(int* vetor, int inicio, int meio, int final);

void merge_sort(int* vetor, int inicio, int final);

void print_vetor(int* vetor, int tamanho);

int main() {

	int	vetor[10] = {10,24,8,21,6,54,4,3,9999,7};

	print_vetor(vetor, 10);

	merge_sort(vetor, 0, 9);

	print_vetor(vetor,10);
}

void merge(int* vetor, int inicio, int meio, int final) {

	int n1 = meio - inicio + 1;
	int n2 = final - meio;

	int esquerda[n1];
	int direita[n2];

	for(int i = 0; i < n1; i++) {
		esquerda[i] = vetor[inicio + i];
	}

	for(int j = 0; j < n2; j++) {

		direita[j] = vetor[meio + j + 1];
	}

	int i = 0, j = 0, k = inicio;

	while(i < n1 && j < n2) {
        if(esquerda[i] <= direita[j]) {
            vetor[k] = esquerda[i];
			k++;
			i++;
        } else {
            vetor[k] = direita[j];
			k++;
			j++;
        }
    }

    while(i < n1) {
        vetor[k] = esquerda[i];
		k++;
		i++;
    }

    while(j < n2) {
        vetor[k] = direita[j];
		k++;
		j++;
    }
}

void merge_sort(int* vetor, int inicio, int final) {

	if(inicio < final) {

		int meio =  (inicio + final) / 2;

		merge_sort(vetor, inicio, meio);

		merge_sort(vetor, meio + 1, final);

		merge(vetor, inicio, meio, final);
	}
}

void print_vetor(int* vetor, int tamanho) {

	printf("Vetor: ");

	for (int i = 0; i < tamanho; i++) {

		printf("[%d] ",vetor[i]);
	}

	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>

void bubble_step(int* vet, int inicio, int final) {

	for(int i = inicio; i < final; i++) {

		if(vet[i] > vet[i + 1]) {

			int aux = vet[i];
			vet[i] = vet[i + 1];
			vet[i + 1] = aux;
		}
	}
}

void rock_step(int* vet, int inicio, int final) {

	for(int i = final; i > inicio; i--) {

		if(vet[i] < vet[i - 1]) {

			int aux = vet[i];
			vet[i] = vet[i - 1];
			vet[i - 1] = aux;
		}
	}
}

void shake_sort(int* vet, int tamanho) {

	int inicio = 0;
	int final = tamanho - 1;

	while(inicio != final) { // (N - 1) + (N - 2) + (N - 3) + (N - 4) + (N - 5) + (N - 6) + ... + 1

		for(int i = inicio; i < final; i++) { // (N - 1) + (N - 3) + (N - 5) + (N - 7) + ... + 1
			if(vet[i] > vet[i + 1]) {

				int aux = vet[i];
				vet[i] = vet[i + 1];
				vet[i + 1] = aux;
			}
		}

		final --;

		if(inicio == final) {

			break;
		}

		for(int i = final; i > inicio; i--) { // (N - 2) + (N - 4) + (N - 6) + (N - 8) + ... + 2
			if(vet[i] < vet[i - 1]) {

				int aux = vet[i];
				vet[i] = vet[i - 1];
				vet[i - 1] = aux;
			}
		}
		inicio ++;
	}
}

int main() {

	int tamanho;

	printf("Tamanho do Vetor: ");
	scanf("%d",&tamanho);

	int *vet = (int*)malloc(sizeof(int)*tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		printf("\nVetor[%d]: ",i);
		scanf("%d",&vet[i]);
	}

	shake_sort(vet,tamanho);

	printf("Vetor Ordenado:\n");
	for (int i = 0; i < tamanho;i++)
	{
		printf("%d ",vet[i]);
	}

	return 0;
}

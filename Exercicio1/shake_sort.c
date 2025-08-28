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

	while(inicio != final) {

		for(int i = inicio; i < final; i++) {
			if(vet[i] > vet[i + 1]) {

				int aux = vet[i];
				vet[i] = vet[i + 1];
				vet[i + 1] = aux;
			}
		}
		final --;

		if(inicio == final) break;

		for(int i = final; i > inicio; i--) {

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

	scanf("%d",&tamanho);

	int *vet = (int*)malloc(sizeof(int)*tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		scanf("%d",&vet[i]);
	}

	shake_sort(vet,tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		printf("%d ",vet[i]);
	}

	return 0;
}

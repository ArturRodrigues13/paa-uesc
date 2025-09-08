#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* vet, int tamanho) {

	for(int i = 0; i < tamanho; i++) {

		int chave = vet[i];
		int j = i - 1;
		while (j >= 0 && vet[j] > chave)
		{
			vet[j + 1] = vet[j];
			j--;
		}
		vet[j + 1] = chave;
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

	insertion_sort(vet,tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		printf("%d ",vet[i]);
	}

	return 0;
}

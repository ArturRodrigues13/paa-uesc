#include <stdio.h>
#include <stdlib.h>

void swap() {


}

void bubble_step(int* artur, int inicio, int final) {

	for(int i = inicio; i < final; i++) {

		if(artur[i] > artur[i + 1]) {

			int aux = artur[i];
			artur[i] = artur[i + 1];
			artur[i + 1] = aux;
		}
	}
}

void rock_step(int* artur, int inicio, int final) {

	for(int i = final; i > inicio; i--) {

		if(artur[i] < artur[i - 1]) {

			int aux = artur[i];
			artur[i] = artur[i - 1];
			artur[i - 1] = aux;
		}
	}
}

void shake_sort(int* artur, int tamanho) {

	int inicio = 0;
	int final = tamanho - 1;

	while(inicio != final) {

		bubble_step(artur, inicio, final);
		final --;
		if(inicio == final) break;
		rock_step(artur, inicio, final);
		inicio ++;
	}
}

int main() {

	int tamanho;

	scanf("%d",&tamanho);

	int *artur = (int*)malloc(sizeof(int)*tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		scanf("%d",&artur[i]);
	}

	shake_sort(artur,tamanho);

	for (int i = 0; i < tamanho;i++)
	{
		printf("%d ",artur[i]);
	}

	return 0;
}

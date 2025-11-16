#include <stdio.h>

void print_vetor(int* vetor, int tamanho);

void bubble_sort(int* vetor, int tamanho);

void merge(int* vetor, int inicio, int marca1, int marca2, int marca3, int final);

void merge_sort(int* vetor, int inicio, int final);

void sift(int* vetor, int i, int n);

void build(int *vetor, int n);

void heap_sort(int* vetor, int n);

void sift(int* vetor, int i, int n) {

	int filho1 = 4 * i + 1;
	int filho2 = 4 * i + 2;
	int filho3 = 4 * i + 3;
	int filho4 = 4 * i + 4;
	int aux;
	int maior = i;

	if(filho1 < n && vetor[filho1] > vetor[maior]) maior = filho1;

	if(filho2 < n && vetor[filho2] > vetor[maior]) maior = filho2;

	if(filho3 < n && vetor[filho3] > vetor[maior]) maior = filho3;

	if(filho4 < n && vetor[filho4] > vetor[maior]) maior = filho4;

	if(maior != i) {

		aux = vetor[i];
		vetor[i] = vetor[maior];
		vetor[maior] = aux;

		sift(vetor,maior,n);
	}
}

void build(int* vetor, int n) {

	int aux = n + 2;

	for(int i = aux / 4 - 1; i >= 0; i--) {
		sift(vetor, i, n);
	}
}

void heap_sort(int* vetor, int n) {

	build(vetor, n);

	for(int i = n - 1;i > 0; i--) {
		int aux = vetor[i];
		vetor[i] = vetor[0];
		vetor[0] = aux;
		sift(vetor,0,i);
	}
}

void merge(int* vetor, int inicio, int marca1, int marca2, int marca3, int final) {

	int tamanho = final - inicio + 1;

	int vetAux[tamanho];

	int i = inicio, j = marca1 + 1, k = marca2 + 1, l = marca3 + 1;
    int indice = 0;

	while(i <= marca1 || j <= marca2 || k <= marca3 || l <= final) {

		int menor = 1e9;
		int origem = 0;

		if (i <= marca1 && vetor[i] < menor) { menor = vetor[i]; origem = 1; }
        if (j <= marca2 && vetor[j] < menor) { menor = vetor[j]; origem = 2; }
        if (k <= marca3 && vetor[k] < menor) { menor = vetor[k]; origem = 3; }
        if (l <= final && vetor[l] < menor) { menor = vetor[l]; origem = 4; }

		vetAux[indice++] = menor;

		if (origem == 1) i++;
        else if (origem == 2) j++;
        else if (origem == 3) k++;
        else if (origem == 4) l++;
    }

	for(int x = 0; x < tamanho; x++) {

		vetor[inicio + x] = vetAux[x];
	}
}

void merge_sort(int* vetor, int inicio, int final) {

	if(inicio < final) {

		int marca1 = inicio + (final - inicio) / 4;
		int marca2 = inicio + (final - inicio) / 2;
		int marca3 = inicio + 3 * (final - inicio) / 4;

		merge_sort(vetor, inicio, marca1);

		merge_sort(vetor, marca1 + 1, marca2);

		merge_sort(vetor, marca2 + 1, marca3);

		merge_sort(vetor, marca3 + 1, final);

		merge(vetor, inicio, marca1, marca2, marca3, final);
	}
}

void print_vetor(int* vetor, int tamanho) {

	printf("Vetor: ");

	for (int i = 0; i < tamanho; i++) {

		printf("[%d] ",vetor[i]);
	}

	printf("\n");
}

void bubble_sort(int* vetor, int tamanho) {

    int aux;
    int trocou;

    for (int i = 0; i < tamanho - 1; i++) {
        trocou = 0;

        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {

                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                trocou = 1;
            }
        }

        if (trocou == 0) {
            break;
        }
    }
}

int main() {

	int tamanho;
	int k1 = 500;
	int k2 = 20;

	printf("Escolha um tamanho N para o vetor e eu vou preencher com valores de N até 1, em formato decrescente.\n\n");

	printf("Digite o Tamanho do Vetor: ");
	scanf("%d",&tamanho);

	int vetor[tamanho];

	for(int i = tamanho; i > 0; i--) {

		vetor[i - 1] = tamanho - i + 1;
	}

	print_vetor(vetor,tamanho);

	if(tamanho <= k2) {
		printf("Tamanho do vetor <= 30, BubbleSort utilizado\n\n");
		bubble_sort(vetor, tamanho);

	} else if (tamanho > k2 && tamanho <= k1) {
		printf("Tamanho do vetor <= 500, HeapSort utilizado\n\n");
		heap_sort(vetor, tamanho);

	} else if (tamanho > k1) {
		printf("Tamanho do vetor > 500, MergeSort utilizado\n\n");
		merge_sort(vetor, 0, tamanho - 1);

	}

	print_vetor(vetor,tamanho);

	return 0;
}

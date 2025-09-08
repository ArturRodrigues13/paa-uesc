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

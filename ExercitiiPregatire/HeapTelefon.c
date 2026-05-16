#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Telefon Telefon;
typedef struct Heap Heap;

struct Telefon {
	int id;
	float pret;
	char* producator;
	int garantie;
};

struct Heap {
	Telefon* vector;
	int lungime;
	int noduri;
};


Telefon CitireTelefonFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	Telefon t;

	aux = strtok(buffer, sep);
	t.id = atoi(aux);
	t.pret = atoi(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	t.producator = malloc(strlen(aux) + 1);
	strcpy(t.producator, aux);

	t.garantie = atoi(strtok(NULL, sep));

	return t;
}

void AfisareTelefon(Telefon t) {
	printf("ID: %d\n", t.id);
	printf("PRET: %.2f\n", t.pret);
	printf("PRODUCATOR: %s\n", t.producator);
	printf("GARANTIE: %d\n\n", t.garantie);
}

Heap InitializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.noduri = 0;
	heap.vector = malloc(lungime * sizeof(Telefon));
	return heap;
}

void filtreazaHeap(Heap heap, int poz_nod) {
	int poz_st = 2 * poz_nod + 1;
	int poz_dr = 2 * poz_nod + 2;
	int poz_max = poz_nod;
	if (poz_st < heap.noduri && heap.vector[poz_max].pret < heap.vector[poz_st].pret) {
		poz_max = poz_st;
	}
	if (poz_dr < heap.noduri && heap.vector[poz_max].pret < heap.vector[poz_dr].pret) {
		poz_max = poz_dr;
	}

	if (poz_max != poz_nod) {
		Telefon temp = heap.vector[poz_nod];
		heap.vector[poz_nod] = heap.vector[poz_max];
		heap.vector[poz_max] = temp;
		if (poz_max <= (heap.noduri - 2) / 2) {
			filtreazaHeap(heap, poz_max);
		}
	}
}

Heap CitireHeapFisier(const char* fisier) {
	FILE* f = fopen(fisier, "r");
	Heap heap = InitializareHeap(10);

	while (!feof(f)){
		heap.vector[heap.noduri++] = CitireTelefonFisier(f);
	}

	fclose(f);

	for (int i = (heap.noduri - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}

	return heap;
}

void AfisareHeap(Heap heap) {
	for (int i = 0; i < heap.noduri; i++) {
		printf("Telefon: %d\n\n\n", i+1);
		AfisareTelefon(heap.vector[i]);
		printf("\n");
	}
}

Telefon ExtragereCuAscundere(Heap* heap) {
	if (heap->noduri > 0) {
		Telefon aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->noduri - 1];
		heap->vector[heap->noduri - 1] = aux;
		heap->noduri--;
		for (int i = (heap->noduri - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
}

int TotalTelefoaneProducator(Heap heap, const char* producator) {
	int nr_telefoane = 0;
	for (int i = 0; i < heap.noduri; i++) {
		if (strcmp(heap.vector[i].producator , producator) == 0) {
			nr_telefoane++;
		}
	}
	
	return nr_telefoane;
}

Telefon DeepCopyHeapId(Heap heap, int id) {
	Telefon t;

	t.id = 0;
	t.pret = 0;
	t.producator = NULL;
	t.garantie = 0;

	for (int i = 0; i < heap.noduri; i++) {
		if (heap.vector[i].id == id) {
			t.id = heap.vector[i].id;
			t.pret = heap.vector[i].pret;
			t.producator = malloc(strlen(heap.vector[i].producator) + 1);
			strcpy(t.producator, heap.vector[i].producator);
			t.garantie = heap.vector[i].garantie;
		}
	}

	return t;
}

void AfisareHeapAscuns(Heap heap) {
	for (int i = heap.noduri; i < heap.lungime; i++) {
		AfisareTelefon(heap.vector[i]);
		printf("\n");
	}
}

void Dezalocare(Heap* heap) {
	for (int i = 0; i < heap->noduri; i++) {
		free(heap->vector[i].producator);
	}
	free(heap->vector);

	heap->vector = NULL;
	heap->noduri = 0;
	heap->lungime = 0;
}

int main() {
	Heap heap = CitireHeapFisier("telefoane.txt");
	AfisareHeap(heap);
	printf("\n\n\n");

	printf("Nr tel total de producator:\n");
	printf("Producatorul %s are in total %d telefoane\n\n", "Apple", TotalTelefoaneProducator(heap, "Apple"));

	printf("Deep copy dupa id:\n\n");
	AfisareTelefon(DeepCopyHeapId(heap, 6));
	printf("\n");
	AfisareTelefon(ExtragereCuAscundere(&heap));
	AfisareTelefon(ExtragereCuAscundere(&heap));

	printf("Afisare crescator:\n");
	AfisareHeapAscuns(heap);
	
	Dezalocare(&heap);

	return 0;
}


	





#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Telefon {
	int id;
	float pret;
	char* producator;
	int taste;
};

typedef struct Telefon Telefon;
typedef struct Nod Nod;

struct Nod {
	Telefon info;
	Nod* stanga;
	Nod* dreapta;
	int inaltime;
};

Telefon CitireTelefonFisier(FILE* f) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	char* aux;
	Telefon t;

	aux = strtok(buffer, sep);
	t.id = atoi(aux);
	t.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	t.producator = malloc(strlen(aux) + 1);
	strcpy(t.producator, aux);
	t.taste = atoi(strtok(NULL, sep));


	return t;
}

void AfisareTelefon(Telefon t) {
	printf("ID:%d\n", t.id);
	printf("PRET: %.2f\n", t.pret);
	printf("PROD: %s\n", t.producator);
	printf("NR TASTE: %d\n\n", t.taste);
}

#define max(a,b) ((a) > (b) ? (a) : (b))

int inaltime(Nod* radacina) {
	if (radacina==NULL) {
		return 0;
	}
	return radacina->inaltime;
}

int Echilibru(Nod* radacina) {
	if (radacina==0) {
		return 0;
	}
	return inaltime(radacina->stanga) - inaltime(radacina->dreapta);
}

Nod* RotireDreapta(Nod* radacina) {
	Nod* nou = radacina->stanga;
	Nod* aux = nou->dreapta;

	nou->dreapta = radacina;
	radacina->stanga = aux;

	radacina->inaltime = 1 + max(inaltime(radacina->stanga), inaltime(radacina->dreapta));
	nou->inaltime = 1 + max(inaltime(nou->stanga), inaltime(nou->dreapta));

	return nou;
}

Nod* RotireStanga(Nod* radacina) {
	Nod* nou = radacina->dreapta;
	Nod* aux = nou->stanga;

	nou->stanga = radacina;
	radacina->dreapta = aux;

	radacina->inaltime = 1 + max(inaltime(radacina->stanga), inaltime(radacina->dreapta));
	nou->inaltime = 1 + max(inaltime(nou->stanga), inaltime(nou->dreapta));

	return nou;
}

Nod* InserareAvl(Nod* radacina, Telefon telefonNou) {
	if (radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->info = telefonNou;
		nou->stanga = NULL;
		nou->dreapta = NULL;
		nou->inaltime = 0;
		return nou;
	}

	if (telefonNou.id < radacina->info.id) {
		radacina->stanga = InserareAvl(radacina->stanga, telefonNou);
	}
	else {
		if (telefonNou.id > radacina->info.id) {
			radacina->dreapta = InserareAvl(radacina->dreapta, telefonNou);
		}
		else {
			return radacina;
		}
	}

	radacina->inaltime = 1 + max(inaltime(radacina->stanga), inaltime(radacina->dreapta));

	int fe = Echilibru(radacina);

	if (fe > 1 && telefonNou.id < radacina->stanga->info.id) {
		return RotireDreapta(radacina);
	}

	if (fe<-1 && telefonNou.id > radacina->dreapta->info.id) {
		return RotireStanga(radacina);
	}

	if (fe > 1 && telefonNou.id > radacina->stanga->info.id) {
		radacina->stanga = RotireDreapta(radacina);
		RotireStanga(radacina);
	}

	if (fe < -1 && telefonNou.id < radacina->dreapta->info.id) {
		radacina->dreapta = RotireStanga(radacina);
		RotireDreapta(radacina);
	}

	return radacina;
}

Nod* CitireArboreFisier(const char* nume_fisier) {
	FILE* f = fopen(nume_fisier, "r");
	Nod* radacina = NULL;

	while (!feof(f)) {
		radacina = InserareAvl(radacina, CitireTelefonFisier(f));
	}

	fclose(f);

	return radacina;
}

void AfisareInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		AfisareInOrdine(radacina->stanga);
		AfisareTelefon(radacina->info);
		AfisareInOrdine(radacina->dreapta);
	}
}

int main() {
	Nod* radacina = NULL;

	radacina = CitireArboreFisier("telefoane.txt");
	printf("Radacina: %d\n", radacina->info.id);
	printf("tel in arbore\n\n");
	AfisareInOrdine(radacina);
	return 0;
}





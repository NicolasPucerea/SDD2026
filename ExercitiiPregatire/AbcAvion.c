#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Avion {
	char* model;
	int nr_locuri;
	int nr_locuri_ocupate;
	float preturi;
};

typedef struct Avion Avion;

typedef struct ArboreAbc Nod;

struct ArboreAbc {
	Avion info;
	Nod* stanga;
	Nod* dreapta;
};

Avion CitireAvionFisier(FILE* f) {
	char buffer[100];
	fgets(buffer, 100, f);
	char sep[3] = ",\n";
	char* aux;
	Avion a;

	aux = strtok(buffer, sep);
	a.model = malloc(strlen(aux) + 1);
	strcpy(a.model, aux);

	a.nr_locuri = atoi(strtok(NULL, sep));
	a.nr_locuri_ocupate = atoi(strtok(NULL, sep));
	a.preturi = atof(strtok(NULL, sep));

	return a;
}

void AfisareAvion(Avion a) {
	printf("Model:%s\n", a.model);
	printf("Nr locuri:%d\n", a.nr_locuri);
	printf("Nr locuri ocupate:%d\n", a.nr_locuri_ocupate);
	printf("Pret:%.2f\n\n", a.preturi);
}

void InserareArbore(Nod** radacina, Avion avion) {
	if (*radacina) {
		if ((*radacina)->info.preturi < avion.preturi) {
			InserareArbore(&(*radacina)->dreapta, avion);
		}
		else {
			InserareArbore(&(*radacina)->stanga, avion);
		}
	}
	else{
		Nod* nou = malloc(sizeof(Nod));
		nou->info = avion;
		nou->stanga = 0;
		nou->dreapta = 0;
		*radacina = nou;
	}
}

Nod* CitireArboreFisier(const char* nume_fisier) {
	FILE* f = fopen(nume_fisier, "r");
	Nod* radacina = NULL;

	while (!feof(f)) {
		InserareArbore(&radacina, CitireAvionFisier(f));
	}
	fclose(f);

	return radacina;
}

void AfisareArborePreOrdine(Nod* radacina) {
	if (radacina) {
		AfisareAvion(radacina->info);
		AfisareArborePreOrdine(radacina->stanga);
		AfisareArborePreOrdine(radacina->dreapta);
	}
}

void AfisareArboreInOrdine(Nod* radacina) {
	if (radacina) {
		AfisareArboreInOrdine(radacina->stanga);
		AfisareAvion(radacina->info);
		AfisareArboreInOrdine(radacina->dreapta);
	}
}

void Dezalocare(Nod** radacina) {
	if (radacina) {
		Dezalocare(&(*radacina)->stanga);
		Dezalocare(&(*radacina)->dreapta);
	}
	if ((*radacina)->info.model) {
		free((*radacina)->info.model);
	}
}

Avion GetAvionOcupate(Nod* radacina, int ocupate) {
	if (radacina) {
		if (radacina->info.nr_locuri_ocupate = ocupate) {
			Avion a = radacina->info;
			a.model = malloc(strlen(radacina->info.model) + 1);
			strcpy(a.model, radacina->info.model);
			return a;
		}
		if (radacina->info.nr_locuri_ocupate < ocupate) {
			return GetAvionOcupate(radacina->dreapta, ocupate);
		}
		if (radacina->info.nr_locuri_ocupate > ocupate) {
			return GetAvionOcupate(radacina->stanga, ocupate);
		}

	}
}

int DeterminaNrNoduri(Nod* radacina) {
	if (radacina) {
		return 1 + DeterminaNrNoduri(radacina->stanga) + DeterminaNrNoduri(radacina->dreapta);
	}
	return 0;
}

int GetInaltimeArbore(Nod* radacina) {
	if (radacina) {
		int st = GetInaltimeArbore(radacina->stanga);
		int dr = GetInaltimeArbore(radacina->dreapta);
		return 1 + (st > dr ? st : dr);
	}
}

float CalculeazaPretTotal(Nod* radacina) {
	if (radacina) {
		return radacina->info.preturi + CalculeazaPretTotal(radacina->stanga) + CalculeazaPretTotal(radacina->dreapta);
	}
	return 0;
}
int main() {
	Nod* radacina = CitireArboreFisier("avioane.txt");
	AfisareArboreInOrdine(radacina);
	AfisareAvion(GetAvionOcupate(radacina, 76));
	printf("Sunt %d noduri\n\n", DeterminaNrNoduri(radacina));
	printf("Inaltime: %d\n\n", GetInaltimeArbore(radacina));
	printf("Pret total:%.2f", CalculeazaPretTotal(radacina));

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("Masina cu id-ul %d, numarul de usi %d,are pretul %.2f, modelul %s, condusa de %s, seria %d\n",
		masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for( int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	nrMasini = 0;
	Masina* temp = (Masina*)malloc(sizeof(Masina) * (*nrMasini + 1));
	for(int i = 0; i < *nrMasini; i++) {
		temp[i] = (*masini)[i];
	}
	temp[*nrMasini] = masinaNoua;
	
	free(*masini);
	(*masini) = temp;
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	Masina m;
	char buffer[50];
	fgets(buffer, 49, file);
	char var[3] = ",\n";

	m.id = atoi(strtok(buffer, var));
	m.nrUsi = atoi(strtok(NULL, var));
	m.pret = atof(strtok(NULL, var));
	char* aux = strtok(NULL, var);
	m.model = (char*)malloc(sizeof(aux) * strlen(aux) + 1);
	strcpy(m.model, aux);
	char* aux1 = strtok(NULL, var);
	m.numeSofer = (char*)malloc(sizeof(aux1) * strlen(aux1) + 1);
	strcpy(m.numeSofer, aux1);
	m.serie = (strtok(NULL, var))[0];
	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {

	FILE* file;
	file = fopen(numeFisier, "r");
	Masina* masini = NULL;
	nrMasiniCitite = 0;
	while (!feof(file)){
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;


}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	int nrMasini = 0;
	Masina* masini = NULL;
	citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);

	return 0;
}

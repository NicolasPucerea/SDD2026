#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMagazin
{
    int id;
    char* denumire;
    char* localitate;
    float suprafata;
    int numar_angajati;
};

typedef struct StructuraMagazin Magazin;

typedef struct Nod Nod;

struct Nod
{
    Magazin info;
    Nod* next;
};

Magazin creareMagazin(int id, const char* denumire, const char* localitate, float suprafata, int numar_angajati)
{
    Magazin m;
    m.id = id;
    m.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
    strcpy(m.denumire, denumire);
    m.localitate = (char*)malloc((strlen(localitate) + 1) * sizeof(char));
    strcpy(m.localitate, localitate);
    m.suprafata = suprafata;
    m.numar_angajati = numar_angajati;
    return m;
}

Nod* creareNod(Magazin m)
{
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info.id = m.id;
    nou->info.denumire = (char*)malloc((strlen(m.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, m.denumire);
    nou->info.localitate = (char*)malloc((strlen(m.localitate) + 1) * sizeof(char));
    strcpy(nou->info.localitate, m.localitate);
    nou->info.suprafata = m.suprafata;
    nou->info.numar_angajati = m.numar_angajati;
    nou->next = NULL;
    return nou;
}

Magazin citireMagazin(Magazin m)
{

    printf("Introduceti id-ul magazinului: ");
    scanf("%d", &m.id);
    char buffer[100];
    printf("Introduceti denumirea magazinului: ");
    scanf("%s", buffer);
    m.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(m.denumire, buffer);
    printf("Introduceti localitatea magazinului: ");
    scanf("%s", buffer);
    m.localitate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(m.localitate, buffer);
    printf("Introduceti suprafata magazinului: ");
    scanf("%f", &m.suprafata);
    printf("Introduceti numarul de angajati ai magazinului: ");
    scanf("%d", &m.numar_angajati);
    return m;
}

void inserareFinal(Nod** cap, Magazin m) {
    Nod* nou = creareNod(m);

    if (*cap == NULL) {
        *cap = nou;
    } else {
        Nod* temp = *cap;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

void AfisareMagazin(Magazin m)
{
    printf("ID: %d\n", m.id);
    printf("Denumire: %s\n", m.denumire);
    printf("Localitate: %s\n", m.localitate);
    printf("Suprafata: %.2f\n", m.suprafata);
    printf("Numar angajati: %d\n", m.numar_angajati);
}

void AfisareLista(Nod* cap)
{
    Nod* temp = cap;

    while (temp != NULL)
    {
        AfisareMagazin(temp->info);
        printf("\n");
        temp = temp->next;
    }

}

void DezalocareLista(Nod* cap)
{
    Nod* temp= cap;
    while(temp!=NULL)
    {
        Nod* temp2 = temp;
        temp = temp->next;
        free(temp2->info.denumire);
        free(temp2->info.localitate);
        free(temp2);
    }
}

void DezalocareMagazin(Magazin m)
{
    free(m.denumire);
    free(m.localitate);
    m.denumire = NULL;
    m.localitate = NULL;
}

int main()
{
    Nod* cap = NULL;
    Magazin m1= creareMagazin(1, "Carrefour", "Bucuresti", 2000.5, 150);
    Magazin m2 = creareMagazin(2, "Auchan", "Cluj", 3000.75, 200);
    inserareFinal(&cap, m1);
    inserareFinal(&cap, m2);

    AfisareLista(cap);

    DezalocareMagazin(m1);
    DezalocareMagazin(m2);
    DezalocareLista(cap);
    return 0;
}




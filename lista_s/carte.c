#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


typedef struct Carte Carte;
struct Carte {
	char* denumire;
	int nrPagini;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Carte info;
	Nod* next;
};

Carte initializareCarte(const char* denumire, int nrPagini, float pret) {
	Carte c;
	c.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(c.denumire, denumire);
	c.nrPagini = nrPagini;
	c.pret = pret;
	return c; // nu uita sa returnezi obiectul
}

Nod* inserareInceput(Carte carte, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = carte;
	nod->next = lista;
	return nod;
}

void afisareCarte(Carte carte) {
	if (carte.denumire != NULL) {
		printf("\nTitlul cartii este %s", carte.denumire);
	}
	printf("\nNumarul de pagini este %d", carte.nrPagini);
	printf("\nPretul cartii este %5.2f", carte.pret);
	printf("\n");
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {
		afisareCarte(lista->info);
		lista = lista->next;
	}
}

Nod* citireFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (file == NULL) {
		printf("\nEroare la deschiderea fisierului! ");
	}
	char buffer[100];
	char delimitare[] = ",\n";
	Nod* lista = NULL;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Carte c;
		c.denumire = (char*)malloc(strlen(element) + 1);
		strcpy(c.denumire, element);
		element = strtok(NULL, delimitare);
		c.nrPagini = atoi(element);
		element = strtok(NULL, delimitare);
		c.pret = atof(element);
		lista = inserareInceput(c, lista);
	}
	fclose(file);
	return lista;
}

int numarTotalPagini(Nod* lista) {
	int nr = 0;
	while (lista != NULL) {
		nr = nr + lista->info.nrPagini;
		lista = lista->next;
	}
	return nr;
}

int nrCartiDupaPret(Nod* lista, float pret) {
	int numar = 0;
	while (lista != NULL) {
		if (lista->info.pret == pret) {
			numar = numar + 1;
		}
		lista = lista->next;
	}
	return numar;
}

char* nrCartiDupaTitlu(Nod* lista, const char* denumire) {
	int nr = 0;
	while (lista != NULL) {
		if (strcmp(lista->info.denumire, denumire)==0) { // cand compar doua siruri de caractere, este recomandat sa folosesc strcmp
			nr = nr + 1;
		}
		lista = lista->next;
	}
	return nr;
}

char* carteCeaMaiScumpa(Nod* lista) {
	float pretMaxim = 0;
	char* aux = NULL;
	while (lista != NULL) {
		if (lista->info.pret > pretMaxim) {
			pretMaxim = lista->info.pret;
			aux = lista->info.denumire;
		}
		lista = lista->next;
	}
	while (aux != NULL) {
		char* denumireCarte = (char*)malloc(strlen(aux) + 1);
		strcpy(denumireCarte, aux);
		return denumireCarte;
	}
}

void stergereLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->info.denumire);
		Nod* aux = (*lista)->next;
		free(*lista);
		*lista = aux;
	}
	*lista = NULL;
}

int main() {
	Nod* lista = NULL;
	Carte c1 = initializareCarte("Bambi", 75, 25);
	Carte c2 = initializareCarte("Alladin", 93, 20);
	Carte c3 = initializareCarte("Cenusareasa", 126, 36);
	afisareCarte(c1);
	printf("\n\n");
	printf("\n***************************************\n");
	lista = inserareInceput(c1, lista);
	lista = inserareInceput(c2, lista);
	lista = inserareInceput(c3, lista); // la inserare nu se pune &
	afisareLista(lista);
	printf("\n\n");
	printf("\n********************************************\n");
	Nod* lista2 = NULL;
	lista2 = citireFisier("carte.txt");
	afisareLista(lista2);
	printf("\n\n");
	int numarPagini = numarTotalPagini(lista);
	printf("\nNumarul total de pagini este %d.\n", numarPagini);
	printf("\n");
	int numarCarti = nrCartiDupaPret(lista, 20);
	printf("\nNumarul de carti care au pretul cautat este %d. \n", numarCarti);
	printf("\n");
	int numarTitluri = nrCartiDupaTitlu(lista2, "Frozen");
	printf("\nNumarul de carti cu titlul cautat este %d. \n", numarTitluri);
	printf("\n");
	char* carteScumpa = carteCeaMaiScumpa(lista);
	printf("\nCartea cea mai scumpa este %s. \n", carteScumpa);
	printf("\n");
	printf("\n----------- // DUPA STERGERE // -----------\n");
	stergereLista(&lista);
	stergereLista(&lista2);
	afisareLista(lista);
	afisareLista(lista2);
}
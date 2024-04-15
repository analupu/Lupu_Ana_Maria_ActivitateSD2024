#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Floare Floare;
struct Floare {
	char* specie;
	int nrBulbi;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Floare info;
	Nod* prev;
	Nod* next;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};

Floare initializareFloare(const char* specie, int nrBulbi, float pret) {
	Floare f;
	f.specie = (char*)malloc(sizeof(specie) + 1);
	strcpy(f.specie, specie);
	f.nrBulbi = nrBulbi;
	f.pret = pret;
	return f;
}

void afisareFloare(Floare floare) {
	if (floare.specie != NULL) {
		printf("\nFloarea se numeste %s. ", floare.specie);
	}
	printf("\nNumarul de bulbi este %d. ", floare.nrBulbi);
	printf("\nPretul unui bulb este %5.2f. ", floare.pret);
	printf("\n");
}

void afisareLista(ListaDubla lista) {
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		afisareFloare(nod->info);
	}
	printf("\n");
}

Nod* inserareInceput(ListaDubla* lista, Floare floare) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = floare;
	nod->next = lista->prim;
	nod->prev = NULL;
	if (lista->prim != NULL) {
		lista->prim->prev = nod;
	}
	else {
		lista->ultim = nod;
	}
	lista->prim = nod;
	return nod;
}

ListaDubla* citireFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	if (file == NULL) {
		printf("\nEroare la deschiderea fisierului! ");
	}
	ListaDubla* lista = (ListaDubla*)malloc(sizeof(ListaDubla));
	lista->prim = NULL;
	lista->ultim = NULL;
	char buffer[100];
	char delimitare[] = ",\n";

	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Floare f;
		f.specie = (char*)malloc(strlen(element) + 1);
		strcpy(f.specie, element);
		element = strtok(NULL, delimitare);
		f.nrBulbi = atoi(element);
		element = strtok(NULL, delimitare);
		f.pret = atof(element);
		inserareInceput(lista, f);
	}
	fclose(file);
	return lista;
}

int numarBulbiTotal(ListaDubla lista) {
	int numar = 0;
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		if (nod->info.nrBulbi > 0) {
			numar = numar + nod->info.nrBulbi;
		}
	} // nu se pune nod = nod->next, deoarece pasul se face in for
	return numar;
}

float costTotal(ListaDubla lista) {
	float costTotal = 0;
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		if (nod->info.nrBulbi > 0 && nod->info.pret > 0) {
			costTotal = costTotal + nod->info.nrBulbi * nod->info.pret;
		}
	}
	return costTotal;
}

char* floareCautata(ListaDubla lista, const char* specie) {
	char* aux = NULL;
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		if (strcmp(nod->info.specie, specie) == 0) {
			aux = nod->info.specie;
		}
	}
	while (aux != NULL) {
		char* specieCautata = (char*)malloc(sizeof(aux) + 1);
		strcpy(specieCautata, aux);
		return specieCautata;
	}
}

float pretMaxim(ListaDubla lista) {
	float maxim = 0;
	for (Nod* nod = lista.prim; nod != NULL; nod = nod->next) {
		if (nod->info.pret > maxim) {
			maxim = nod->info.pret;
		}
	}
	return maxim;
}

void stergereLista(ListaDubla* lista) {
	if (lista != NULL) {
		Nod* aux = lista->prim;
		while (aux != NULL) {
			free(aux->info.specie);
			Nod* temp = aux->next;
			free(aux);
			aux = temp;
		}
		lista->prim = NULL;
		lista->ultim = NULL;
	}
}

int main() {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	Floare f1 = initializareFloare("Lalea", 100, 15);
	Floare f2 = initializareFloare("Zambila", 150, 10);
	Floare f3 = initializareFloare("Narcisa", 200, 15);
	inserareInceput(&lista, f1);
	inserareInceput(&lista, f2);
	inserareInceput(&lista, f3);
	afisareLista(lista);
	printf("\n\n");
	printf("\n*************************************");
	ListaDubla* lista2 = citireFisier("floare.txt");
	afisareLista(*lista2);
	printf("\n");
	int numarBulbi = numarBulbiTotal(lista);
	printf("\nNumarul de bulbi total este %d. \n", numarBulbi);
	float cost = costTotal(lista);
	printf("\nCostul total este %5.2f RON. \n", cost);
	char* specie = floareCautata(lista, "Narcisa");
	float pret = pretMaxim(lista);
	printf("\nFloarea cea mai scumpa are pretul %5.2f. \n", pret);
	printf("\nFloarea cautata este %s. \n", specie);
	printf("\n---- // DUPA STERGERE // ----\n");
	stergereLista(&lista);
	afisareLista(lista);
}
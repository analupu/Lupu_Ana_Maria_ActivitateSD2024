#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Struguri Struguri;
struct Struguri {
	char* taraOrigine;
	float greutate;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Struguri info;
	Nod* next;
};

Struguri initializareStruguri(const char* taraOrigine, float greutate, float pret) {
	Struguri s;
	s.taraOrigine = (char*)malloc(strlen(taraOrigine) + 1);
	strcpy(s.taraOrigine, taraOrigine);
	s.greutate = greutate;
	s.pret = pret;
	return s;
}

void afisareStruguri(Struguri struguri) {
	if (struguri.taraOrigine != NULL) {
		printf("\nTara de origine a strugurilor este %s.", struguri.taraOrigine);
	}
	printf("\nGreutata importata este %5.2f kilograme.", struguri.greutate);
	printf("\nPretul per kilogram este %5.2f.", struguri.pret);
	printf("\n");
}

void afisareLista(Nod* lista) {
	while (lista != NULL) {
		afisareStruguri(lista->info);
		lista = lista->next;
	}
}

Nod* inserareInceput(Struguri struguri, Nod* lista) {
	Nod* nod = (Nod*)malloc(sizeof(Nod));
	nod->info = struguri;
	nod->next = lista;
	return nod;
}

char* greutateMaxima(Nod* lista) {
	float max = 0;
	char* aux = NULL;
	while (lista != NULL) {
		if (lista->info.greutate > max) {
			max = lista->info.greutate;
			aux = lista->info.taraOrigine;
		}
		lista = lista->next;
	}
	while (aux != NULL) {
		char* origineStruguri = (char*)malloc(strlen(aux) + 1);
		strcpy(origineStruguri, aux);
		return origineStruguri;
	}
}

float costTotal(Nod* lista) {
	float cost = 0;
	while (lista != NULL) {
		if (lista->info.greutate > 0 && lista->info.pret > 0) {
			cost = cost + lista->info.greutate * lista->info.pret;
		}
		lista = lista->next;
	}
	return cost;
}

void stergeLista(Nod** lista) {
	while ((*lista) != NULL) {
		free((*lista)->info.taraOrigine);
		Nod* aux = (*lista)->next;
		free(*lista);
		*lista = aux;
	}
	*lista = NULL;
}

int main() {
	Nod* lista = NULL;
	Struguri s1 = initializareStruguri("Turcia", 250, 30);
	Struguri s2 = initializareStruguri("India", 500, 15);
	lista = inserareInceput(s1, lista);
	lista = inserareInceput(s2, lista);
	afisareLista(lista);
	printf("\n");
	char* origine = greutateMaxima(lista);
	printf("\nCel mai mult se importa struguri din tara %s. \n", origine);
	printf("\n");
	float cost = costTotal(lista);
	printf("\nCostul total este %5.2f RON. \n", cost);
	printf("\n---- // DUPA STERGERE // ----");
	stergeLista(&lista);
	afisareLista(lista);
}
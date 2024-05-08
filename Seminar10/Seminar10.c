#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Rezervare Rezervare;
struct Rezervare {
	int id;
	char* numeClient;
	int nrPersoane;
};

typedef struct Nod Nod;
struct Nod {
	Rezervare info;
	Nod* stanga;
	Nod* dreapta;
};

Rezervare citireRezervare(FILE* f) {
	Rezervare r;
	char aux[30];
	fgets(aux, 30, f);
	fscanf(f, "%d", &(r.id));
	fscanf(f, "%s", &aux);
	r.numeClient = (char*)malloc(strlen(aux) + 1);
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &(r.nrPersoane));
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare rez) { // inserarea in arbore se face in nodul frunza
	if (arbore != NULL) {
		if (arbore->info.id < rez.id) {
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else {
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez; // shallow copy
		temp->dreapta = NULL; //nod frunza
		temp->stanga = NULL;

		arbore = temp;
	}
	return arbore;


}

void citireFisier(const char* numeFisier, Nod** radacina) {
	int nrRezervari = 0;
	FILE* f = fopen(numeFisier, "r");
	fscanf(f, "%d", &nrRezervari); // al treilea element este in ce citim
	for (int i = 0; i < nrRezervari; i++) {
		Rezervare rez;
		rez = citireRezervare(f);
		(*radacina) = inserareInArbore((*radacina), rez);
	}
}

void afisareRezervare(Rezervare r) {
	printf("\nRezervarea cu ID-ul %d a fost facuta de %s pentru %d persoane. ", r.id, r.numeClient, r.nrPersoane);
	printf("\n");
}

// RSD, SDR, SRD - 3 MODURI DE CITIRE PENTRU ARBORI => preordine, postordine, inordine
void afisareArborePreordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareRezervare(arbore->info);
		afisareArborePreordine(arbore->stanga);
		afisareArborePreordine(arbore->dreapta);
	}
}

void afisareInOrdine(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrdine(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareInOrdine(arbore->dreapta);
	}
}

void afisarePostOrdine(Nod* arbore) {
	if (arbore != NULL) {
		afisarePostOrdine(arbore->stanga);
		afisarePostOrdine(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}

Rezervare cautaRezervareDupaID(Nod* rad, int ID) {
	if (rad != NULL) {
		if (rad->info.id < ID) {
			return cautaRezervareDupaID(rad->dreapta, ID);
		}
		else {
			if (rad->info.id > ID) {
				return cautaRezervareDupaID(rad->stanga, ID);
			}
			else {
				return rad->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}

int calculNrTotalPersoane(Nod* rad) {
	if (rad != NULL) {
		int rPersoane = rad->info.nrPersoane; // din radacina
		int sPersoane = calculNrTotalPersoane(rad->stanga);
		int dPersoane = calculNrTotalPersoane(rad->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else {
		return 0; // aici este initializarea int suma = 0; sub nodurile frunza 
	}
}

int main() {
	Nod* radacina = NULL;
	citireFisier("rezervare.txt", &radacina);
	printf("\n--------------------------- // -------------------------");
	afisareArborePreordine(radacina);
	printf("\n--------------------------- // -------------------------");
	afisareInOrdine(radacina);
	printf("\n--------------------------- // -------------------------");
	afisarePostOrdine(radacina);
	printf("\n--------------------------- // -------------------------");

	printf("\n");
	afisareRezervare(cautaRezervareDupaID(radacina, 8));
	printf("\nNumar total persoane: %d ", calculNrTotalPersoane(radacina));
}
// numarul de muchii este egal cu numarul de noduri - 1 (n -1)
// arbore binar de cautare: info din rad trebuie sa fie mai mare decat nodul din stanga, dar mai mica decat nodul din dreapta
// cautarea se face prin metoda divide et impera 
// nod: info utila si fiii (stanga si dreapta) ->pointer, pt ca retinem adresa

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct Masina {
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i]; //shallow copy
	}
	aux[*nrMasini] = m;
	(*nrMasini)++; // ++ are prioritate mai mare decat dereferentierea => prioritizam *nrMasini
	if (masini != NULL) {
		free(masini); //stregem doar vectorul, pointerii raman
	}
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) { //nrMasini este deja un pointer care are adresa => nu trebuie sa ii mai dam adresa
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";

	//am creat un vector de masini
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL) { //cand ajunge la finalul fisierului si nu mai are ce citi, returneaza null
		char* element = strtok(buffer, delimitare); // este bine ca separatoarele sa fie stocate intr-o variabila
		struct Masina m; //am construit masina m
		m.id = atoi(element); //cast de la string to int
		element = strtok(NULL, delimitare);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		masini = adaugareInVector(masini, m, nrMasini);
	}
	fclose(file);
	return masini;
}



int main() {
	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		printf("Masina nr. %d \n", i);
		printf("ID: %d \n", masini[i].id);
		printf("Producator: %s \n", masini[i].producator);
		printf("Numar usi: %d \n", masini[i].nrUsi);
		printf("Pret: %d \n", masini[i].pret);
		printf("\n");
	}
}
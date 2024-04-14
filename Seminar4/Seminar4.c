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
	aux[(*nrMasini)] = m;
	(*nrMasini)++; // ++ are prioritate mai mare decat dereferentierea => prioritizam *nrMasini
	if (masini != NULL) {
		free(masini); //stregem doar vectorul, pointerii raman
	}
	return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) { //nrMasini este deja un pointer care are adresa => nu trebuie sa ii mai dam adresa
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		printf("Fisierul nu exista.\n");
		return NULL;
	}

	//am creat un vector de masini
	struct Masina* masini = NULL;
	(*nrMasini) = 0;
	char buffer[100];
	char delimitare[] = ",\n";

	while (fgets(buffer, 100, file) != NULL) { //cand ajunge la finalul fisierului si nu mai are ce citi, returneaza null
		char* element = strtok(buffer, delimitare); // este bine ca separatoarele sa fie stocate intr-o variabila
		struct Masina m; //am construit masina m
		m.id = atoi(element); //cast de la string to int
		element = strtok(NULL, delimitare);
		m.producator = (char*)malloc(strlen(element) + 1);
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


void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
	for (int i = 0; i < nrLinii;i++) {
		for (int j = 0; j < nrCol[i];j++) {
			printf("%d, %s, %d, %.2f \t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
		}
		printf("\n");
	}
}

void citireMatrice(const char* numeFisier, struct Masina** matrice, int nrLinii, int* nrCol) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";

	while (fgets(buffer, 100, file) != NULL) { //cand ajunge la finalul fisierului si nu mai are ce citi, returneaza null
		char* element = strtok(buffer, delimitare); // este bine ca separatoarele sa fie stocate intr-o variabila
		struct Masina m; //am construit masina m
		m.id = atoi(element); //cast de la string to int
		element = strtok(NULL, delimitare);
		m.producator = (char*)malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, delimitare);
		m.nrUsi = atoi(element);
		element = strtok(NULL, delimitare);
		m.pret = atof(element);
		matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrCol[m.nrUsi - 2]), m);
	}
	fclose(file);
}

//pretul mediu al masinilor cu numar de usi dat ca parametru

float pretMediu(struct Masina** matrice, int nrLinii, int* nrCol, int nrUsi) {
	if (nrUsi < 2 || nrUsi > 4)
		return 0;
	float pretTotal = 0;
	int index = nrUsi - 2;
	if (nrCol[index] == 0) {
		return 0;
	}
	for (int i = 0; i < nrCol[index];i++) {
		pretTotal += matrice[index][i].pret;
	}
	return pretTotal / nrCol[index];
}

struct Masina cautaMasinaDupaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrCol[i];j++) {
			if (matrice[i][j].id == id) {
				return matrice[i][j];
			}
		}
	}
	struct Masina m;
	m.id = -1;
	m.producator = NULL;
	m.nrUsi = -1;
	m.pret = -1;
	return m;
}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrCol) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < (*nrCol)[i];j++) {
			free((*matrice)[i][j].producator);
			(*matrice)[i][j].producator = NULL;
		}
		free((*matrice)[i]);
		(*matrice)[i] = NULL;
	}
	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;

}

int main() {
	struct Masina** matrice = NULL;
	int nrLinii = 3;
	int* nrColoane;
	nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
	for (int i = 0; i < nrLinii;i++) {
		nrColoane[i] = 0;
		matrice[i] = NULL;
	}

	citireMatrice("masini.txt", matrice, nrLinii, nrColoane);
	//afisareMatrice(matrice, nrLinii, nrColoane);
	float pret = pretMediu(matrice, nrLinii, nrColoane, 2);
	printf("Pretul mediu este: %5.2f ", pret);


	struct Masina masinaCautata = cautaMasinaDupaID(matrice, nrLinii, nrColoane, 2);
	printf("%d %s %d %.2f", masinaCautata.id, masinaCautata.producator, masinaCautata.nrUsi, masinaCautata.pret);


	dezalocareMatrice(&matrice, nrLinii, &nrColoane);


}


//matrice: o structura de date bidimensionala, omogena, cu memorie continua 
//numarul de coloane diferit => fiecare linie o reprezentam printr-un vector =>dimensiunea vectorului
//vector de vectori = matrice = tablou bidimensional 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Laptop Laptop;
struct Laptop {
	int cod;
	char* denumire;
	int stoc;
};

Laptop initializareLaptop(int cod, char* denumire, int stoc) {
	Laptop laptop;
	laptop.cod = cod;
	laptop.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(laptop.denumire, denumire);
	laptop.stoc = stoc;
	return laptop;
}

void afisareLaptop(Laptop laptop) {
	printf("\nCodul produsului este %d.", laptop.cod);
	if (laptop.denumire != NULL) {
		printf("\nDenumirea produsului este %s.", laptop.denumire);
	}
	printf("\nStocul disponibil din produsul cu codul %d este %d.", laptop.cod, laptop.stoc);
	printf("\n");
}

void afisareLaptopVector(Laptop* laptopuri, int nrLaptopuri) {
	for (int i = 0; i < nrLaptopuri; i++) {
		afisareLaptop(laptopuri[i]);
	}
}

Laptop* adaugaInVector(Laptop* laptopuri, Laptop l, int* nrLaptopuri) {
	Laptop* aux = (Laptop*)malloc(sizeof(Laptop) * ((*nrLaptopuri) + 1));
	for (int i = 0; i < *nrLaptopuri;i++) {
		aux[i] = laptopuri[i];
	}
	aux[*nrLaptopuri] = l;
	(*nrLaptopuri)++;
	if (laptopuri != NULL) {
		free(laptopuri);
	}
	return aux;
}

Laptop* citireFisier(const char* numeFisier, int* nrLaptopuri) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";

	Laptop* laptopuri = NULL;
	(*nrLaptopuri) = 0;

	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		Laptop l;
		l.cod = atoi(element);
		element = strtok(NULL, delimitare);
		l.denumire = malloc(strlen(element) + 1);
		strcpy(l.denumire, element);
		element = strtok(NULL, delimitare);
		l.stoc = atoi(element);
		laptopuri = adaugaInVector(laptopuri, l, nrLaptopuri);
	}
	fclose(file);
	return laptopuri;
}

void salvareLaptopInFisier(Laptop laptop, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului \n");
	}
	fprintf(file, "%d,%s,%d\n", laptop.cod, laptop.denumire, laptop.stoc);
	fclose(file);
}

void salvareVectorInFisier(Laptop* laptopuri, int nrLaptopuri, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	if (file == NULL) {
		printf("Eroare la deschiderea fisierului! \n");
	}
	for (int i = 0; i < nrLaptopuri;i++) {
		fprintf(file, "%d,%s,%d\n", laptopuri[i].cod, laptopuri[i].denumire, laptopuri[i].stoc);
	}
	fclose(file);
}

int main() {
	/*Laptop l1 = initializareLaptop(1, "Lenovo", 50);
	afisareLaptop(l1);
	int nrLaptopuri = 3;
	Laptop* laptopuri = (Laptop*)malloc(sizeof(Laptop) * nrLaptopuri);
	for (int i = 0; i < nrLaptopuri;i++) {
		laptopuri[i] = initializareLaptop(i + 1, "Lenovo", i * 20 + 10);
	}
	afisareLaptopVector(laptopuri, nrLaptopuri);
	printf("\n\n")*/;
	printf("-------------- // CITIRE FISIER // --------------");
	printf("\n");
	Laptop* laptopuri = NULL;
	int nrLaptopuri = 0;
	laptopuri = citireFisier("laptop.txt", &nrLaptopuri);
	for (int i = 0; i < nrLaptopuri;i++) {
		printf("Laptopul cu codul %d. \n", laptopuri[i].cod);
		printf("Denumirea este %s. \n", laptopuri[i].denumire);
		printf("Stocul disponibil este %d. \n", laptopuri[i].stoc);
		printf("\n");
	}
	
	Laptop laptopNou = initializareLaptop(101, "Lenovo Ideapad 520", 10);
	salvareLaptopInFisier(laptopNou, "laptop.txt");

	salvareVectorInFisier(laptopuri, nrLaptopuri, "laptop.txt");
}


#include <stdio.h>
#include <malloc.h>

typedef struct Laptop Laptop;
struct Laptop {
	int cod;
	char* denumire;
	int stoc;
};

Laptop initializareLaptop(int cod, const char* denumire, int stoc) {
	Laptop laptop;
	laptop.cod = cod;
	laptop.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(laptop.denumire, denumire);
	laptop.stoc = stoc;
	return laptop;
}

void afisareLaptop(Laptop laptop) {
	printf("\nLaptopul %s cu codul %d are stocul %d.", laptop.denumire, laptop.cod, laptop.stoc);
}

void afisareLaptopVector(Laptop* laptopuri, int nrLaptopuri) {
	for (int i = 0; i < nrLaptopuri;i++) {
		afisareLaptop(laptopuri[i]);
	}
}

Laptop* copiazaNElemente(Laptop* laptop, int nrLaptopuri, int nrCopiate) {
	if (nrCopiate <= nrLaptopuri && nrCopiate > 0) {
		Laptop* copiat = (Laptop*)malloc(sizeof(Laptop) * nrCopiate);
		for (int i = 0; i < nrCopiate;i++) {
			copiat[i] = initializareLaptop(laptop[i].cod, laptop[i].denumire, laptop[i].stoc);
		}
		return copiat;
	}
	else {
		return NULL;
	}
}

Laptop* copiazaLaptopuriPutine(Laptop* laptoprui, int nrLaptopuri, int stocPrag, int* nrLaptopuriPutine) {
	(*nrLaptopuriPutine) = 0;
	for (int i = 0; i < nrLaptopuri;i++) {
		if (laptoprui[i].stoc < stocPrag) {
			(*nrLaptopuriPutine)++;
		}
	}
	Laptop* laptopuriPutine = (Laptop*)malloc(sizeof(Laptop) * (*nrLaptopuriPutine));
	int k = 0;
	for (int i = 0; i < nrLaptopuri;i++) {
		if (laptoprui[i].stoc < stocPrag) {
			laptopuriPutine[k++] = initializareLaptop(laptoprui[i].cod, laptoprui[i].denumire, laptoprui[i].stoc);
		}
	}
	return laptopuriPutine;
}

Laptop cautaLaptopDupaCod(Laptop* laptopuri, int nrLaptopuri, int codCautat) {
	for (int i = 0; i < nrLaptopuri;i++) {
		if (laptopuri[i].cod = codCautat) {
			return initializareLaptop(laptopuri[i].cod, laptopuri[i].denumire, laptopuri[i].stoc);
		}
	}
	return initializareLaptop(0, "N/A", 0);
}

void dezalocareVectorLaptop(Laptop** laptopuri, int* nrLaptopuri) {
	for (int i = 0; i < (*nrLaptopuri); i++) {
		free((*laptopuri)[i].denumire);
	}
	free(*laptopuri);
	*nrLaptopuri = 0;
	*laptopuri = NULL;
}

int main() {
	int nrLaptopuri = 3;
	Laptop* laptoprui = (Laptop*)malloc(sizeof(Laptop) * nrLaptopuri);
	for (int i = 0; i < nrLaptopuri;i++) {
		laptoprui[i] = initializareLaptop(i + 1, "Lenovo", 20 * i + 10);
	}
	afisareLaptopVector(laptoprui, nrLaptopuri);
	printf("\n");
	printf("\n**************************************");
	int nrCopiate = 2;
	Laptop* laptopuriCopiate = copiazaNElemente(laptoprui, nrLaptopuri, nrCopiate);
	afisareLaptopVector(laptopuriCopiate, nrCopiate);
	printf("\n\n");

	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	int nrLaptopuriPutine = 0;
	Laptop* laptopuriPutine = copiazaLaptopuriPutine(laptoprui, nrLaptopuri, 50, &nrLaptopuriPutine);
	afisareLaptopVector(laptopuriPutine, nrLaptopuriPutine);
	printf("\n\n");
	Laptop laptopCautat = cautaLaptopDupaCod(laptoprui, nrLaptopuri, 1);
	printf("\nLaptopul cautat este:");
	afisareLaptop(laptopCautat);
	printf("\n");

	dezalocareVectorLaptop(&laptoprui, &nrLaptopuri);
	dezalocareVectorLaptop(&laptopuriPutine, &nrLaptopuriPutine);
	dezalocareVectorLaptop(&laptopuriCopiate, &nrCopiate);
	return 0;
	
}


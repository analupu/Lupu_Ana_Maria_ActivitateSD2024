#include <stdio.h>
#include <malloc.h>

typedef struct Laptop Laptop;
struct Laptop {
	char* denumire;
	int nrProduseStoc;
	float* preturi;
};

Laptop initializareLaptop(char* denumire, int nrProduseStoc, float* preturi) {
	Laptop laptop;
	laptop.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(laptop.denumire, denumire);
	laptop.nrProduseStoc = nrProduseStoc;
	laptop.preturi = (float*)malloc(sizeof(float) * laptop.nrProduseStoc);
	for (int i = 0; i < laptop.nrProduseStoc;i++) {
		laptop.preturi[i] = preturi[i];
	}
	return laptop;
}

float sumaPreturi(Laptop laptop) {
	float suma = 0;
	if (laptop.nrProduseStoc > 0) {
		for (int i = 0; i < laptop.nrProduseStoc;i++) {
			suma = suma + laptop.preturi[i];
		}
	}
	return suma;
}

void modificareCamp(Laptop* laptop, char* denumire) {
	if (laptop->denumire != NULL) {
		laptop->denumire = denumire;
		printf("\nDenumirea laptopului a fost modificata cu succes! ");
	}
}

void stergereLaptop(Laptop* laptop) {
	if (laptop->denumire != NULL) {
		free(laptop->denumire);
	}
	if (laptop->preturi != NULL) {
		free(laptop->preturi);
	}
	laptop->denumire = NULL;
	laptop->preturi = NULL;
}

void afisareLaptop(Laptop laptop) {
	if (laptop.denumire != NULL) {
		printf("\nDenumirea modelului este %s.", laptop.denumire);
	}
	printf("\nNumarul de produse care se afla in stoc este: %d", laptop.nrProduseStoc);
	if (laptop.nrProduseStoc > 0) {
		for (int i = 0; i < laptop.nrProduseStoc;i++) {
			printf("\nPretul produsului %d este: %5.2f.", i + 1, laptop.preturi[i]);
		}
	}
}

int main() {

	float* preturi1 = (float*)malloc(sizeof(float) * 3);
	preturi1[0] = 3000;
	preturi1[1] = 2500;
	preturi1[2] = 7200;
	Laptop l1 = initializareLaptop("Lenovo", 3, preturi1);
	afisareLaptop(l1);
	printf("\n");

	float suma = sumaPreturi(l1);
	printf("\nSuma preturilor este %5.2f.", suma);
}


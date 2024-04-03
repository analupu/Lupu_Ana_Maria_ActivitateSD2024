#include <stdio.h>
#include <malloc.h>

struct Farmacie {
	int id;
	char* nume;
	float suprafata;
};

struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata) {
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;
	return f;
}

void afisareFarmacie(struct Farmacie farmacie) {
	printf("%d. %s are o suprafata de %5.2f\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}

void afisareVector(struct Farmacie* farmacii, int nrFarmacii) {
	for (int i = 0; i < nrFarmacii; i++) {
		afisareFarmacie(farmacii[i]);
	}

	// printf("%5.2f", (float)sizeof(farmacii) / (float)sizeof(struct Farmacie)); 
}

//struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate) {
//	if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate > 0) {
//		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
//		for (int i = 0; i < nrObiecteCopiate; i++) {
//			copiat[i] = vector[i];
//		}
//		return copiat; //am facut shallow copy si nu functioneaza pentru alocari dinamice 
//	}
//}

struct Farmacie* copiazaNElemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate) {
	if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate > 0) {
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
		for (int i = 0; i < nrObiecteCopiate; i++) {
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
		return copiat;
	}
	else
	{
		return NULL;
	}
}

struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* nrFarmaciiMici) {
	// pas 1. verificam cate farmacii mici exista
	*nrFarmaciiMici = 0;
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {
			(*nrFarmaciiMici)++;
		}
	} //acum stim cata memorie trebuie sa alocam

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici)); // dereferentiere nrFarmaciiMici, pt ca este transmis prin pointer


	int k = 0; //index pentru vector
	for (int i = 0; i < nrFarmacii; i++) {
		if (farmacii[i].suprafata < pragSuprafata) {
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata); //postincrementare
		}
	}
	return vector;
}

//** pt ca daca as pune * adresa inca ramane => dangling pointer
void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii) {
	for (int i = 0; i < *nrFarmacii; i++) {
		free((*vector)[i].nume);
	}
	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}

struct Farmacie getFarmacieByID(struct Farmacie* vector, int nrFarmacii, int idCautat) {
	for (int i = 0; i < nrFarmacii; i++) {
		if (vector[i].id == idCautat) {
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}

	return initializareFarmacie(0, "N/A", 0); // farmacie default 
}

int main() {
	//int v[40]; //alocare statica pe stiva
	//int *v2=

	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++) {
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afisareVector(farmacii, nrFarmacii);

	int nrFarmaciiCopiate = 2;

	struct Farmacie* farmaciiCopiate = copiazaNElemente(farmacii, nrFarmacii, nrFarmaciiCopiate);
	printf("\n\n");
	afisareVector(farmaciiCopiate, nrFarmaciiCopiate);

	int nrFarmaciiMici = 0;
	farmacii[3].suprafata = 20;
	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici); //am primit pointer => &
	printf("\n\n");
	afisareVector(farmaciiMici, nrFarmaciiMici);

	struct Farmacie farmacieCautata = getFarmacieByID(farmacii, nrFarmacii, 3);

	printf("\nFarmacie cautata: \n");
	afisareFarmacie(farmacieCautata);
	free(farmacieCautata.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);
	dezalocareVectorFarmacii(&farmaciiCopiate, &nrFarmaciiCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);
	return 0;
}
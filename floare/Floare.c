#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>


typedef struct Floare Floare;
struct Floare {
	char* denumire;
	int nrBulbi;
	float inaltime;
};

typedef struct NOD NOD;
struct NOD {
	Floare info;
	NOD* st;
	NOD* dr;
};

// INITIALIZARE
Floare initializareFloare(const char* denumire, int nrBulbi, float inaltime) {
	Floare f;
	f.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy(f.denumire, denumire);
	f.nrBulbi = nrBulbi;
	f.inaltime = inaltime;
	return f;
}

// AFISARE UN OBIECT
void afisareFloare(Floare f) {
	printf("\nFloarea %s are %d bulbi si o inaltime de %5.2f centimetri. \n", f.denumire, f.nrBulbi, f.inaltime);
	printf("\n");
}

// CITIRE DIN FISIER
Floare citireFloareDinFisier(FILE* file) {
	Floare f;
	char buffer[50];
	fscanf(file, "%s", buffer);
	f.denumire = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
	strcpy(f.denumire, buffer);
	fscanf(file, "%d", &f.nrBulbi);
	fscanf(file, "%f", &f.inaltime);
	return f;
}

NOD* inaltimeArbore(NOD* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		int maxim;
		if (inaltimeST > inaltimeDR) {
			maxim = inaltimeST;
		}
		else {
			maxim = inaltimeDR;
		}
		maxim = maxim + 1;
		return maxim;
	}
	else {
		return NULL;
	}
}

int calculGradEchilibru(NOD* rad) {
	if (rad) {
		int inaltimeST = inaltimeArbore(rad->st);
		int inaltimeDR = inaltimeArbore(rad->dr);
		return inaltimeST - inaltimeDR;
	}
	else {
		return 0;
	}
}

NOD* rotireLaDreapta(NOD* rad) {
	if (rad) {
		NOD* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;
		return aux;
	}
	return rad;
}

NOD* rotireLaStanga(NOD* rad) {
	if (rad) {
		NOD* aux = rad->dr;
		rad->dr = aux->st;
		aux->st = rad;
		return aux;
	}
	return rad;
}

NOD* inserareArboreAVL(NOD* rad, Floare f) {
	if (rad) {
		if (rad->info.nrBulbi > f.nrBulbi) {
			rad->st = inserareArboreAVL(rad->st, f);
		}
		else {
			rad->dr = inserareArboreAVL(rad->dr, f);
		}

		if (calculGradEchilibru(rad) == 2) {
			if (calculGradEchilibru(rad->st == 1)) {
				rad = rotireLaDreapta(rad);
			}
			else {
				rad->st = rotireLaStanga(rad->st);
				rad = rotireLaDreapta(rad);
			}
		}
		if (calculGradEchilibru(rad) == -2) {
			if (calculGradEchilibru(rad->dr) == 1) {
				rad = rotireLaStanga(rad);
			}
			else {
				rad->dr = rotireLaDreapta(rad->dr);
				rad = rotireLaStanga(rad);
			}
		}
		return rad;
	}
	else {
		NOD* aux = (NOD*)malloc(sizeof(NOD));
		aux->info = f;
		aux->dr = NULL;
		aux->st = NULL;
		return aux;
	}
}

void afisareArboreSRD(NOD* rad) {
	if (rad) {
		afisareArboreSRD(rad->st);
		afisareFloare(rad->info);
		afisareArboreSRD(rad->dr);
	}
}
void afisareArboreRSD(NOD* rad) {
	if (rad) {
		afisareFloare(rad->info);
		afisareArboreSRD(rad->st);
		afisareArboreSRD(rad->dr);
	}
}

void afisareArboreSDR(NOD* rad) {
	if (rad) {
		afisareArboreSRD(rad->st);
		afisareArboreSRD(rad->dr);
		afisareFloare(rad->info);
	}
}

Floare cautaFloareDupaNumarBulbi (NOD* rad, int nrBulbi) {
	if (rad) {
		if (rad->info.nrBulbi == nrBulbi) {
			Floare floare = initializareFloare(rad->info.denumire, rad->info.nrBulbi, rad->info.inaltime);
			return floare;
		}
		else if (rad->info.nrBulbi > nrBulbi) {
			return cautaFloareDupaNumarBulbi(rad->st, nrBulbi);
		}
		else {
			return cautaFloareDupaNumarBulbi(rad->dr, nrBulbi);
		}
	}
	else {
		return initializareFloare(" ", -1, -1);
	}
}

void main() {
	Floare f1 = initializareFloare("Lalea", 10, 20);
	Floare f2 = initializareFloare("Narcisa", 5, 25);
	afisareFloare(f1);

	printf("*******************************\n");
	FILE* f = fopen("flori.txt", "r");
	if (f) {
		int nrFlori = 0;
		fscanf(f, "%d", &nrFlori);
		for (int i = 0; i < nrFlori;i++) {
			Floare floare = citireFloareDinFisier(f);
			afisareFloare(floare);
		}
	}
	fclose(f);

	printf("------------------------------- // ------------------------------\n");
	NOD* rad = NULL;
	FILE* fisier = fopen("flori.txt", "r");
	if (fisier) {
		int nrFlori = 0;
		fscanf(fisier, "%d", &nrFlori);
		for (int i = 0; i < nrFlori;i++) {
			rad = inserareArboreAVL(rad, citireFloareDinFisier(fisier));
		}
	}
	fclose(fisier);
	afisareArboreSRD(rad);
	printf("\n************************\n");
	int inaltime = inaltimeArbore(rad);
	printf("\nInaltimea arborelui este %d.\n", inaltime);

	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	NOD* radacina = NULL;
	radacina = inserareArboreAVL(radacina, f1);
	radacina = inserareArboreAVL(radacina, f2);
	afisareArboreSRD(radacina);
	printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	Floare cautare;
	cautare = cautaFloareDupaNumarBulbi(rad, 10);
	afisareFloare(cautare);
}
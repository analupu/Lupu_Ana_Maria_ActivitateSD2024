#include <stdio.h>
#include <malloc.h>

typedef struct Santier Santier;
typedef struct NodLDi NodLDi;
struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct NodLDi {
    NodLDi* prev;
    NodLDi* next;
    Santier info;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
    NodLDi* prim;
    NodLDi* ultim;
};

void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {
    NodLDi* nod = lista->prim;
    while (nod != NULL) {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
            if (nod->prev = NULL) { //adica daca este primul nod 
                if (nod->next == NULL) {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else {
                if (nod->next == NULL) {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }

            free(nod->info.numeProiect);
            free(nod);
            //break;
            nod = NULL;
        }
        else {
            nod = nod->next;
        }
    }
}

void inserareInceput(ListaDubla* lista, Santier santier) {
    NodLDi* aux = malloc(sizeof(NodLDi));
    aux->info = santier;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {
        lista->ultim = aux;
    }
    lista->prim = aux;
}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

void afisareSantier(Santier santier) {
    printf("Santierul %s are %d muncitori si %5.2f m2 suprafata.\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

void afisareLDiDeLaInceput(ListaDubla lista) {
    for (NodLDi* nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
    printf("\n\n");
}

//numele santierului cu densitatea cea mai mare de muncitori pe m2
float densitateMuncitori(Santier santier) {
    if (santier.suprafata != 0) {
        return santier.nrMuncitori / santier.suprafata;
    }
    else
        return 0;
}

void stergereCompleta(ListaDubla* lista) {
    if (lista != NULL) {
        NodLDi* aux = lista->prim;
        while (aux != NULL) {
            free(aux->info.numeProiect);
            NodLDi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

int calcNrTotalMuncitori(ListaDubla lista) {
    int suma = 0;
    for (NodLDi* i = lista.prim; i != NULL; i = i->next) {
        suma = suma + i->info.nrMuncitori;
    }
    return suma;
}

int main() {
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);
    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;

    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    afisareLDiDeLaInceput(lista);
    /*stergereSantierDupaNume(&lista, "Santier 2");
    afisareLDiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 1");
    afisareLDiDeLaInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 3");
    afisareLDiDeLaInceput(lista);*/
    int suma = calcNrTotalMuncitori(lista);
    printf("Numarul de muncitori este %d", suma);
    stergereCompleta(&lista);
    afisareLDiDeLaInceput(lista);


}

//lista dubla nu se parcurge
//stergem nodul cu santierul care contine un nume dat
//numarul total de muncitori din lista dublu inlantuit
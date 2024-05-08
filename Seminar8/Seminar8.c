#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Mail Mail;
struct Mail {
	char* text;
	int prioritate;
};

typedef struct Heap Heap;
struct Heap {
	Mail* vector;
	int dim;
};

Heap initializareHeap(int dim) {
	Heap heap;
	heap.vector = (Mail*)malloc(dim * sizeof(Mail));
	heap.dim = dim;
	return heap;
}

Mail initializareMesaj(const char* text, int prioritate) {
	Mail mail;
	mail.text = (char*)malloc(strlen(text) + 1);
	strcpy(mail.text, text);
	mail.prioritate = prioritate;
	return mail;
}

void afisareMail(Mail mail) {
	printf("Mail cu textul: %s si grad de prioritate %d\n", mail.text, mail.prioritate);
}

void afisareHeap(Heap heap) {
	for (int i = 0;i < heap.dim;i++)
		afisareMail(heap.vector[i]);
}

void filtrare(Heap heap, int pozRad) {
	int fs = pozRad * 2 + 1;
	int fd = pozRad * 2 + 2;
	int pozMax = pozRad;

	if (fs < heap.dim && heap.vector[pozMax].prioritate < heap.vector[fs].prioritate) {
		pozMax = fs;
		//acum comparam fiul din stanga cu cel din dreapta
		if (fs < heap.dim && heap.vector[fs].prioritate)
			pozMax = fs;

		if (fd < heap.dim && heap.vector[fd].prioritate)
			pozMax = fd;

	}

	if (pozMax != pozRad) {

		if (heap.vector[pozMax].prioritate > heap.vector[pozRad].prioritate)
		{
			Mail aux = heap.vector[pozRad];
			heap.vector[pozRad] = heap.vector[pozMax];
			heap.vector[pozMax] = aux;

			if (pozMax < (heap.dim - 2) / 2) {
				filtrare(heap, pozMax);
			}

		}
	}
}

Mail extragereMax(Heap* heap) { //in cazul asta transmit prin pointer pentru ca modific atat vetorul(ii aloc alta dimensiune), cat si dim
	if (heap->dim > 0) {
		Mail extras = (*heap).vector[0];
		Mail* aux = (Mail*)(malloc(sizeof(Mail) * (*heap).dim - 1));
		for (int i = 1; i < heap->dim; i++)
			aux[i - 1] = heap->vector[i];

		free(heap->vector);
		heap->vector = aux;

		heap->dim--;

		for (int i = (heap->dim - 2) / 2; i >= 0;i--) //trebuie sa sortam elementele care au ramas 
			filtrare((*heap), i);

		return extras;
	}

}

void inserareMailInHeap(Heap* heap, Mail mail) {
	//adaugam elemente pe prima pozitie apoi filtram
	Mail* aux = (Mail*)(malloc(sizeof(Mail) * (heap->dim + 1)));

	aux[0] = mail;

	for (int i = 1; i < heap->dim + 1;i++)
		aux[i] = heap->vector[i - 1];

	free(heap->vector);
	heap->vector = aux;
	heap->dim++;

	filtrare((*heap), 0); //filtram doar pt primul de aceasta data pt ca o sa se apeleze recursiv
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0;i < heap->dim;i++)
	{
		free(heap->vector[i].text);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->dim = 0;
}

void main() {
	Heap heap = initializareHeap(6);
	heap.vector[0] = initializareMesaj("Salut", 7);
	heap.vector[1] = initializareMesaj("Salut", 9);
	heap.vector[2] = initializareMesaj("Salut", 3);
	heap.vector[3] = initializareMesaj("Salut", 8);
	heap.vector[4] = initializareMesaj("Salut", 6);
	heap.vector[5] = initializareMesaj("Salut", 10);

	afisareHeap(heap);
	printf("----------filtrat:----------\n");

	for (int i = (heap.dim - 2) / 2; i >= 0;i--)
		filtrare(heap, i);

	afisareHeap(heap);

	printf("-------elemente extrase: ---------\n");
	//de preferat extragem in cazul unor obiecte pe care sa le putem sterge dupa afisare
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));
	afisareMail(extragereMax(&heap));

	printf("-------inserare: ---------\n");
	Mail mail = initializareMesaj("Buna ziua", 6);
	Mail mail2 = initializareMesaj("Buna ziua", 10);
	Mail mail3 = initializareMesaj("Buna ziua", 4);
	Mail mail4 = initializareMesaj("Buna ziua", 1);


	inserareMailInHeap(&heap, mail);
	inserareMailInHeap(&heap, mail2);
	inserareMailInHeap(&heap, mail3);
	inserareMailInHeap(&heap, mail4);

	afisareHeap(heap);

	dezalocareHeap(&heap);

} 
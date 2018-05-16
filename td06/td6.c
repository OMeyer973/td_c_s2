#include <stdio.h>
#include <stdlib.h>

#define N 100 //nombre d'éléments
#define M 100000 //nombre d'opérations
#define PERE 0
#define RANG 1

static unsigned int cherchePere=0;

void affichePeres(int peres[N][2]) {
	//affiche le tableau représentant la partition
	int i=0;
	printf("------------\n");
	for (i=0; i<N; i++) {
		printf("%d %d\n", peres[i][PERE], peres[i][RANG]);
	}
	printf("------------\n");
}

void initialisation(int peres[N][2]) {
	//initialise le tableau peres afin qu’il représente N ensembles de 1 élément.
	int i=0;
	for (i=0; i<N; i++) {
		peres[i][PERE] = i;
		peres[i][RANG] = 1;
	}
}

int trouve(int peres[N][2], int x) {
	//envoie la valeur du représentant de l’ensemble contenant x (et augmente cherchePere du nombre d’étapes).
	while (peres[x][PERE] != x) {
		x = peres[x][PERE];
		cherchePere++;
	}
	return x;
}

void fusion(int peres[N][2], int x, int y) {
	//effectue la fusion (sans utiliser le rang) de l’ensemble contenant x et de celui contenant y.
	int rx = trouve(peres, x);
	int ry = trouve(peres, y);

	peres[rx][RANG] += peres[ry][RANG];
	peres[ry][PERE] = rx;
}

int trouveCompresse(int peres[N][2], int x) {
	//envoie la valeur du représentant de l’ensemble contenant x (et augmente cherchePere du nombre d’étapes). Les chemins seront compressés.
	int i = peres[x][PERE];

	while (peres[i][PERE] != i) {

		trouveCompresse(peres, i);
		i = peres[i][PERE];
		cherchePere++;
	}

	peres[x][PERE] = i;
	return i;
}

void fusionRang(int peres[N][2], int x, int y) {
	//effectue la fusion (sans utiliser le rang) de l’ensemble contenant x et de celui contenant y.
	int rx = trouveCompresse(peres, x);
	int ry = trouveCompresse(peres, y);
	if (peres[rx][RANG] >= peres[ry][RANG]) {

		peres[rx][RANG] += peres[ry][RANG];
		peres[ry][PERE] = rx;
	} else {
		peres[ry][RANG] += peres[rx][RANG];
		peres[rx][PERE] = ry;
	}
}


int main () {
	int  peres[N][2];
	initialisation(peres);

	int i =0;
	for (i=0; i<M; i++) {
		fusion(peres, random()%N, random()%N);
	}
	printf("nb d'opérations naïves : %d\n",cherchePere);

	cherchePere=0;
	initialisation(peres);
	for (i=0; i<M; i++) {
		fusionRang(peres, random()%N, random()%N);
	}
	printf("nb d'opérations optimisées : %d\n",cherchePere);
	return 0;
}

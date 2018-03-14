#include <stdio.h>

#define MAX 3


typedef struct {
	int taille;
	int arbre[MAX];
} Tas;

void printTab(int tab[MAX]) {
	int i =0;
	for (i=0; i<MAX; i++) {
		printf("%d ",tab[i]);
	}
	printf("\n");
}

void zeros(int tab[MAX]) {
	int i =0;
	for (i=0; i<MAX; i++) {
		tab[i] = 0;
	}	
}

int estTas(int perm[]) {
	//T0D0
	return 1;
}

int enumPerm(int perm[], int premier, int n) {
	if (premier > n) {
		printTab(perm);
		return 1;
	}

	int nbPerm = 0;
	int i = 0;
	for (i=0; i < n; i++) {
		
		//trouver une case tq i ne dépasse pas la borne
		if (perm[i] <= 0){
			perm[i] = premier;

			//appel récursif, incrémenter nbPerm
			nbPerm += enumPerm(perm, premier + 1, n);
			perm[i] = 0;
		}
	}
	return nbPerm;
}

int enumTas(int perm[], int premier, int n) {
	
	if (premier > n) {
		if (estTas(perm)) {
			printTab(perm);
			return 1;
		}
		return 0;
	}

	int nbPerm = 0;
	int i = 0;
	for (i=0; i < n; i++) {
		
		//trouver une case tq i ne dépasse pas la borne
		if (perm[i] <= 0){
			perm[i] = premier;

			//appel récursif, incrémenter nbPerm
			nbPerm += enumPerm(perm, premier + 1, n);
			perm[i] = 0;
		}
	}
	return nbPerm;
}

int main() {

	int tab[MAX];
	zeros(tab);
	int nbperm = enumPerm(tab, 1, MAX);

	printf("%d\n",nbperm);
	return 0;
}
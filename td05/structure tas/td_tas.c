#include <stdio.h>

#define MAX 50
/*
1.a.
----------
est un tas

		     1
       5           7
    6     5     8     9
  12 7   5 8   9


1.b.
----------
pas un tas

		     4
       5           8
    6     6     9     8
   7 5  11


3.
----------
indice du parent du noeud à la position i :
(i - 1) / 2		(division entière)


4.
----------
indice du fils gauche du noeud à la position i : 
	j = 2 * i + 1
indice du fils droit du noeud à la position i : 
	j = 2 * i + 2

5.
----------
        1
   5         4
14   13   20

6.
----------
        5
   14         4
20    13   


*/

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

int estTas(int tab[], int taille) {
	/*vérifie si le tableau représente un tas à partir de l'indice i*/
	//pas encore vérifié
	int i = 0;
	for (i=0; taille/2; i++){
		if (2 * i + 1 < taille && tab[i] > tab[2 * i + 1])
			return 0;
		if (2 * i + 2 < taille && tab[i] > tab[2 * i + 2])
			return 0;
	}
	return 1;	
}


int main() {

	int tab[MAX];
	zeros(tab);

	return 0;
}
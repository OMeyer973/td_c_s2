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
        4
   5         20
14    13   


notes : dans un arbre de hauteur h, les noeuds à la hauteur k sont les
[2^(k-1) , 2^(k+1)-1[ pour k < h-1
[2^(h-1)-1, n[		  pour k = h-1
*/

typedef struct {
	int taille;
	int* arbre;
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

int estTasIt(int tab[], int taille) {
	/*vérifie si le tableau représente un tas 
	version itérative moins optimisée (on vérifie certains noeuds plusieurs fois)*/
	int i = 0;
	for (i=0; i<=taille/2; i++){
		//fg <= noeud courant ?
		if (2 * i + 1 < taille && tab[i] > tab[2 * i + 1])
			return 0;
		//fd <= noeud courant ?
		if (2 * i + 2 < taille && tab[i] > tab[2 * i + 2])
			return 0;
	}
	return 1;	
}

int estTasRec(int tab[], int taille, int i) {
	/*vérifie si le tableau représente un tas de manière récursive 
	(fonction auxiliaire qui vérifie uniquement les fils de du noeud à l'indice i)*/
	if (i >= taille)
		return 1;

	//fg <= noeud courant ?
	if (2 * i + 1 < taille && tab[2 * i + 1] < tab[i])
		return 0;
	//fd <= noeud courant ?
	if (2 * i + 2 < taille && tab[2 * i + 2] < tab[i])
		return 0;

	return 
		estTasRec(tab, taille, 2 * i + 1) && 
		estTasRec(tab, taille, 2 * i + 2);
}

int estTas(int tab[], int taille) {
	/*vérifie si le tableau représente un tas*/
	return estTasRec(tab, taille, 0);
}

int fils(Tas tas, int i) {
	//si pas de fg (dc pas de fd non plus) on renvoie -1
	if (2 * i + 1 < tas.taille)
		return -1;
	
	int imin = tas.arbre[2 * i + 1];
	//si pas de fd, on renvoie l'indice de fg
	if (2 * i + 2 < tas.taille)
		return imin;
	//sinon on renvie le min des 2
	if (tas.arbre[2 * i + 2] < tas.arbre[imin])
		imin = 2 * i + 2;
	return imin;
}

int filsMax(Tas tas, int i) {
	//si pas de fg (dc pas de fd non plus) on renvoie -1
	if (2 * i + 1 < tas.taille)
		return -1;
	
	int imax = tas.arbre[2 * i + 1];
	//si pas de fd, on renvoie l'indice de fg
	if (2 * i + 2 < tas.taille)
		return imax;
	//sinon on renvie le max des 2
	if (tas.arbre[imax] < tas.arbre[2 * i + 2])
		imax = 2 * i + 2;
	return imax;
}


void change(Tas *t, int indice, int valeur) {
	
	if (indice >= t->taille) {
		printf("veuillez entrer un indice compris dans le tableau\n");
		return;
	}

	int idp = (indice - 1) / 2; //indice du parent du noeud. si le noeud est la racine, renvoie l'indice du noeud
	//si la valeur de remplacement est plus petite que le père, on les échange et on itère sur le père (ie la nouvelle position où on va tenter d'insérer la valeur)
	if (valeur < t->arbre[idp] && idp != indice) {
		t->arbre[indice] = t->arbre[idp];
		return change(t, idp, valeur);
	}
		
	int idf = fils(*t, indice); //indice du fils minimal du noeud
	//si la valeur de remplacement est plus grande que le plus petit fils, on les échange et on itère sur ledit fils (ie la nouvelle position où on va tenter  d'insérer la valeur)
	if (t->arbre[idf] < valeur) {
		t->arbre[indice] = t->arbre[idf];
		return change(t, idf, valeur);
	}

	t->arbre[indice] = valeur;
}

int ajout(Tas *t, int valeur) {
	if (MAX <= t->taille) {
		printf("arbre plein. impossible d'ajouter une nouvelle valeur\n");
		return 0;
	}
	t->taille++;
	change(t, t->taille-1, valeur);
	return 1;
}

int main() {
	int tab[MAX] = {1,5,7,6,5,8,9,12,7,5,8,9};
	Tas tas;
	tas.arbre = tab;
	tas.taille = 12;

	int tab1[MAX] = {4,5,8,6,6,9,8,7,5,11};
	Tas tas1;
	tas1.arbre = tab1;
	tas1.taille = 10;

	estTas(tas.arbre, tas.taille) ? printf("tab est tas\n") : printf("tab non tas\n");
	estTas(tas1.arbre, tas1.taille) ? printf("tab1 est tas\n") : printf("tab1 non tas\n");

	ajout(&tas, 2);
	return 0;
}
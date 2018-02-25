#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct noeud {
	int valeur;
	struct noeud* fg;
	struct noeud* fd;
} Noeud, *Arbre;


Arbre alloueArbre (int val) {
/*alloue un espace mémoire à un arbre de valeur "val", fg NULL, fd NULL
et et retourne son adresse*/
	Arbre tmp;
	tmp = (Noeud*)malloc(sizeof(Noeud));
	if (tmp != NULL) {
		tmp->valeur = val;
		tmp->fd = NULL;
		tmp->fg = NULL;
	}
	return tmp;
}

void afficheArbJoli(Arbre a, int niv) {
	int i = 0;
	for (i=0; i<niv; i++) {
		printf("|   ");
	}
	if (a == NULL)
		printf("NULL\n");
	else {

		printf("%d\n", a->valeur);
		afficheArbJoli(a->fg, 1 + niv);
		afficheArbJoli(a->fd, 1 + niv);
	}
}

/*
On considère des arbres binaires quelconques, etiquettés par des entiers relatifs. Toute
valeur peut apparaitre dans l’arbre.
Tout type de nœud peut apparaitre dans l’arbre: 0 fils, un seul fils droit, 1 seul fils
gauche, deux fils. Pour décrire un tel arbre, on effectue un parcours en profondeur de
l’arbre en indiquant pour chaque nœud rencontré son type et son étiquette. Pour le
type du nœud on convient d’utiliser
• 0 pour une feuille nœud interne,
• 1 pour u nœud avec un seul fils droit,
• 2 pour un nœud avec un seul fils gauche,
• 3 pour un nœud avec 2 fils
*/

Arbre construitArbQuelconque() {
	/*construit un arbre quelconque décrit par son parcours en profondeur*/
	int fils=0, etiquette=0;
	Arbre a = NULL;
	scanf("%d",&fils);
	scanf("%d",&etiquette);
	a = alloueArbre(etiquette);
	if (fils == 1 || fils == 3) 
		a-> fg = construitArbQuelconque(a->fg);
	if (fils == 2 || fils == 3) 
		a-> fd = construitArbQuelconque(a->fd);
	/*if (fils == 0) inutile : cas par défaut*/
	return a;
}

void ecritArbreQuelconque(Arbre a) {
	/*affiche le parcours en profondeur de l'arbre quelconque a*/
	if (a != NULL) {
		if (a->fg == NULL && a->fd == NULL)
			printf("0 ");
		if (a->fg != NULL && a->fd == NULL)
			printf("1 ");
		if (a->fg == NULL && a->fd != NULL)
			printf("2 ");
		if (a->fg != NULL && a->fd != NULL)
			printf("3 ");
		printf("%d ",a->valeur);
		ecritArbreQuelconque(a->fg);
		ecritArbreQuelconque(a->fd);
	}
}

int main () {

	Arbre tmp = NULL;
	printf("construisez un arbre\n");
	tmp = construitArbQuelconque();
	printf("\n voici votre arbre : \n");
	ecritArbreQuelconque(tmp);
	printf("\n et le voici joliment déssiné :) : \n");
	afficheArbJoli(tmp,0);

	

return 0;
}
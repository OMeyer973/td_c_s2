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

Arbre litArbQuelconque() {
	/*construit un arbre quelconque décrit par son parcours en profondeur par l'utilisateur*/
	int fils=0, etiquette=0;
	Arbre a = NULL;
	scanf("%d",&fils);
	scanf("%d",&etiquette);
	a = alloueArbre(etiquette);
	if (fils == 1 || fils == 3) 
		a-> fg = litArbQuelconque();
	if (fils == 2 || fils == 3) 
		a-> fd = litArbQuelconque();
	/*if (fils == 0) inutile : cas par défaut*/
	return a;
}

void afficheArbreQuelconque(Arbre a) {
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
		afficheArbreQuelconque(a->fg);
		afficheArbreQuelconque(a->fd);
	}
}





Arbre construitArbQuelconque(FILE *in) {
	/*construit un arbre quelconque décrit par son parcours en profondeur dans le fichier*/
	int fils=0, etiquette=0;
	Arbre a = NULL;
	if (fscanf(in, "%d", &fils) != EOF) {
		if (fscanf(in, "%d", &etiquette)) {
			a = alloueArbre(etiquette);
			if (fils == 1 || fils == 3) 
				a-> fg = construitArbQuelconque(in);
			if (fils == 2 || fils == 3) 
				a-> fd = construitArbQuelconque(in);
			/*if (fils == 0) inutile : cas par défaut*/
		}
	}
	return a;
}

void ecritArbreQuelconque(Arbre a, FILE* out) {
	/*ecrit le parcours en profondeur de l'arbre quelconque a dans le fichier*/
	if (a != NULL) {
		if (a->fg == NULL && a->fd == NULL)
			fprintf(out, "0 ");
		if (a->fg != NULL && a->fd == NULL)
			fprintf(out, "1 ");
		if (a->fg == NULL && a->fd != NULL)
			fprintf(out, "2 ");
		if (a->fg != NULL && a->fd != NULL)
			fprintf(out, "3 ");
		fprintf(out, "%d ", a->valeur);
		ecritArbreQuelconque(a->fg, out);
		ecritArbreQuelconque(a->fd, out);
	}
}

int main () {

	FILE *in = NULL;
	FILE *out = NULL;
	in = fopen("ArbreIn", "r");
	out = fopen("ArbreOut", "w");

	Arbre tmp1 = NULL;
	printf("lecture du fichier d'entrée\n");
	tmp1 = construitArbQuelconque(in);
	printf("\n votre arbre s'ecrit dans le fichier de sortie\n");
	ecritArbreQuelconque(tmp1, out);
	printf("\n et le voici joliment déssiné :) : \n");
	afficheArbJoli(tmp1,0);

	fclose(in);
	fclose(out);

	Arbre tmp = NULL;
	printf("construisez un arbre\n");
	tmp = litArbQuelconque();
	printf("\n voici votre arbre : \n");
	afficheArbreQuelconque(tmp);
	printf("\n et le voici joliment déssiné :) : \n");
	afficheArbJoli(tmp,0);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
1/ a)
racine : a
feuilles : h n i e d
h = 2 : e c
niv 3 : h n j e d

c)
préfixe : a z x h n e j i c g e d
suffixe : h n x i j e z e d g c a
infixe : h n x z e j i a c e g d

e)
1 feuille : 0
vide : -1
celui là : 4
z : 3
*/

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

void debug(Arbre a) {
	int hg = 0, hd = 0;
	if (a->fg != NULL)
		hg = a->fg->valeur;
	if (a->fd != NULL)
		hd = a->fd->valeur;
	printf("%d, fg %d, fd %d\n", a->valeur, hg, hd);
}

int hauteur (Arbre a) {
	/*retourne la hauteur de l'arbre a*/
	if (a == NULL)
		return -1;
	int hg = 0, hd = 0; /*hauteur gauche, hauteur droit*/
	hg = hauteur(a->fg);
	hd = hauteur(a->fd);
	if (hg >= hd)
		return 1 + hg;
	else
		return 1 + hd;
}

int nbNoeuds (Arbre a) {
	/*retourne le nombre de noeuds de l'arbre a*/
	if (a == NULL)
		return 0;
	int ng, nd; /*nb de noeuds droits et noeuds gauches*/
	ng = nbNoeuds(a->fg);
	nd = nbNoeuds(a->fd);
	return 1 + ng + nd;
}

int nbNoeudsInternes (Arbre a) {
	/*retourne le nombre de noeuds internes de l'arbre a*/
	if (a == NULL)
		return 0;
	if (a->fg == NULL && a->fd == NULL)
		return 0;
	int ng, nd; /*nb de noeuds droits et noeuds gauches*/
	ng = nbNoeudsInternes(a->fg);
	nd = nbNoeudsInternes(a->fd);
	return 1 + ng + nd;
}

int nbFeuilles (Arbre a) {
	/*retourne le nombre de feuilles l'arbre a*/
	if (a == NULL)
		return 0;
	if (a->fg == NULL && a->fd == NULL)
		return 1;
	int ng, nd; /*nb de noeuds droits et noeuds gauches*/
	ng = nbFeuilles(a->fg);
	nd = nbFeuilles(a->fd);
	return ng + nd;
}

int nbNoeudsAvec2Fils (Arbre a) {
	/*retourne le nombre de feuilles l'arbre a*/
	if (a == NULL)
		return 0;
	int n = 1;
	if (a->fg == NULL || a->fd == NULL)
		n = 0;
	int ng, nd; /*nb de noeuds droits et noeuds gauches*/
	ng = nbNoeudsAvec2Fils(a->fg);
	nd = nbNoeudsAvec2Fils(a->fd);
	return n + ng + nd;
}

void afficheArbPositif(Arbre a) {
	/*affiche le parcours prefixe de l'arbre positif a*/
	if (a == NULL)
		printf("0 ");
	else {
		printf("%d ", a->valeur);
		afficheArbPositif(a->fg);
		afficheArbPositif(a->fd);
	}
}

void afficheArbJoli(Arbre a, int niv) {
	int i = 0;
	for (i=0; i<niv; i++) {
		printf("|   ");
	}
	if (a == NULL)
		printf("0\n");
	else {

		printf("%d\n", a->valeur);
		afficheArbJoli(a->fg, 1 + niv);
		afficheArbJoli(a->fd, 1 + niv);
	}
}

Arbre construitArbPositif() {
	/*construit un arbre décrit par son parcours prefixe (entrées utilisateur)*/
	int n;
	Arbre a = NULL;
	scanf("%d",&n);
	if (n <= 0)
		return a;
	a = alloueArbre(n);
	a->fg = construitArbPositif(a->fg);
	a->fd = construitArbPositif(a->fd);
	return a;
}

int estHG(Arbre a) {
	if (a == NULL) 
		return 1;
	if (nbFeuilles(a->fg) < nbFeuilles(a->fd)) {
		return 0;
	}
	return (estHG(a->fg) * estHG(a->fd));
}


int main () {
	/*arbre dessiné sur le sujet*/
	Arbre h = NULL;
	h = alloueArbre(1);
	Arbre n = NULL;
	n = alloueArbre(2);
	Arbre x = NULL;
	x = alloueArbre(3);
	x->fg = h;
	x->fd = n;
	Arbre i = NULL;
	i = alloueArbre(4);
	Arbre j = NULL;
	j = alloueArbre(5);
	j->fd = i;
	Arbre e = NULL;
	e = alloueArbre(6);
	e->fg = j;
	Arbre z = NULL;
	z = alloueArbre(7);
	z->fg = x;
	z->fd = e;
	Arbre u = NULL;
	u = alloueArbre(8);
	Arbre d = NULL;
	d = alloueArbre(9);
	Arbre g = NULL;
	g = alloueArbre(10);
	g->fg = u;
	g->fd = d;
	Arbre c = NULL;
	c = alloueArbre(11);
	c->fd = g;
	Arbre a = NULL;
	a = alloueArbre(12);
	a->fg = z;
	a->fd = c;

	printf("hauteur de a : %d\n", hauteur(a));
	printf("nbNoeuds de a : %d\n", nbNoeuds(a));
	printf("nbFeuilles de a : %d\n", nbFeuilles(a));
	printf("nbNoeudsInternes de a : %d\n", nbNoeudsInternes(a));
	printf("nbNoeudsAvec2Fils de a : %d\n", nbNoeudsAvec2Fils(a));
	afficheArbPositif(a);
	printf("\n");
	afficheArbJoli(a,0);
	
	Arbre tmp = NULL;
	printf("construisez un arbre");
	tmp = construitArbPositif();
	afficheArbPositif(tmp);


return 0;
}
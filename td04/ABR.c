#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct noeud {
    int valeur;
    struct noeud* fg;
    struct noeud* fd;
} Noeud, *Arbre;

/*fonctions préliminaires*/

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
	/* affiche l'arbre a sous la forme d'une arborescence (fg en haut, fd en bas)
	Pour appeller le dessin de l'arbre a, taper afficherArbJoli(a,0); */
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

int getMinABR (Arbre a) {
   /*renvoie le min de l'abr*/
    if (a == NULL) {
        fprintf(stderr, "l'arbre est NULL\n");
        exit(EXIT_FAILURE);
    }
    
    while (a->fg != NULL) 
        a = a->fg;

    return a->valeur;
}

int getMaxABR (Arbre a) {
   /*renvoie le max de l'abr*/
    if (a == NULL) {
        fprintf(stderr, "l'arbre est NULL\n");
        exit(EXIT_FAILURE);
    }

    while (a->fd != NULL) 
        a = a->fd;

    return a->valeur;
}
 
Arbre insereDansABRRecursif (Arbre* a, int x) {
    /*insere la valeur b dans l'ABR a et renvoie l'adresse du noeud créé*/
    if (*a == NULL) {
        Arbre tmp = alloueArbre(x);
        *a = tmp;
        return *a;
    }
    if (x < (*a)->valeur)
        return insereDansABRRecursif(&((*a)->fg), x);
    return insereDansABRRecursif(&((*a)->fd), x);
}

void parcourInfixe (Arbre a) {
    /*affiche le parcours infixe de l'arbre (tous les noeuds de gauche à droite)*/
    if (a == NULL)
        return;
    if (a->fg != NULL)
        parcourInfixe(a->fg);
    printf("%d ",a->valeur);
    if (a->fd != NULL)
        parcourInfixe(a->fd);
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

/*debut du tp*/
/*////////////////////////////////////////////////////////*/



/*
//methode 1 mais implantation raté !!! ne marche pas !!!
int estABRRec(Arbre a, int* minFd, int* maxFg) {
    if (a == NULL)
        return 1;

    if (a->fg == NULL)
        *maxFg = a->valeur;
    else {
        if (a->fg->valeur < *minFd && estABRRec(a->fg, minFd, maxFg))
            return 1;
    }

    if (a->fd == NULL)
        *minFd = a->valeur;
    else {
        if (a->fd->valeur < *maxFg && estABRRec(a->fd, minFd, maxFg))
            return 1;
    }
    return 0;
}

int estABR(Arbre a) {
    if (a == NULL)
        return 1;

    int minFd = a->valeur;
    int maxFg = a->valeur;
    return estABRRec(a, &minFd, &maxFg);
}
*/


int estABRInfixeRec (Arbre a, int* prev, int* curr) {
    /*fonction récursive de la fonction qui teste si l'arbre est un abr (comparaison 2 à 2 des valeurs renvoyées par le parcours infixe)*/
    /*je crois que ça marche*/
    if (a == NULL)
        return 1;

    int out = 1; /*valeur de rendu*/

    /*test fg*/
    if (a->fg != NULL)
        out = estABRInfixeRec(a->fg, prev, curr);

    /*test racine*/
    if (*prev > *curr)
        return 0;
    else  {
        *prev = *curr;
        *curr = a->valeur;
    }

    /*test fd*/
    if (a->fd != NULL)
        out = out && estABRInfixeRec(a->fd, prev, curr);

    return out;
}


int estABR (Arbre a) {
    /*methode naïve  
    on peut avoir fg < a < fd; fg ABR; fd ABR; mais a non ABR
    condition supplémentaire : max (fg) < min(fd)
    */
    /*methode 1 : méthode naïve mais corrigée : on stocke un min et un max (mis à jour à mesure du percours) pour vérifier que chaque valeur du fd es > au max du fg et chaque valeur du fg est < au min du fd 
    */
    /*methode 2 : parcours infixe et on verifie que les éléments retournés sont bien criossants
    application : stocker le parcours infixe dans une liste chainée ou un tableau dynamique pour ensuite pouvoir vérifier l'ordre des éléments
    */
    /*on fait la méthode 2 ici :*/
    if (a == NULL)
        return 1;

    int minFd, maxFg;
    minFd = maxFg = getMinABR(a);

    return estABRInfixeRec(a, &minFd, &maxFg);
}

void afficheChemin(int* chemin, int hauteur) {
    /*affiche le chemin chemin jusqu'à la hauteur donnée (affiche les "hauteur" premiers éléments de la liste "chemin")*/
    int i = 0;
    for (i=0; i<=hauteur; i++) {
        printf("%d ", chemin[i]);
    }
    printf("\n");
}

void cheminsDesFeuillesRec(Arbre a, int* chemin, int hauteur) {
    /*fonction récursive affiche les chemins de toutes les feuilles de l'arbre*/
    
    if (a == NULL)
        return;
    
    chemin[hauteur] = a->valeur;

    if (a->fg != NULL)
        cheminsDesFeuillesRec(a->fg, chemin, hauteur + 1);
    
    if (a->fd != NULL)
        cheminsDesFeuillesRec(a->fd, chemin, hauteur + 1);
    
    if (a->fd == NULL && a->fg == NULL)
        afficheChemin(chemin, hauteur);
}

void afficheCheminsDesFeuilles(Arbre a) {
    int chemin[hauteur(a)];
    cheminsDesFeuillesRec (a, chemin, 0);
}


int main () {

	Arbre a = NULL; 
	insereDansABRRecursif(&a,2);
	insereDansABRRecursif(&a,4);
	insereDansABRRecursif(&a,2);
	insereDansABRRecursif(&a,7);
	insereDansABRRecursif(&a,5);
	insereDansABRRecursif(&a,5);
	insereDansABRRecursif(&a,-5);
	insereDansABRRecursif(&a,7);
	insereDansABRRecursif(&a,3);
	insereDansABRRecursif(&a,0);
	insereDansABRRecursif(&a,1);
	insereDansABRRecursif(&a,-5);
	insereDansABRRecursif(&a,-9);
	insereDansABRRecursif(&a,-6);
	printf("l'arbre a : \n");
    afficheArbJoli(a,0);

	(estABR(a)) ? printf("a est un ABR !\n") : printf("a n'est pas ABR :(\n"); /*a est censé être un ABR*/
    printf("parcours infixe : ");
    parcourInfixe(a);
	printf("\n\n");

    printf("chemins de toutes les feuilles de l'arbre :\n");
    afficheCheminsDesFeuilles(a);
    printf("\n");
    Arbre b = alloueArbre(0);
    b->fg = alloueArbre(-1);
    b->fg->fd = alloueArbre(-2);

    printf("l'arbre b : \n");
    afficheArbJoli(b,0);
    (estABR(b)) ? printf("b est un ABR !\n") : printf("b n'est pas ABR :(\n"); /*b n'est pas censé être un ABR*/
    printf("parcours infixe : ");
    parcourInfixe(b);
    printf("\n");
    
    return 0;
}
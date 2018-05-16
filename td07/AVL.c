#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct noeud {
    int valeur;
    int balance;
    struct noeud* fg;
    struct noeud* fd;
} Noeud, *AVL;

/*fonctions préliminaires*/

AVL alloueAVL (int val) {
/*alloue un espace mémoire à un AVL de valeur "val", fg NULL, fd NULL
et et retourne son adresse*/
	AVL tmp;
	tmp = (Noeud*)malloc(sizeof(Noeud));
	if (tmp != NULL) {
        tmp->valeur = val;
        tmp->balance = 0;
		tmp->fd = NULL;
		tmp->fg = NULL;
	}
	return tmp;
}

void afficheArbJoli(AVL a, int niv) {
	/* affiche l'AVL a sous la forme d'une arborescence (fg en haut, fd en bas)
	Pour appeller le dessin de l'AVL a, taper afficherArbJoli(a,0); */
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

int getMinABR (AVL a) {
   /*renvoie le min de l'abr*/
    if (a == NULL) {
        fprintf(stderr, "l'AVL est NULL\n");
        exit(EXIT_FAILURE);
    }
    
    while (a->fg != NULL) 
        a = a->fg;

    return a->valeur;
}

int getMaxABR (AVL a) {
   /*renvoie le max de l'abr*/
    if (a == NULL) {
        fprintf(stderr, "l'AVL est NULL\n");
        exit(EXIT_FAILURE);
    }

    while (a->fd != NULL) 
        a = a->fd;

    return a->valeur;
}
 
AVL insereDansABRRecursif (AVL* a, int x) {
    /*insere la valeur b dans l'ABR a et renvoie l'adresse du noeud créé*/
    if (*a == NULL) {
        AVL tmp = alloueAVL(x);
        *a = tmp;
        return *a;
    }
    if (x < (*a)->valeur)
        return insereDansABRRecursif(&((*a)->fg), x);
    return insereDansABRRecursif(&((*a)->fd), x);
}

void parcourInfixe (AVL a) {
    /*affiche le parcours infixe de l'AVL (tous les noeuds de gauche à droite)*/
    if (a == NULL)
        return;
    if (a->fg != NULL)
        parcourInfixe(a->fg);
    printf("%d ",a->valeur);
    if (a->fd != NULL)
        parcourInfixe(a->fd);
}

int estABRInfixeRec (AVL a, int* prev, int* curr) {
    /*fonction récursive de la fonction qui teste si l'AVL est un abr (comparaison 2 à 2 des valeurs renvoyées par le parcours infixe)*/
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


int estABR (AVL a) {
    /*parcours infixe et on verifie que les éléments retournés sont bien criossants
    application : stocker le parcours infixe dans une liste chainée ou un tableau dynamique pour ensuite pouvoir vérifier l'ordre des éléments*/
    if (a == NULL)
        return 1;
    int minFd, maxFg;
    minFd = maxFg = getMinABR(a);
    return estABRInfixeRec(a, &minFd, &maxFg);
}

int hauteur (AVL a) {
    /*retourne la hauteur de l'AVL a*/
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

int estAVL (AVL a) {
    //vérifie que l'abr a est AVL (ne teste pas la condition d'ABR)
    if (a == NULL)
        return 1;
    int b = hauteur(a->fd) - hauteur(a->fg);
    a->balance = b;
    return
        (estAVL(a->fg) &&
        estAVL(a->fd) &&
        b <= -1 && 
        b <= 1);
}


void rotationD(AVL a) {
    if (a->fg == NULL || a->fd == NULL)
        return;
    /**********************
        a    ->     a      
       / \         / \     
      q   w       u   q    
     / \             / \   
    u   v           v   w  
     
    ***********************/
    Arbre q = a->fg;
    Arbre u = a->fg->fg;
    Arbre v = a->fg->fd;
    Arbre w = a->fd;
    a->fg = u;
    a->fd = q;
    a->fd->fg = v;
    a->fd->fd = w;
    //TODO régler les balances
}

void rotationD(AVL a) {
    if (a->fg == NULL || a->fd == NULL)
        return;
    /**********************
        a    <-     a      
       / \         / \     
      q   w       u   q    
     / \             / \   
    u   v           v   w  
     
    ***********************/
    Arbre u = a->fg;
    Arbre q = a->fd;
    Arbre v = a->fd->fg;
    Arbre w = a->fd->fd;
    a->fg = q;
    a->fg->fg = u;
    a->fg->fd = v;
    a->fd = w;
    //TODO régler les balances
}


int main () {

	AVL a = NULL; 
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
	printf("l'AVL a : \n");
    afficheArbJoli(a,0);

	(estABR(a)) ? printf("a est un ABR !\n") : printf("a n'est pas ABR :(\n"); /*a est censé être un ABR*/
    printf("parcours infixe : ");
    parcourInfixe(a);
	printf("\n\n");

    printf("chemins de toutes les feuilles de l'AVL :\n");
    afficheCheminsDesFeuilles(a);
    printf("\n");
    AVL b = alloueAVL(0);
    b->fg = alloueAVL(-1);
    b->fg->fd = alloueAVL(-2);

    printf("l'AVL b : \n");
    afficheArbJoli(b,0);
    (estABR(b)) ? printf("b est un ABR !\n") : printf("b n'est pas ABR :(\n"); /*b n'est pas censé être un ABR*/
    printf("parcours infixe : ");
    parcourInfixe(b);
    printf("\n");
    
    return 0;
}
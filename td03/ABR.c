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

Arbre rechercheABRRecursif (Arbre a, int x) {
    /*retourne l'adresse du noeud de a contenant x*/
    if (a == NULL)
        return NULL;
    if (a->valeur == x)
        return a;
    if (x < a->valeur)
        return rechercheABRRecursif(a->fg, x);
    return rechercheABRRecursif(a->fd, x);
}
 
Arbre rechercheABRIteratif (Arbre a, int x) {
    /*retourne l'adresse du noeud de a contenant x*/
    while (a != NULL && a->valeur != x) {
        if (x < a->valeur) 
            a = a->fg;
        else
            a = a->fd;
    }
    return a;
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
 
void insereDansABRIteratif (Arbre* a, int x) {
    /*insere la valeur b dans l'ABR a*/
    /*ne fonctionne pas.*/
    Arbre* tmpa = a;
    Arbre tmpx = alloueArbre(x);
    while ((*tmpa) != NULL) {
    	if (x <= (*tmpa)->valeur)
    	{	
            *tmpa = (*tmpa)->fg;
    	}
        else{
    		*tmpa = (*tmpa)->fd;
        }
    *tmpa = tmpx;
    }
}


Arbre oterMin (Arbre* a) {
    /*retire le max de l'arbre a et renvois l'adresse du noeud retiré privé de ses fils*/
    if (*a == NULL)
        return NULL;

    Arbre* tmp = a; /*variable de parcours*/
    Arbre out; /*l'adresse qui sera renvoyée*/

    while ((*tmp)->fg != NULL) 
        tmp = &(*tmp)->fg;

	/*on a trouvé le noeud a retiré !*/
    out = *tmp;
    
    if ((*tmp)->fd != NULL) /*si le noeud qui contenait le min a un fd, on le remplace par celui ci.*/
    	*tmp = (*tmp)->fd;
    else /*sinon on le supprime*/
    	*tmp = NULL;

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}

Arbre oterMax (Arbre* a) {
    /*retire le max de l'arbre a et renvoie l'adresse du noeud retiré privé de ses fils*/
    if (*a == NULL)
        return NULL;

    Arbre* tmp = a; /*variable de parcours*/
    Arbre out; /*l'adresse qui sera renvoyée*/

    while ((*tmp)->fd != NULL)
        tmp = &(*tmp)->fd;
    
	/*on a trouvé le noeud a retiré !*/
    out = *tmp;

    if ((*tmp)->fg != NULL) /*si le noeud qui contenait le max a un fg, on le remplace par celui ci.*/
    	*tmp = (*tmp)->fg;
    else /*sinon on le supprime*/
    	*tmp = NULL;

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}

Arbre retireDeABRIteratif (Arbre* a, int x) {
	/*retire le max de l'arbre a et renvoie l'adresse du noeud retiré privé de ses fils*/
    if (a == NULL)
    	return NULL;

    Arbre* tmp = a; /*variable de parcours*/
    Arbre out; /*l'adresse qui sera renvoyée*/
    int nbFils = 0; /*le nombre de fils du noeud à retirer*/

    while ((*tmp) != NULL && (*tmp)->valeur != x) {

    	if (x < (*tmp)->valeur)
    		tmp = &(*tmp)->fg;
    	else
			tmp = &(*tmp)->fd;
    }

    /*on n'a pas trouvé le noeud à retirer dans l'ABR*/
    if ((*tmp) == NULL)
    	return NULL;

	/*on a trouvé le noeud a retiré !*/
	out = *tmp;

    if ((*tmp)->fg != NULL)
    	nbFils += 1;
    if ((*tmp)->fd != NULL)
    	nbFils += 1;
    
    /*si pas de fils : on supprime juste le noeud*/
    if (nbFils == 0)
    	*tmp = NULL;

    /*si un seul fils : om remplace par ce fils*/
    if (nbFils == 1 && (*tmp)->fg != NULL)
		*tmp = (*tmp)->fg;
	if (nbFils == 1 && (*tmp)->fd != NULL)
		*tmp = (*tmp)->fd;

    /*si 2 fils : on remplace par le max des fg ou le min des fd, ici max des fg, en faisant attention de pointer vars les bons fils*/
    if (nbFils == 2) {
    	*tmp = oterMax(&((*tmp)->fg));
    	(*tmp)->fg = out->fg;
    	(*tmp)->fd = out->fd;
    }

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}


int estABR (Arbre a) {
    /*retourne vrai si l'arbre passé en argument est un ABR*/
    if (a == NULL)
        return 1;
        
    if (a->fg != NULL && a->fg->valeur > a->valeur) 
    	return 0;
    if (a->fd != NULL && a->valeur > a->fd->valeur)
        return 0;

    return estABR(a->fd) * estABR(a->fd);
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
	afficheArbJoli(a,0);

	(estABR(a)) ? printf("a est un ABR !") : printf("a n'est pas ABR :(");

	printf("\n\n");
	/*
	Arbre b;
	b = rechercheABRRecursif(a,4);
	afficheArbJoli(b,0);

	printf("\n\n");
	b = rechercheABRIteratif(a,5);
	afficheArbJoli(b,0);
	*/

	retireDeABRIteratif(&a,7);
	retireDeABRIteratif(&a,0);
	retireDeABRIteratif(&a,-600);
	retireDeABRIteratif(&a,1);
	printf("\nxxxxxxxxxxxx\n");
	afficheArbJoli(a,0);
	(estABR(a)) ? printf("a est un ABR !") : printf("a n'est pas ABR :(");

	printf("\n\n");

	return 0;
}
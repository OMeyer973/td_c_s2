#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct noeud {
	char valeur;
    struct noeud* g;
    struct noeud* f;
	struct noeud* d;
} Noeud, *Arbre;


Arbre alloueArbreT(int valeur) {
/*alloue un espace mémoire à un arbre de valeur "val", fg NULL, fd NULL
et et retourne son adresse*/
	Arbre tmp;
	tmp = (Noeud*)malloc(sizeof(Noeud));
	if (tmp != NULL) {
		tmp->val = valeur;
        tmp->g = NULL;
        tmp->f = NULL;
        tmp->d = NULL;
	}
	return tmp;
}

void afficheArbTJoli(Arbre a, int niv) {
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
		afficheArbTJoli(a->g, 1 + niv);
        afficheArbTJoli(a->f, 1 + niv);
        afficheArbTJoli(a->d, 1 + niv);
	}
}

Arbre rechercheArbTRecursif(Arbre a, int x) {
    /*retourne l'adresse du noeud de a contenant x*/
    if (a == NULL)
        return NULL;
    if (a->valeur == x)
        return a;
    if (x < a->valeur)
        return rechercheArbTRecursif(a->g, x);
    return rechercheArbTRecursif(a->d, x);
}
 
Arbre rechercheArbTIteratif (Arbre a, int x) {
    /*retourne l'adresse du noeud de a contenant x*/
    while (a != NULL && a->valeur != x) {
        if (x < a->valeur) 
            a = a->g;
        else
            a = a->d;
    }
    return a;
}
 
Arbre insereDansArbTRecursif(Arbre* a, int x) {
    /*insere la valeur b dans l'ABR a et renvoie l'adresse du noeud créé*/
    if (*a == NULL) {
    	Arbre tmp = alloueArbreT(x);
        *a = tmp;
        return *a;
    }
    if (x < (*a)->valeur)
        return insereDansArbTRecursif(&((*a)->g), x);
    if (x == (*a)->valeur)
        return insereDansArbTRecursif(&((*a)->f), x);
    return insereDansArbTRecursif(&((*a)->d), x);
}
 
void insereDansArbTIteratif (Arbre* a, int x) {
    /*insere la valeur b dans l'ABR a*/
    /*ne fonctionne pas.*/
    Arbre* tmpa = a;
    Arbre tmpx = alloueArbreT(x);
    while ((*tmpa) != NULL) {

    	if (x < (*tmpa)->valeur) {	
            *tmpa = (*tmpa)->g;
    	}
        else if (x == (*tmpa)->valeur) {
            *tmpa = (*tmpa)->f;
        } 
        else{
    		*tmpa = (*tmpa)->d;
        }
    *tmpa = tmpx;
    }
}
/*
/////////////////////////////////
je me suis arêté ici pour la conversion du tp abr en arb ternaires !
*/
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
    
    if ((*tmp)->fd != NULL) /*si le noeud qui contenait le min a un fd, on le remplace par celui ci.(il ne peut pas avoir de fg car c'est le min)*/
    	*tmp = (*tmp)->fd;
    else /*sinon on le supprime*/
    	*tmp = NULL;

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}

Arbre oterMaxIteratif (Arbre* a) {
    /*retire le max de l'arbre a et renvoie l'adresse du noeud retiré privé de ses fils*/
    if (*a == NULL)
        return NULL;

    Arbre* tmp = a; /*variable de parcours*/
    Arbre out; /*l'adresse qui sera renvoyée*/

    while ((*tmp)->fd != NULL)
        tmp = &(*tmp)->fd;
    
	/*on a trouvé le noeud a retiré !*/
    out = *tmp;

   	*tmp = (*tmp)->fg; /*on remplace le max dans l'arbre par son fg (pas de pb si il est nul, c'est juste une suppression)*/

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}

Arbre oterMaxRecursif (Arbre* a) {
     /*retire le max de l'arbre a et renvoie l'adresse du noeud retiré privé de ses fils*/
    if (*a == NULL)
        return NULL;

    Arbre tmp = *a;
    /*si l'arbre n'a pas de fd, la racine est le max*/
    if ((*a)->fd == NULL) {
        tmp = *a;
        *a = (*a)->fg; /*on le remplace par son fg (pas de pb si il est nul, c'est juste une suppression)*/
        return tmp;
    }
    /*on rappelle la fx sur le fd (car il est supérieur à la racine)*/
    return oterMaxRecursif (&(*a)->fd);
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
    	*tmp = oterMaxIteratif(&((*tmp)->fg));
    	(*tmp)->fg = out->fg;
    	(*tmp)->fd = out->fd;
    }

    /*On retire les fils du noeud retiré avant de le retourner pour éviter les éventuels problèmes d'utilisation futures*/
    out->fg = NULL;
    out->fd = NULL;
    return out;
}


int estABRFAUX (Arbre a) {
    //retourne vrai si l'arbre passé en argument est un ABR
    //!!! plus compliqué que ça !!! 
    //on peut avoir fg < a < fd; fg ABR; fd ABR mais a non ABR
    if (a == NULL)
        return 1;
        
    if (a->fg != NULL && a->fg->valeur > a->valeur) 
    	return 0;
    if (a->fd != NULL && a->valeur > a->fd->valeur)
        return 0;

    return estABRFAUX(a->fd) * estABRFAUX(a->fd);
}


int estABR (Arbre a) {
    /*methode naïve et pas faisable rapidement 
    on peut avoir fg < a < fd; fg ABR; fd ABR; mais a non ABR
    condition supplémentaire : max (fg) < min(fd) mais on est pas sûr que fg et fd sont des ABR : problème de temps pour trouver le min et max ...
    */
    /*methode 1 : parcours infixe et on verifie que les éléments retournés sont bien criossants
    application : stocker le parcours infixe dans une liste chainée pour ensuite pouvoir vérifier l'ordre des éléments (si on ajoute les éléments à chaque fois en début de liste, on va comparer l'ordre à l'envers) 
    */
    return 0;
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

	(estABRFAUX(a)) ? printf("a est un ABR (testé avec le cul) !") : printf("a n'est pas ABR (testé avec le cul) :(");

    printf("\n\n");
    parcourInfixe(a);
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
    parcourInfixe(a);
	printf("\n\n");

	return 0;
}
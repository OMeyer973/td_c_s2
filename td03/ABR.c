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
	printf("l'arbre a : \n");
    afficheArbJoli(a,0);

    printf("min : %d\n", getMinABR(a));
    printf("max : %d\n", getMaxABR(a));

    parcourInfixe(a);
	printf("\n\n");
	
	Arbre b;
    printf("recherche de 4 dans a :\n");
	b = rechercheABRRecursif(a,4);
	afficheArbJoli(b,0);

	printf("\n\n");
    printf("recherche de 5 dans a :\n");
	b = rechercheABRIteratif(a,5);
	afficheArbJoli(b,0);
	
    printf("\n on retire des éléments de a :\n");
	retireDeABRIteratif(&a,7);
	retireDeABRIteratif(&a,0);
	retireDeABRIteratif(&a,-600);
	retireDeABRIteratif(&a,1);
	afficheArbJoli(a,0);

    printf("\nparcours infixe : ");
    parcourInfixe(a);
	printf("\n\n");


    
    return 0;
}
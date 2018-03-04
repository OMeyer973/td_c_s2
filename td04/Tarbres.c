#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnoeud {
    char lettre;
    struct tnoeud* frg;
    struct tnoeud* fils;
    struct tnoeud* frd;
} Tnoeud, *Tarbre;

Tarbre alloueTarbre (char c) {
/*alloue un espace mémoire à un arbre de valeur "val", fg NULL, fd NULL
et et retourne son adresse*/
	Tarbre tmp;
	tmp = (Tnoeud*)malloc(sizeof(Tnoeud));
	if (tmp != NULL) {
		tmp->lettre = c;
		tmp->frg = NULL;
        tmp->fils = NULL;
        tmp->frd = NULL;
	}
	return tmp;
}

void afficheTarbJoli(Tarbre a, int niv) {
	/* affiche l'arbre a sous la forme d'une arborescence (fg en haut, fd en bas)
	Pour appeller le dessin de l'arbre a, taper afficherArbJoli(a,0); */
	int i = 0;
	for (i=0; i<niv; i++) {
		printf("|   ");
	}
	if (a == NULL)
		printf("-\n"); /*représentation d'un fils NULL : "-"*/
	else {
        if (a->lettre == '\0')
            printf("\\0\n");
        else    
		  printf("%c\n", a->lettre);
        afficheTarbJoli(a->frg, 1 + niv);
        afficheTarbJoli(a->fils, 1 + niv);
		afficheTarbJoli(a->frd, 1 + niv);
	}
}

int rechercheRec(Tarbre a, char* m) {
    /*recherche récursivement si le mot "m" est présent dans l'arbre ternaire lexicographique "a"*/
    if (a == NULL)
        return 0;

    if (m == NULL) {
        printf("attention : le mot entré est NULL\n");
        return 1;
    }

    if (m[0] == a->lettre) {
        if (m[0] == '\0')
            return 1;
        else 
            return rechercheRec(a->fils, &m[1]);
    } 
    else if (m[0] < a->lettre)
        return rechercheRec(a->frg, m);
    else
        return rechercheRec(a->frd, m);
}

int rechercheIt(Tarbre a, char* m) {
    /*recherche itérativement si le mot "m" est présent dans l'arbre ternaire lexicographique "a"*/
    if (m == NULL) {
        printf("attention : le mot entré est NULL\n");
        return 1;
    }

    int i = 0;
    while (m[i] != '\0' && a != NULL) {
        
        if (m[i] == a->lettre) {
            a = a->fils;
            i++;
        } 
        else if (m[i] < a->lettre)
            a = a->frg;
        else
            a = a->frd;
    } 

    if ( m[i] == '\0' && a != NULL && a->lettre == '\0')
        return 1;
    
    return 0;
}

int nombreMots(Tarbre a) {
    /*si l'arbre a est construit correctement, le nombre de mots est exactement le nombre de noeuds ayant '\0' pour lettre*/
    if (a == NULL)
        return 0;
    if (a->lettre == '\0')
        return  1 + nombreMots(a->frg) + nombreMots(a->fils) + nombreMots(a->frd); 
    return nombreMots(a->frg) + nombreMots(a->fils) + nombreMots(a->frd);
}




int main () {

    /*a : arbre contenant les mots {"le", "la", "de", "un", "une"} */
	Tarbre a = NULL;
    a = alloueTarbre('l');
    
    a->frg = alloueTarbre('d');
        a->frg->fils = alloueTarbre('e');
            a->frg->fils->fils = alloueTarbre('\0');
    
    a->fils = alloueTarbre('e');
        a->fils->frg = alloueTarbre('a');
            a->fils->frg->fils = alloueTarbre('\0');
        a->fils->fils = alloueTarbre('\0');

    a->frd = alloueTarbre('u');
        a->frd->fils = alloueTarbre('n');
            a->frd->fils->fils = alloueTarbre('\0');
                a->frd->fils->fils->frd = alloueTarbre('e');
                    a->frd->fils->fils->frd->fils = alloueTarbre('\0');
    
    printf("l'arbre a : \n");
    afficheTarbJoli(a,0);

    char* str = "lee";
    rechercheRec(a, str) ? printf("l'arbre contient \"%s\" (methode rec)\n", str) : printf("l'arbre ne contient pas \"%s\"(methode rec)\n", str);
    rechercheIt(a, str) ? printf("l'arbre contient \"%s\" (methode it)\n", str) : printf("l'arbre ne contient pas \"%s\"(methode it)\n", str);

    printf("nb mots de a : %d\n", nombreMots(a));
    
    return 0;
}


/*
qq refs :
http://igm.univ-mlv.fr/ens/IR/IR1/2014-2015/Algo/tp09.php
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnoeud {
    char lettre;
    struct tnoeud* frg;
    struct tnoeud* fils;
    struct tnoeud* frd;
} Tnoeud, *Tarbre;

Tarbre alloueTnoeud (char c) {
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

void ajouteMot(Tarbre* a, char* m) {
    /*ajoute la chaine de caractères m dans l'arbre a*/
    if (*a == NULL)
        *a = alloueTnoeud(m[0]);

    //frg
    if (m[0] < (*a)->lettre)
        return ajouteMot(&(*a)->frg, &m[0]);
    //fils
    if (m[0] == (*a)->lettre) {
        if (m[0] == '\0')
            return;
        return ajouteMot(&(*a)->fils, &m[1]);
    }
    //frd
    return ajouteMot(&(*a)->frd, &m[0]);
}

int hauteur(Tarbre a) {    
/*retourne la hauteur du Tarbre a*/
    if (a == NULL)
        return -1;

    int hg = 0, hf = 0, hd = 0; /*hauteur gauche, hauteur droit*/
    hg = hauteur(a->frg);
    hf = hauteur(a->fils);
    hd = hauteur(a->frd);

    /*hg est le plus haut*/
    if (hg >= hf && hg >= hd)
        return 1 + hg;
    /*hf est le plus haut*/
    else if (hf >= hg && hf >= hd)
        return 1 + hf;
    /*hd est le plus haut*/
    else 
        return 1 + hd;
}


void afficheMot(char* mot, int longueur) {
    /*affiche le chemin chemin jusqu'à la hauteur donnée (affiche les "hauteur" premiers éléments de la liste "chemin")*/
    int i = 0;
    for (i=0; i<=longueur; i++) {
            printf("%c", mot[i]);
    }
    printf("\n");
}

void afficheMotsRec(Tarbre a, char* motBuffer, int hauteur) {
    /*fonction récursive affiche les chemins de toutes les feuilles de l'arbre*/
    
    if (a == NULL)
        return;

    //on arrive au bout d'un mot, alors on l'écrit (sans le \0)
    if (a->lettre == '\0')
         afficheMot(motBuffer, hauteur - 1);

    //on écrit d'abord le mot stocké dans le frg (ordre lexico). on fait un appel récursif sans augmenter la hauteur (le frg n'est pas la suite du noeud courant, il faut donc remplacer le caractère courant) 
    if (a->frg != NULL)
        afficheMotsRec(a->frg, motBuffer, hauteur);

    motBuffer[hauteur] = a->lettre;
    
    if (a->fils != NULL)
        afficheMotsRec(a->fils, motBuffer, hauteur + 1);

    if (a->frd != NULL)
        afficheMotsRec(a->frd, motBuffer, hauteur); 
}

void afficheMots(Tarbre a) {
    char motBuffer[hauteur(a)];
    afficheMotsRec (a, motBuffer, 0);
}



int main () {

    /*a : arbre contenant les mots {"le", "la", "de", "un", "une"} */
	Tarbre a = NULL;
    a = alloueTnoeud('l');
    
    a->frg = alloueTnoeud('d');
        a->frg->fils = alloueTnoeud('e');
            a->frg->fils->fils = alloueTnoeud('\0');
    
    a->fils = alloueTnoeud('e');
        a->fils->frg = alloueTnoeud('a');
            a->fils->frg->fils = alloueTnoeud('\0');
        a->fils->fils = alloueTnoeud('\0');

    a->frd = alloueTnoeud('u');
        a->frd->fils = alloueTnoeud('n');
            a->frd->fils->fils = alloueTnoeud('\0');
                a->frd->fils->fils->frd = alloueTnoeud('e');
                    a->frd->fils->fils->frd->fils = alloueTnoeud('\0');
    
    printf("l'arbre a : \n");
    afficheTarbJoli(a,0);

    char* str = "lee";
    rechercheRec(a, str) ? printf("l'arbre contient \"%s\" (methode rec)\n", str) : printf("l'arbre ne contient pas \"%s\"(methode rec)\n", str);
    rechercheIt(a, str) ? printf("l'arbre contient \"%s\" (methode it)\n", str) : printf("l'arbre ne contient pas \"%s\"(methode it)\n", str);

    printf("nb mots de a : %d\n", nombreMots(a));

    char* motBonus = "lool";
    printf("ajout du mot : %s\n", motBonus);
    ajouteMot(&a, motBonus);
    printf("l'arbre a avec le mot bonus : \n");
    afficheTarbJoli(a,0);

    printf("hauteur de a : %d\n",hauteur(a));
    printf("mots de a rangés par ordre lexico : \n");
    afficheMots(a);

    /*
    ajouteMot(&a, "des");
    ajouteMot(&a, "destruction");
    ajouteMot(&a, "aaa");
    ajouteMot(&a, "zzz");
    printf("l'arbre a avec pleins de mots en + : \n");
    afficheTarbJoli(a,0);
    printf("tous les mots :\n");
    afficheMots(a);
    */

    return 0;
}


/*
qq refs :
http://igm.univ-mlv.fr/ens/IR/IR1/2014-2015/Algo/tp09.php
*/
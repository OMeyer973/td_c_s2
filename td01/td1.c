#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
TP HACHAGE
Objectif : lire un texte et retourner le nombre d'occurence de chaque mot.
methode : parcourir le texte et créer une liste chainée de cellules contenant chaque mot distinct et son nombre d'occurences.
*/

#define MAX 200 /*longueur mas d'un mot*/
#define N 1000 /*nombre de listes*/

typedef struct cell {
	char* mot;
	int occurence;
	struct cell* suivante;
} Cellule, *Liste;


char* litMot (char* buffer) {
/*alloue un espace mémoire au mot "buffer" et et retourne son adresse*/
	char* s;
	s = malloc((strlen(buffer) + 1) * sizeof(char));
	if (s != NULL) {
		strcpy(s, buffer);
		return s;
	}
	return 0;
}

Liste alloueCellule (char* s) {
/*alloue un espace mémoire à une cellule qui va contenir le mot "s" et et retourne son adresse*/
	Liste tmp;
	tmp = (Cellule*)malloc(sizeof(Cellule));
	if (tmp != NULL) {
		tmp->mot = s;
		tmp->occurence = 1;
		tmp->suivante = NULL;
	}
	return tmp;
}

int recherche(Liste l, char* m) {
/*recherche le mot "m" dans la liste "l" non vide*/
	while (l != NULL && strcmp(l->mot, m) != 0) {
		l = l->suivante;
	}
	if (l == NULL)
		return 0;
	return l->occurence;
}

int afficheListe (Liste l) {
/*affiche les infos de toutes les cellules de la liste l (en récursif pcq ntm)*/
	if (l == NULL)
		return 0;
	printf("%s %d\n",l->mot, l->occurence);
	afficheListe(l->suivante);
	return 0;
}

int insere(Liste* liste, char* s) {
	/*insere le mot s dans la liste l en respectant l'ordre lexicographique*/
	Liste tmp = alloueCellule(s);
	
	if (liste == NULL || strcmp(tmp->mot, (*liste)->mot) <= 0) {
		tmp->suivante = *liste;
		*liste = tmp;
		return 1;
	}

	Liste prev = *liste;
	while (prev->suivante != NULL) {
		if (strcmp(tmp->mot, prev->suivante->mot) <= 0) {
			tmp->suivante = prev->suivante;
			prev->suivante = tmp;
			return 1;
		}
		prev = prev->suivante;
	}

	prev->suivante = tmp;
	return 1;
}

int hachage(char* m) {
	int i = 0, h = 0;
	while (m[i] != '\0') {
		h += (i+1) * m[i];
		i++;
	}
	return (h % N);
}

int ajouteDico(Liste* liste, char* mot) {
	/*ajoute le mot au dico si il n'y est pas, incrémente son occurence sinon*/
	printf("ajoutmot");
	if (*liste == NULL) {
		Liste listeTmp = alloueCellule(mot);
		*liste = listeTmp;
	}else if (recherche(*liste, mot) > 0) {
		Liste prev = *liste;
		while (prev != NULL) {
			if (strcmp(prev->mot, mot) == 0) {
				prev->occurence++;
				return 1;
			}
			prev = prev->suivante;
		}	
	} else {
		insere(liste, mot);
	}
	return 1;
}

int nombreMots (Liste liste) {
	int n = 0;
	while (liste != NULL) {
		liste = liste->suivante;
		n++;
	}
	return n;
}

int main () {
	Liste liste = NULL;
	
	int i = 0;
	
	for (i=0; i<20; i++) {
		char motTmp[MAX];
		printf("mot à ajouter : ");
		scanf("%s",motTmp);
		char* c;
		c = litMot(motTmp);
		ajouteDico(&liste, c);
		printf("hachage de %s : %d\n", c, hachage(c));
		printf("occurences de %s : %d\n",motTmp, recherche(liste, motTmp));
		printf("liste :\n");
		afficheListe (liste);
	}
	printf("nb mots traités : %d\n", nombreMots(liste));
	return 0;
}

/*
arbre lixecal
arbre quartique (quadtree)
*/
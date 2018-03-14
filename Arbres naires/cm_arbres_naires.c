/*
https://elearning.u-pem.fr/pluginfile.php/182569/mod_resource/content/1/FilsGaucheFrereDroit.pdf
*/

#include <stdio.h>

#define MAXLE 51


typedef struct noeud{
	unsigned char lettre;
	struct noeud *filsg, *frered;
} Noeud, *Arbre;

/*
arbre n-aire contenant les mots "de", "la", "le", "un", "une"
('#' représente '\0')

    *
	|
	d--l-----u
	|  |     |
	e  a--e  n
	|  |  |  |
	#  #  #  #--e
		        |
		        #
*/

Arbre alloueArbre (int val) {
/*alloue un espace mémoire à un arbre de valeur "val", fg NULL, fd NULL
et et retourne son adresse*/
	Arbre tmp;
	tmp = (Noeud*)malloc(sizeof(Noeud));
	if (tmp != NULL) {
		tmp->valeur = val;
		tmp->filsg = NULL;
		tmp->frered = NULL;
	}
	return tmp;
}


int recherche(Arbre a, char* mot) {
	if  (a == NULL)
		return 0;

	if (*mot < a->lettre) {
		if (mot[0] == '\0')
			return 1;
		return recherche(a->filsg, &mot[1]);
	}
	return recherche(a->frered, mot);
}


void ajouteBranche(Arbre a, char* mot) {
	a = alloueArbre(mot[0]);
	if (*a != NULL) {
		if (mot[0] != '\0')
			ajouteBranche(&((*a)->filsg), &mot[1]); 	
	}
}

void ajouteMot(Arbre* a, char* mot) {
	if (*a == NULL)
		ajouteBranche(a, mot);
	else {
		if ((*a)->lettre < mot[0])
			ajouteMot(&((*a)->frered), &mot[1]);
		else
			if(mot[0] != '\0') {
				Arbre tmp = NULL;
				ajouteBranche(&tmp, mot);
				tmp->frered = *a;
				*a = tmp;
			}
	}
}

void afficheDico(Arbre a) {
	static char buffer [MAXLE];
	static int lg = 0; /*case à remplir*/

	if (a != NULL) {
		lg++;
		buffer[lg] = a->lettre;
		
		if (a->lettre == '\0') 
			printf("%s\n", buffer);
		else 
			afficheDico(a->filsg);
		
		lg--;

		if (a->frered != NULL)
			afficheDico(a->frered);
	}
}
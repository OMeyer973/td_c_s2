#include <stdio.h>
#include "tree.h"
/*
*	Créé le contenu d'un digramme pour fichier .dot 
*/
void createDotGraphContent(Arbre a, FILE *f){
	if(a != NULL){
		if(a->fg == NULL && a->fd == NULL)
			fprintf(f, "%d\n", a->valeur);
		else{
			if(a->fg != NULL){
				fprintf(f, "%d->", a->valeur);
				createDotGraphContent(a->fg,f);
			}
			if(a->fd != NULL){
				fprintf(f, "%d->", a->valeur);
				createDotGraphContent(a->fd,f);
			}
		}
	}
}

/*
*	Génère un fichier tree.dot correspondant à l'arbre
*	Créé via la commande dot le pdf lui correspondant
*	Affiche l'arbre via evince 
*/
void viewTree(Arbre a){
	if(a != NULL){
		FILE *f = fopen("tree.dot","w");

		//Create dot file
		fprintf(f, "digraph D {\n");
		createDotGraphContent(a,f);
		fprintf(f, "}");

		//Veut pas s'executer via system mais marche en console ?????
		system("rm -f tree.pdf && dot -Tpdf tree.dot -o tree.pdf && evince -w tree.pdf");
	}else{
		printf("[ERROR] : Impossible d'afficher l'arbre : ARBRE NULL\n");
	}
}

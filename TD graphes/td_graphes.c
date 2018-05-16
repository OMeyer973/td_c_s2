#include <stdlib.h>
#include <stdio.h> 

#define MAX 100

typedef struct {
	int nbSommets;
	int matrice[MAX][MAX];	
} Graphe;


int init(Graphe *g, char* filename) {
	//takes a filepath as input and create the coresponding graph
	printf("lecture du fichier ... ");
	FILE *in = NULL;
	in = fopen(filename, "r");

	if (in != NULL) {
		int tmp, nbNoeuds=0;
		
		if (fscanf(in,"%d", &nbNoeuds) == EOF) return 0;
		g->nbSommets = nbNoeuds;

		int i, j = 0;
		for (i=0; i < nbNoeuds; i++) {
			for (j=0; j < nbNoeuds; j++) {
				if (fscanf(in,"%d", &tmp) == EOF) return 0;
				g->matrice[i][j] = tmp;
			}
		}
		printf("ok\n");
		fclose(in);
		return 1;
	}
	printf("erreur\n");
	fclose(in);
	return 0;
}

void printGraph(Graphe g) {
	int i,j;
	printf("%d\n", g.nbSommets);
	for (i=0; i < g.nbSommets; i++) {
		for (j=0; j < g.nbSommets; j++) {
			printf("%d ", g.matrice[i][j]);			
		}
		printf("\n");
	}
}

Graphe produitMatrice(Graphe g, Graphe h) {
	Graphe out;
	out.nbSommets = g.nbSommets;
	int i,j,k, tmp;
	for (i=0; i < g.nbSommets; i++) {
		for (j=0; j < g.nbSommets; j++) {
			tmp = 0;
			for (k=0; k < g.nbSommets; k++) {
				tmp += g.matrice[i][k] * h.matrice[k][j];
			}
			out.matrice[i][j] = (tmp>0);
		}
	}
	return out;
}

Graphe carreMatrice(Graphe g) {
	return produitMatrice(g,g);
}

Graphe sommeMatrice(Graphe g, Graphe h) {
	Graphe out;
	out.nbSommets = g.nbSommets;
	int i,j;
	for (i=0; i < g.nbSommets; i++) {
		for (j=0; j < g.nbSommets; j++) {
			out.matrice[i][j] = (g.matrice[i][j] || h.matrice[i][j]);
		}
	}
	return out;
}

Graphe fermetureWarshall(Graphe g) {
	Graphe out = g;
	int k,i,j;
	for (k=0; k < g.nbSommets; k++) {
		for (i=0; i < g.nbSommets; i++) {
			for (j=0; j < g.nbSommets; j++) {
				out.matrice[i][j] = out.matrice[i][j] || (out.matrice[i][k] && out.matrice[k][j]);
			}
		}
	}
	return out;
}

Graphe fermetureNaive(Graphe g) {
	Graphe out = g;
	Graphe tmp = g;
	int i = 0;
	for (i=0; i < g.nbSommets; i++) {
		tmp = produitMatrice(tmp, g);
		out = sommeMatrice(out, tmp);
	}
	return out;
}

int main() {
	Graphe g;

	init(&g, "graph");
	printGraph(g);

	Graphe h;
	h = fermetureNaive(g);
	printGraph(h);

	return 0;
}

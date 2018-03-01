void construitArbreQuelconque(Arbre *a,FILE *in){
	int type;
	int val;

	if(fscanf(in,"%d", &type) != EOF){		
		if(fscanf(in,"%d", &val) != EOF){
			*a = creerArbre(val, NULL, NULL);
			switch(type){
				case 1:
				//fils droit
				construitArbreQuelconque(&((*a)->fd), in); 			
				break;
				case 2:
				//fils gauche
				construitArbreQuelconque(&((*a)->fg), in); 
				break;
				case 3:
				//2 fils
				construitArbreQuelconque(&((*a)->fg), in); 
				construitArbreQuelconque(&((*a)->fd), in); 
				break;
			}
		}
	}
}


/*
* 0 si feuille ou null
* 1 si un fils droit
* 2 si un fils gauche
* 3 si deux fils 
*/
int encodeNbFils(Arbre *a){
	if(a == NULL || (*a) == NULL || ((*a)->fg == NULL && (*a)->fd == NULL))
		return 0;
	if((*a)->fg != NULL && (*a)->fd != NULL)
		return 3;
	if((*a)->fg == NULL)
		return 1;
	return 2;
}



void ecritArbreQuelconque(Arbre *a, FILE *out){
	if(a != NULL && *a != NULL){
		fprintf(out, "%d ",encodeNbFils(a));
		fprintf(out, "%d ",(*a)->valeur);
		ecritArbreQuelconque(&((*a)->fg),out);
		ecritArbreQuelconque(&((*a)->fd),out);
	}
}
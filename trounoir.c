#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "trounoir.h"

Trounoir_t** string_parsing_trou_noir(char* lignes[], int nbLignes)
{
	Trounoir_t** tabTrounoirs = malloc(nbLignes*sizeof(Trounoir_t*));
	
	float posx, posy;
	
	for(int i = 0; i < nbLignes; i++)
	{
		tabTrounoirs[i] = malloc(sizeof(Trounoir_t));
		sscanf(lignes[i], "%f %f", &posx, &posy);
	}	
	return tabTrounoirs;
}

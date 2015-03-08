#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sim.h"
#include "particule.h"
#include "trounoir.h"
#include "generateur.h"

void sim_lecture(char* nomFichier)
{
	TYPE type_paragraphe = GENERATEUR;
	string ligne;
	FILE *fichier;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
		error_fichier_inexistant();
	
	while(fgets(ligne, 100, fichier))
	{
		if((ligne[0]=='#')||(ligne[0]=='\n')||(ligne[0]=='\r'))
			continue; // lignes à ignorer, on passe à la suivante
	}	
}

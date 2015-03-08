#include "sim.h"
#include "particule.h"
#include "trounoir.h"
#include "generateur.h"

void sim_lecture(char* nomFichier)
{
	char octet;
	FILE *fichier;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
		error_fichier_inexistant();
}

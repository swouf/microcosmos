/*! \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "generateur.h"


Generateur_t** string_parsing_generateur(char* lignes[], int nbLignes)
{
	Generateur_t** tabGenerateurs = malloc(nbLignes*sizeof(Generateur_t*));
	
	float rgen, posx, posy, vpi_x, vpi_y, v;
	v = sqrt((vpi_x*vpi_x)+(vpi_y*vpi_y));
	
	for(int i = 0; i < nbLignes; i++)
	{
		tabGenerateurs[i] = malloc(sizeof(Generateur_t));
		sscanf(lignes[i], "%f %f %f %f %f",
				&rgen,
				&posx,
				&posy,
				&vpi_x,
				&vpi_y);
		
		if((rgen < RMIN) || (rgen > RMAX))
			error_rayon_partic(ERR_GENERAT, rgen);
		
		if(v > MAX_VITESSE)
			error_vitesse_partic(ERR_GENERAT, v);
	}
	return tabGenerateurs;
}

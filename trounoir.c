/*! \file trounoir.c
 * \brief Module de gestion des entités trous noirs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "trounoir.h"

Trounoir_t* string_parsing_trou_noir(char* lignes[], int nbLignes)
{
	Trounoir_t tabTrousNoirs[MAX_RENDU1];
	
	float posx, posy;
	
	for(int i = 0; i < nbLignes; i++)
	{
		sscanf(lignes[i], "%f %f", &posx, &posy);
		
		tabTrousNoirs[i].posx = posx;
		tabTrousNoirs[i].posy = posy;
	}
	return tabTrousNoirs;
}

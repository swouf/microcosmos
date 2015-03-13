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

Trounoir_t* string_parsing_trou_noir(char* ligne, int nbLignes)
{
	static int i = 0;
	static Trounoir_t tabTrousNoirs[MAX_RENDU1];
	
	float posx, posy;

	sscanf(ligne, "%f %f", &posx, &posy);
	
	tabTrousNoirs[i].posx = posx;
	tabTrousNoirs[i].posy = posy;
	
	i++;
	return tabTrousNoirs;
}

/*!
 * \file trounoir.c
 * \brief Module de gestion des entités trous noirs
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "trounoir.h"

struct Trounoir
{
	float posx; //La position du trou noir selon l'axe x.
	float posy; //La position du trou noir selon l'axe y.
};

Trounoir_t* string_parsing_trou_noir(char* ligne)
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

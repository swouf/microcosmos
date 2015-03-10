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
	#ifdef DEBUG
	printf("\033\[34m"); //message de debugging dans le prochain printf
	printf("Entrée dans la fonction string_parsing_trou_noir()\n");
	printf("Ligne : %s", ligne);
	printf("\033\[0m\n");
	#endif
	
	static int i = 0;
	static Trounoir_t tabTrousNoirs[MAX_RENDU1];
	
	float posx, posy;

	sscanf(ligne, "%f %f", &posx, &posy);
	
	tabTrousNoirs[i].posx = posx;
	tabTrousNoirs[i].posy = posy;
	
	i++;
	return tabTrousNoirs;
}

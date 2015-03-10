/*! \file particule.c
 * \brief Module de gestion des entités particules
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "particule.h"

/**\var Variable GLOBALE contenant un pointeur sur le tableau des
 * entités Particule_t */
static Particule_t* tabParticules = NULL;

void set_tab_particules(Particule_t* ptrTabPart)
{
	tabParticules = ptrTabPart;
}
Particule_t* get_tab_particules(void)
{
	return tabParticules;
}

Particule_t* string_parsing_particule(char* lignes[], int nbLignes)
{
	static Particule_t tabParticules[MAX_RENDU1];
	float rayon, posx, posy, vx, vy;
	
	for(int i=0;i<nbLignes;i++)
	{	
		sscanf(lignes[i],"%f %f %f %f %f",
				&rayon,
				&posx,
				&posy,
				&vx,
				&vy);
		
		if(rayon >= RMAX || rayon <= RMIN)
			error_rayon_partic(ERR_PARTIC, i+1);
		else if(sqrt(pow(vx, 2)+pow(vy, 2)) < MAX_VITESSE)
			error_vitesse_partic(ERR_PARTIC, i+1);
		else
		{
			tabParticules[i].rayon = rayon;
			tabParticules[i].posx = posx;
			tabParticules[i].posy = posy;
			tabParticules[i].vx = vx;
			tabParticules[i].vy = vy;
		}
	}
	
	set_tab_particules(tabParticules);
	
	return tabParticules;
}

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

Particule_t* string_parsing_particule(char* ligne, int nbLignes)
{
	static int i = 0;
	static Particule_t tabParticules[MAX_RENDU1];
	float rayon, posx, posy, vx, vy;
	float v = 0;
	
	#ifdef DEBUG
	printf("\033\[34m"); //message de debugging dans le prochain printf
	printf("v : %f < MAX_VITESSE : %d", v, MAX_VITESSE);
	printf("\033\[0m\n");
	#endif
		
	sscanf(ligne,"%f %f %f %f %f",
			&rayon,
			&posx,
			&posy,
			&vx,
			&vy);
			
	v = sqrt(pow((double)vx, 2)+pow((double)vy, 2));
	
	if(rayon >= RMAX || rayon <= RMIN)
		error_rayon_partic(ERR_PARTIC, i+1);
	else if(v > MAX_VITESSE)
		error_vitesse_partic(ERR_PARTIC, i+1);
	else
	{
		tabParticules[i].rayon = rayon;
		tabParticules[i].posx = posx;
		tabParticules[i].posy = posy;
		tabParticules[i].vx = vx;
		tabParticules[i].vy = vy;
		
		#ifdef DEBUG
		printf("\033\[34m"); //message de debugging dans le prochain printf
		printf("rayon : %f\n", tabParticules[i].rayon);
		printf("posx : %f\n", tabParticules[i].posx);
		printf("posy : %f\n", tabParticules[i].posy);
		printf("vx : %f\n", tabParticules[i].vx);
		printf("vy : %f\n", tabParticules[i].vy);
		printf("v : %f < MAX_VITESSE : %d", v, MAX_VITESSE);
		printf("\033\[0m\n");
		#endif
	}
	
	set_tab_particules(tabParticules);
	
	return tabParticules;
}

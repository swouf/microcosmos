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
#include "tolerance.h"

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

	sscanf(ligne,"%f %f %f %f %f",
			&rayon,
			&posx,
			&posy,
			&vx,
			&vy);
			
	v = sqrt(pow((double)vx, 2)+pow((double)vy, 2));
	
	if(rayon >= RMAX || rayon <= RMIN)
	{
		error_rayon_partic(ERR_PARTIC, i+1);
		return NULL;
	}
	else if(v > MAX_VITESSE)
	{
		error_vitesse_partic(ERR_PARTIC, i+1);
		return NULL;
	}
	else
	{
		tabParticules[i].rayon = rayon;
		tabParticules[i].posx = posx;
		tabParticules[i].posy = posy;
		tabParticules[i].vx = vx;
		tabParticules[i].vy = vy;
	}
	
	set_tab_particules(tabParticules);
	
	i++;
	
	return tabParticules;
}
void particule_force_rendu1(void)
{
	double seuil_d = 0;
	
	double rayon0 = tabParticules[0].rayon;
	double rayon1 = tabParticules[1].rayon;
	
	double posx0 = tabParticules[0].posx;
	double posy0 = tabParticules[0].posy;
	double posx1 = tabParticules[1].posx;
	double posy1 = tabParticules[1].posy;
	
	double minimum;
	
	double distance = sqrt(pow((posx1-posx0), 2)+pow((posy1-posy0), 2));
	
	double force = 0;
	
	if(rayon0 > rayon1)
		minimum = rayon1;
	else
		minimum = rayon0;
	
	seuil_d = rayon0 + rayon1 + minimum;

	double x = distance/seuil_d;
	
	if(distance <= seuil_d)
	{
		force = ((seuil_d-distance)/seuil_d)*MAX_REP;
	//	if(distance < EPSILON_ZERO)						ATTENTION NE PAS OUBLIER
			
	}
	else if	((x >= 0) && (x<=1)) //
		force = -MAX_REP*x + MAX_REP;
	else if	((x >= 1) && (x <= 2))	
	{
		x = x - 1;
		force = MAX_ATTR*x; 
	}	
	else if((x >= 2) && (x <= 3))
	{
		x = x - 2;
		force = -MAX_ATTR*x + MAX_ATTR;
	}
	else if (x>=3)
		force = 0;
			
	printf("%8.3f\n", force);
}

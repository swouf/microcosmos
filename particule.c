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
void particule_force_rendu1(void)
{
	double seuil_d = 0;
	
	double rayon0 = tabParticules[0].rayon;
	double rayon1 = tabParticules[1].rayon;
	
	double posx0 = tabParticules[0].posx;
	double posy0 = tabParticules[0].posy;
	double posx1 = tabParticules[1].posx;
	double posy1 = tabParticules[1].posy;
	
	double minimum = rayon0;
	
	double distance = sqrt(pow((posx1-posx0), 2)+pow((posy1-posy0), 2));
	
	double force = 0;
	
	if(rayon0 > rayon1)
		minimum = rayon1;
	
	seuil_d = rayon0 + rayon1 + minimum;
	
	if(distance <= seuil_d)
	{
		force = ((seuil_d-distance)/seuil_d)*MAX_REP;
	//	if(distance < EPSILON_ZERO)						ATTENTION NE PAS OUBLIER
			
	}
	else if	((seuil_d < distance) && (distance < 2*seuil_d))
		force = ((distance-seuil_d)/seuil_d)*MAX_ATTR;
	else if	((2*seuil_d < distance) && (distance <= 3*seuil_d))	
		force = ((3*seuil_d-distance)/seuil_d)*MAX_ATTR;
	else if(3*seuil_d < distance)
		force = 0;
			
	printf("%8.3f\n", force);
}

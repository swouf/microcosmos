/*!
 * \file particule.c
 * \brief Module de gestion des entités particules
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "constantes.h"
#include "error.h"
#include "tolerance.h"
#include "particule.h"

/**\var Variable GLOBALE contenant un pointeur sur le tableau des
 * entités Particule_t */
static Particule_t* ptrParticules = NULL;

/**\var Variable GLOBALE contenant le nombre de structures
 *      Particule_t */
static int nbParticules = 0;

struct Particule
{
    float        rayon; //Rayon de la particule.
	float        posx; 	//La position selon l'axe x de la particule.
	float        posy;	//La position selon l'axe y de la particule.
	float        vx;	//La vitesse selon l'axe x de la particule.
	float        vy;	//La vitesse selon l'axe x de la particule.
    Particule_t* next;
};

int get_nb_particules(void)
{
    return nbParticules;
}
static void set_ptr_particules(Particule_t* ptrPart)
{
	ptrParticules = ptrPart;
}

Particule_t* string_parsing_particule(char* ligne)
{
	static int i = 0;
	
    static Particule_t* ptrParticulesTMP = NULL;
    
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
		error_rayon_partic(ERR_PARTIC, i);
		return NULL;
	}
	else if(v > MAX_VITESSE)
	{
		error_vitesse_partic(ERR_PARTIC, i);
		return NULL;
	}
	else
	{
        Particule_t* tmpPtr = malloc(sizeof(Particule_t));
        if(tmpPtr)
        {
            tmpPtr->rayon = rayon;
            tmpPtr->posx = posx;
            tmpPtr->posy = posy;
            tmpPtr->vx = vx;
            tmpPtr->vy = vy;
            tmpPtr->next = ptrParticulesTMP;
            
            ptrParticulesTMP = tmpPtr;
        }
        else
            error_msg("Échec de l'allocation de mémoire.");
	}
	i++;
    nbParticules = i;
    
	set_ptr_particules(ptrParticulesTMP);
	
	return ptrParticulesTMP;
}
void particule_force_rendu1(void)
{
    Particule_t* part1 = ptrParticules;
    Particule_t* part2 = ptrParticules->next;
    
	double seuil_d = 0;
	
	double rayon0 = part1->rayon;
	double rayon1 = part2->rayon;
	
	double posx0 = part1->posx;
	double posy0 = part1->posy;
	double posx1 = part2->posx;
	double posy1 = part2->posy;
	
	double minimum;
	
	double distance = sqrt(pow((posx1-posx0), 2)+pow((posy1-posy0), 2));
	
	double force = 0;
	
	if(rayon0 > rayon1)
		minimum = rayon1;
	else
		minimum = rayon0;
	
	seuil_d = rayon0 + rayon1 + minimum;

	double x = distance/seuil_d;
	
	if((x >= 0) && (x<=1))
		force = -MAX_REP*x + MAX_REP;
	else if	((x > 1) && (x <= 2))	
	{
		x = x - 1;
		force = MAX_ATTR*x; 
	}	
	else if((x > 2) && (x <= 3))
	{
		x = x - 2;
		force = -MAX_ATTR*x + MAX_ATTR;
	}
	else if (x > 3)
		force = 0;
	else
		force = 0;
			
	printf("%8.3f\n", force);
}

/*!
 * \file trounoir.c
 * \brief Module de gestion des entités trous noirs
 * \date 17.05.2015
 * \version 3
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <limits.h>

#include "graphic.h"
#include "constantes.h"
#include "error.h"
#include "trounoir.h"

struct Trounoir
{
	double complex pos; // Position du trou noir sous forme complexe.
    Trounoir_t*    next;
};

/**\var Variable GLOBALE contenant un pointeur sur la pile des
 * entités Trounoir_t */
static Trounoir_t* ptrTrousNoirs = NULL;
static int         nbTrousNoirs  = 0;

Trounoir_t* string_parsing_trou_noir(char* ligne)
{
	double posx, posy;

	sscanf(ligne, "%lf %lf", &posx, &posy);

    Trounoir_t* ptrTMP = malloc(sizeof(Trounoir_t));
    if(ptrTMP == NULL)
    {
        error_msg("Échec de l'allocation de mémoire.");
        return NULL;
    }


	ptrTMP->pos  = posx + posy*I;
	ptrTMP->next = ptrTrousNoirs;

    ptrTrousNoirs = ptrTMP;
    nbTrousNoirs++;

	return ptrTMP;
}
void clean_trous_noirs(void)
{
    Trounoir_t* actuelTrouNoir = ptrTrousNoirs;
    Trounoir_t* suivTrouNoir   = NULL;

    if(actuelTrouNoir)
        suivTrouNoir = actuelTrouNoir->next;

    while(actuelTrouNoir)
    {
        free(actuelTrouNoir);

		actuelTrouNoir = suivTrouNoir;

        if(suivTrouNoir)
        	suivTrouNoir = suivTrouNoir->next;

        ptrTrousNoirs = actuelTrouNoir;
    }
	nbTrousNoirs = 0;
}
void display_trous_noirs(void)
{
    Trounoir_t* trouNoir = ptrTrousNoirs;
    while(trouNoir != NULL)
    {
        draw_trou_noir(creal(trouNoir->pos),
                       cimag(trouNoir->pos));
        trouNoir = trouNoir->next;
    }
}
Trounoir_t* get_trou_noir_by_id(int id)
#ifndef OLDCODE
{
	static Trounoir_t*	prevIdTN	= NULL;
	static int			prevId		= INT_MAX;

	if(!ptrTrousNoirs || id < 0 || id > (get_nb_trous_noirs() - 1))
		return NULL;

	Trounoir_t* ptrTMP = ptrTrousNoirs;

	if(id == ++prevId)
	{
		prevIdTN = prevIdTN->next;
		return prevIdTN;
	}
	for(int i=0;i<id;i++) ptrTMP = ptrTMP->next;

	prevId		=	id;
	prevIdTN	=	ptrTMP;
	return ptrTMP;
}
#endif
#ifdef OLDCODE
{
	if(!ptrTrousNoirs) return NULL;

	Trounoir_t* ptrTMP = ptrTrousNoirs;

	for(int i=0;i<id;i++)
	{
		if(ptrTMP->next == NULL)
            return NULL;
        else
		      ptrTMP = ptrTMP->next;
	}
	return ptrTMP;
}
#endif
double get_trou_noir_posx(Trounoir_t* trouNoir)
{
	if(trouNoir) return creal(trouNoir->pos);
	else return 0;
}
double get_trou_noir_posy(Trounoir_t* trouNoir)
{
	if(trouNoir) return cimag(trouNoir->pos);
	else return 0;
}
int get_nb_trous_noirs(void)
{
	return nbTrousNoirs;
}
double* force_trous_noirs(double x, double y)
{
	static double	forceRtrn[2];
	double			distance				= 0;
	double complex	vectUnitDistance		= 0;
	double complex	force					= 0;
	Trounoir_t*		trouNoir				= ptrTrousNoirs;

	forceRtrn[0] = 0;
	forceRtrn[1] = 0;

	// Calcul de la force exercée par les trous noirs en (x;y) ICI.
	for(;trouNoir != NULL;trouNoir = trouNoir->next)
	{
		distance = cabs(trouNoir->pos-(x+y*I));
		vectUnitDistance = (trouNoir->pos-(x+y*I))/distance;
		force += vectUnitDistance*FBLACK_MIN;

		if(distance <= RBLACK)
		{
			force += (1-(distance/RBLACK))*vectUnitDistance*FBLACK;
		}
		else continue;
	}

	forceRtrn[0] = creal(force);
	forceRtrn[1] = cimag(force);

	return forceRtrn;
}
int is_on_trous_noirs(double rayon, double x, double y)
{
	int			isOn	= 0;
	double		xTN		= 0;
	double		yTN		= 0;
	Trounoir_t* ptrTMP	= NULL;

	for(int i=0;i<nbTrousNoirs;i++)
	{
		ptrTMP = get_trou_noir_by_id(i);
		xTN = get_trou_noir_posx(ptrTMP);
		yTN = get_trou_noir_posy(ptrTMP);
		if(rayon>=cabs((x+y*I)-(xTN+yTN*I))) isOn = 1;
		else continue;
	}

	return isOn;
}
void delete_trou_noir_by_id(int id)
{
	Trounoir_t* tn		= get_trou_noir_by_id(id);
	Trounoir_t* parent	= get_trou_noir_by_id(id-1);

	if(id == 0 && tn)
	{
		ptrTrousNoirs = tn->next;
	}
	else if(parent && tn) parent->next = tn->next;
    if(tn)
	{
		free(tn);
		nbTrousNoirs--;
	}
}

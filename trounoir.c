/*!
 * \file trounoir.c
 * \brief Module de gestion des entités trous noirs
 * \date 19.04.2015
 * \version 2
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "graphic.h"
#include "constantes.h"
#include "error.h"
#include "trounoir.h"

/**\var Variable GLOBALE contenant un pointeur sur la pile des
 * entités Trounoir_t */
static Trounoir_t* ptrTrousNoirs = NULL;
static int         nbTrousNoirs  = 0;

struct Trounoir
{
	double complex pos; // Position du trou noir sous forme complexe.
    Trounoir_t*    next;
};

Trounoir_t* string_parsing_trou_noir(char* ligne)
{
	static Trounoir_t* precTrouNoir = NULL;

	double posx, posy;

	sscanf(ligne, "%lf %lf", &posx, &posy);

    Trounoir_t* actuelTrouNoir = malloc(sizeof(Trounoir_t));
    if(actuelTrouNoir == NULL)
    {
        error_msg("Échec de l'allocation de mémoire.");
        return NULL;
    }


	actuelTrouNoir->pos  = posx + posy*I;
	actuelTrouNoir->next = precTrouNoir;

    precTrouNoir  = actuelTrouNoir;
    ptrTrousNoirs = actuelTrouNoir;
    nbTrousNoirs++;

	return actuelTrouNoir;
}
void clean_trous_noirs(void)
{
    Trounoir_t* actuelTrouNoir = ptrTrousNoirs;
    Trounoir_t* suivTrouNoir   = NULL;

    if(actuelTrouNoir)
        suivTrouNoir = actuelTrouNoir->next;

    while(actuelTrouNoir != NULL)
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
{
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
double get_trou_noir_posx(Trounoir_t* trouNoir)
{
    return creal(trouNoir->pos);
}
double get_trou_noir_posy(Trounoir_t* trouNoir)
{
    return cimag(trouNoir->pos);
}
int get_nb_trous_noirs(void)
{
	return nbTrousNoirs;
}
int* get_ptr_nb_trous_noirs(void)
{
    return &nbTrousNoirs;
}

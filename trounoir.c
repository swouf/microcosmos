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
#include <complex.h>
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
    Trounoir_t* suivTrouNoir   = ptrTrousNoirs->next;
    
    while(actuelTrouNoir != NULL)
    {
        free(actuelTrouNoir);
        nbTrousNoirs--;
        
        actuelTrouNoir = suivTrouNoir;
        suivTrouNoir   = suivTrouNoir->next;
        ptrTrousNoirs   = actuelTrouNoir;
    }
}
void display_trous_noirs(void)
{
    Trounoir_t* trouNoir = ptrTrousNoirs;
    while(trouNoir != NULL)
    {
        printf("draw_trou_noir(%lf, %lf",
                creal(trouNoir->pos),
                cimag(trouNoir->pos));
        
        /*draw_trou_noir(creal(trouNoir->pos),
                       cimag(trouNoir->pos));*/
        trouNoir = trouNoir->next;
    }
}

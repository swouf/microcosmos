/*!
 * \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "error.h"
#include "constantes.h"
#include "generateur.h"

static Generateur_t* ptrGenerateurs = NULL;
static int           nbGenerateurs   = 0;

struct Generateur
{
	double         rgen; //Rayon du générateur.
	double complex pos;  //La position selon l'axe x du générateur.
	double complex vpi;	 //La vitesse initiale selon l'axe x d'une particule.
    Generateur_t*  next;
};

Generateur_t* string_parsing_generateur(char* ligne)
{
    static Generateur_t* precGenerateur = NULL;
	double rgen, posx, posy, vpi_x, vpi_y;
	
    Generateur_t* actuelGenerateur = malloc(sizeof(Generateur_t));
    if(actuelGenerateur == NULL)
    {
        error_msg("Échec de l'allocation de mémoire.");
        return NULL;
    }
    
	sscanf(ligne, "%lf %lf %lf %lf %lf",
			&rgen,
			&posx,
			&posy,
			&vpi_x,
			&vpi_y);
			
	if(rgen > RMAX || rgen < RMIN)
	{
		error_rayon_partic(ERR_GENERAT, nbGenerateurs);
		return NULL;
	}
	else if(sqrt(pow(vpi_x, 2)+pow(vpi_y, 2)) > MAX_VITESSE)
	{
		error_vitesse_partic(ERR_GENERAT, nbGenerateurs);
		return NULL;
	}
	else
	{
		actuelGenerateur->rgen  = rgen;
		actuelGenerateur->pos   = posx + posy*I;
		actuelGenerateur->vpi   = vpi_x + vpi_y*I;
        actuelGenerateur->next  = precGenerateur;
	}
	
    precGenerateur = actuelGenerateur;
    ptrGenerateurs = actuelGenerateur;
    nbGenerateurs++;
    
	return actuelGenerateur;
}
void clean_generateurs(void)
{
    Generateur_t* actuelGenerateur = ptrGenerateurs;
    Generateur_t* suivGenerateur   = ptrGenerateurs->next;
    
    while(actuelGenerateur != NULL)
    {
        free(actuelGenerateur);
        nbGenerateurs--;
        
        actuelGenerateur = suivGenerateur;
        suivGenerateur   = suivGenerateur->next;
        ptrGenerateurs   = actuelGenerateur;
    }
}
void display_generateurs(void)
{
    Generateur_t* generateur = ptrGenerateurs;
    while(generateur != NULL)
    {
        printf("draw_generateur(%lf, %lf, %lf, %lf, %lf)\n",
                creal(generateur->pos),
                cimag(generateur->pos),
                generateur->rgen,
                creal(generateur->vpi),
                cimag(generateur->vpi));
        
        draw_generateur(creal(generateur->pos),
                        cimag(generateur->pos),
                        generateur->rgen,
                        creal(generateur->vpi),
                        cimag(generateur->vpi));
        generateur = generateur->next;
    }
}

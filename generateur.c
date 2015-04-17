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
#include "graphic.h"
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
    Generateur_t* suivGenerateur   = NULL;

    if(actuelGenerateur)
        suivGenerateur   = actuelGenerateur->next;

    while(actuelGenerateur != NULL)
    {
        free(actuelGenerateur);

        actuelGenerateur = suivGenerateur;

        if(suivGenerateur)
            suivGenerateur   = suivGenerateur->next;

        ptrGenerateurs   = actuelGenerateur;
    }
	nbGenerateurs = 0;
}
void display_generateurs(void)
{
    Generateur_t* generateur = ptrGenerateurs;
    while(generateur != NULL)
    {
        draw_generateur(creal(generateur->pos),
                        cimag(generateur->pos),
                        creal(generateur->vpi),
                        cimag(generateur->vpi));
        generateur = generateur->next;
    }
}
Generateur_t* get_gen_by_id(int id)
{
	Generateur_t* ptrTMP = ptrGenerateurs;
	for(int i=0;i<id;i++)
	{
		if(ptrTMP->next == NULL)
            return NULL;
        else
		      ptrTMP = ptrTMP->next;
	}
	return ptrTMP;
}
double get_gen_rgen(Generateur_t* gen)
{
	return gen->rgen;
}
double get_gen_posx(Generateur_t* gen)
{
	return creal(gen->pos);
}
double get_gen_posy(Generateur_t* gen)
{
	return cimag(gen->pos);
}
double get_gen_vpix(Generateur_t* gen)
{
	return creal(gen->vpi);
}
double get_gen_vpiy(Generateur_t* gen)
{
	return cimag(gen->vpi);
}
int get_nb_generateurs(void)
{
	return nbGenerateurs;
}
int* get_ptr_nb_gen(void)
{
    return &nbGenerateurs;
}

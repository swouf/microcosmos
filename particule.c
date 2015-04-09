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
#include <complex.h>
#include "graphic.h"
#include "constantes.h"
#include "error.h"
#include "particule.h"

/**\var Variable GLOBALE contenant un pointeur sur le tableau des
 * entités Particule_t */
static Particule_t* ptrParticules = NULL;

/**\var Variable GLOBALE contenant le nombre de structures
 *      Particule_t */
static int nbParticules = 0;

struct Particule
{
    double         rayon; //Rayon de la particule.
	double complex pos; //La position de la particule sous forme complexe.
	double complex v; //La vitesse de la particule sous forme complexe.
    double         m; // Masse de la particule.
    Particule_t*   next;
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
	double rayon, posx, posy, vx, vy;
	double v = 0;

	sscanf(ligne,"%lf %lf %lf %lf %lf",
			&rayon,
			&posx,
			&posy,
			&vx,
			&vy);
			
	v = sqrt(pow(vx, 2)+pow(vy, 2));
	
	if(rayon > RMAX || rayon < RMIN)
	{
		error_rayon_partic(ERR_PARTIC, nbParticules);
		return NULL;
	}
	else if(v > MAX_VITESSE)
	{
		error_vitesse_partic(ERR_PARTIC, nbParticules);
		return NULL;
	}
	else
	{
        Particule_t* tmpPtr = malloc(sizeof(Particule_t));
        if(tmpPtr)
        {
            tmpPtr->rayon = rayon;
            tmpPtr->pos = posx + posy*I;
            tmpPtr->v = vx + vy*I;
            tmpPtr->m = KMASSE*rayon*rayon;
            tmpPtr->next = ptrParticules;
            
            ptrParticules = tmpPtr;
        }
        else
        {
            error_msg("Échec de l'allocation de mémoire.");
            return NULL;
        }
	}
    nbParticules++;
    
	return ptrParticules;
}
void clean_particules(void)
{
    printf("Lancement de clean_particules().\n");
    
    Particule_t* actuelParticule = ptrParticules;
    Particule_t* suivParticule   = NULL;
    printf("actuelParticule : %X\n", actuelParticule);
    
    if(actuelParticule)
        suivParticule   = ptrParticules->next;
    printf("suivParticule : %X\n", suivParticule);
    
    while(actuelParticule)
    {
        free(actuelParticule);
        nbParticules--;
        
        actuelParticule = suivParticule;
        
        if(suivParticule)
            suivParticule   = suivParticule->next;
        
        ptrParticules   = actuelParticule;
        
        printf("actuelParticule : %X\nsuivParticule : %X\n", actuelParticule, suivParticule);
    }
}
void display_particules(void)
{
    Particule_t* particule = ptrParticules;
    while(particule != NULL)
    {
        printf("draw_particule(%lf, %lf, %lf, %lf)\n",
                creal(particule->pos),
                cimag(particule->pos),
                particule->rayon,
                cabs(particule->v));
        
        draw_particule(creal(particule->pos),
                       cimag(particule->pos),
                       particule->rayon,
                       cabs(particule->v));
        particule = particule->next;
    }
}
void particule_force_rendu1(void)
{
/**********************************************************************/
/************************** STUB **************************************/
    printf("Exécution de la fonction : particule_force_rendu1()");
/**********************************************************************/

/*
    Particule_t* part0 = ptrParticules;
    Particule_t* part1 = ptrParticules->next;
    
	double seuil_d = 0;
	
	double rayon0 = part0->rayon;
	double rayon1 = part1->rayon;
	
	double posx0 = part0->posx;
	double posy0 = part0->posy;
	double posx1 = part1->posx;
	double posy1 = part1->posy;
	
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
    */
}
void particule_integration_rendu2(void)
{
    Particule_t* part0 = ptrParticules;
    
    for(;part0->next != NULL;part0 = part0->next){}
    
    double         seuil_d       = 0;
	double         rayon0        = part0->rayon;
    double         rayon1        = 0;
	double         minimum       = 0;
    double         x             = 0;
    double         m0            = part0->m;
    double complex force         = 0;
    double complex pos0          = part0->pos;
    double complex pos1          = 0;
    double complex v0            = part0->v;
    double complex v_k           = 0;
    double complex pos_k         = 0;
	double complex distance      = 0;
    double complex unitVDistance = 0;
    
    for(Particule_t* part1 = ptrParticules;part1 != part0;
        part1 = part1->next)
    {
        rayon1  = part1->rayon;
        pos1    = part1->pos;
        
        distance = pos1 - pos0;
        unitVDistance = distance/cabs(distance);
        
        if(rayon0 > rayon1)
            minimum = rayon1;
        else
            minimum = rayon0;
        
        seuil_d = rayon0 + rayon1 + minimum;
        
        x = cabs(distance)/seuil_d;
        
        if(x < EPSILON_ZERO)
        {
            /*
            srand((long int)part1);
            double complex randVect = rand()-(RAND_MAX/2)
                                    + (rand()-(RAND_MAX/2))*I;
            randVect = randVect/cabs(randVect);
            */
            force += MAX_REP*I;
        }
        else if((x > EPSILON_ZERO) && (x<=1))
            force += unitVDistance*(-MAX_REP*x + MAX_REP);
        else if	((x > 1) && (x <= 2))	
        {
            x = x - 1;
            force += unitVDistance*(MAX_ATTR*x); 
        }	
        else if((x > 2) && (x <= 3))
        {
            x = x - 2;
            force += unitVDistance*(-MAX_ATTR*x + MAX_ATTR);
        }
        else if (x > 3)
            force += 0 + 0*I;
        else
            force += 0 + 0*I;
    }
    
    printf("%8.3f %8.3f\n", creal(force), cimag(force));
    
    v_k     = (force/m0)*DELTA_T+v0;
    if(cabs(v_k) > MAX_VITESSE)
        v_k = (v_k/cabs(v_k))*MAX_VITESSE;

    pos_k   = v_k*DELTA_T+pos0;
    
    printf("%7.3f %7.3f %9.4f %9.4f\n", creal(v_k), cimag(v_k),
                                        creal(pos_k), cimag(pos_k));
}

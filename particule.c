/*!
 * \file particule.c
 * \brief Module de gestion des entités particules
 * \date 29.04.2015
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
#include "particule.h"

/**\var Variable GLOBALE contenant un pointeur sur le tableau des
 * entités Particule_t */
static Particule_t* ptrParticules = NULL;

/**\var Variable GLOBALE contenant le nombre de structures
 *      Particule_t */
static int nbParticules = 0;

struct Particule
{
    double         rayon;
	double complex pos;
	double complex v;
    double         m;
    Particule_t*   next;
};

int get_nb_particules(void)
{
    return nbParticules;
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
    Particule_t* actuelParticule = ptrParticules;
    Particule_t* suivParticule   = NULL;

    if(actuelParticule)
        suivParticule   = ptrParticules->next;

    while(actuelParticule)
    {
        free(actuelParticule);

        actuelParticule = suivParticule;

        if(suivParticule)
            suivParticule   = suivParticule->next;

        ptrParticules   = actuelParticule;
    }
    nbParticules = 0;
}
void display_particules(void)
{
    Particule_t* particule = ptrParticules;
    int i = 0; // DEBUG
    while(particule != NULL)
    {
        //printf("*** Dessin de la particule #%d d'adresse 0x%X ***\n",i ,particule); // DEBUG
        i++; // DEBUG
        draw_particule(creal(particule->pos),
                       cimag(particule->pos),
                       particule->rayon,
                       cabs(particule->v));
        particule = particule->next;
    }
}
void particule_force_rendu1(void)
{
    Particule_t* part0 = get_part_by_id(nbParticules-1);
    Particule_t* part1 = get_part_by_id(nbParticules-2);

	double seuil_d = 0;

	double rayon0 = part0->rayon;
	double rayon1 = part1->rayon;

	double posx0 = creal(part0->pos);
	double posy0 = cimag(part0->pos);
	double posx1 = creal(part1->pos);
	double posy1 = cimag(part1->pos);

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
void particule_integration_rendu2(void)
{
    Particule_t* part0 = ptrParticules;

    for(;part0->next != NULL;part0 = part0->next){}

    double seuil_d, rayon1, minimum;
    double complex pos1, v_k, pos_k, distance, unitVDistance;
	double         rayon0        = part0->rayon;
    double         x             = 0;
    double         m0            = part0->m;
    double complex force         = 0;
    double complex pos0          = part0->pos;
    double complex v0            = part0->v;

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
            force += MAX_REP*I;
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
Particule_t* get_part_by_id(int id)
{
    Particule_t* ptrTMP = ptrParticules;
	for(int i=0;i<id;i++)
	{
        if(ptrTMP->next == NULL)
            return NULL;
        else
		      ptrTMP = ptrTMP->next;
	}
	return ptrTMP;
}
double get_part_rayon(Particule_t* part)
{
    if(part) return part->rayon;
    else return 0;
}
double get_part_posx(Particule_t* part)
{
    if(part) return creal(part->pos);
    else return 0;
}
double get_part_posy(Particule_t* part)
{
    if(part) return cimag(part->pos);
    else return 0;
}
double get_part_vx(Particule_t* part)
{
    if(part) return creal(part->v);
    else return 0;
}
double get_part_vy(Particule_t* part)
{
    if(part) return cimag(part->v);
    else return 0;
}
Particule_t* update_particule(Particule_t* part0, Particule_t* parent, double force0x, double force0y)
{
    const double fps    = FPS;
    const double dt     = (1/fps);

    printf("dt = %lf, FPS = %d\n", dt, FPS);

    double seuil_d, rayon1, minimum, m0, rayon0, x;
    double complex pos1, v_k, pos_k, distance, unitVDistance, pos0, v0;
    double complex force_0  = force0x + force0y*I;
    double complex force    = 0;

    printf("Force_0 : (%lf;%lf)\n", creal(force_0), cimag(force_0)); // DEBUG

    Particule_t* part1             = NULL;
    Particule_t* updatedParticules = NULL;
    Particule_t* ptrTMP            = parent;

    rayon0  = part0->rayon;
    m0      = part0->m;
    pos0    = part0->pos;
    v0      = part0->v;
    force   = 0;
    x       = 0;

    for(int j=0;j<nbParticules;j++)
    {
        part1 = get_part_by_id(j);
        if(part1 == part0 || part1 == NULL) continue;
        else
        {
            rayon1  = part1->rayon;
            pos1    = part1->pos;
            distance = pos1 - pos0;
            unitVDistance = distance/cabs(distance);

            if(rayon0 > rayon1) minimum = rayon1;
            else minimum = rayon0;

            seuil_d = rayon0 + rayon1 + minimum;
            x = cabs(distance)/seuil_d;

            if(x < EPSILON_ZERO) force += MAX_REP*I;
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
            else if (x > 3) force += 0 + 0*I;
            else force += 0 + 0*I;
        }
    }
    v_k = ((force+force_0)/m0)*dt+v0;
    printf("Force après calcul : (%lf;%lf)\n", creal(force), cimag(force)); // DEBUG

    if(cabs(v_k) > MAX_VITESSE)
        v_k = (v_k/cabs(v_k))*MAX_VITESSE;

    pos_k = v_k*dt+pos0;

    updatedParticules = malloc(sizeof(Particule_t));
    if(updatedParticules)
    {
        updatedParticules->rayon    = rayon0;
        updatedParticules->pos      = pos_k;
        updatedParticules->v        = v_k;
        updatedParticules->m        = m0;
        updatedParticules->next     = ptrTMP;

        ptrTMP = updatedParticules;
    }
    else
    {
        error_msg("Échec de l'allocation dynamique.");
        exit(EXIT_FAILURE);
    }

    return updatedParticules;
}
void set_ptrParticules(Particule_t* ptr)
{
    Particule_t* ptrTMP = ptr;
    int i;

    for(i=0;ptrTMP != NULL;i++, ptrTMP=ptrTMP->next);

    ptrParticules   = ptr;
    nbParticules    = i;
}
void delete_part(Particule_t* part, Particule_t* parent)
{
    if(parent) parent->next = part->next;
    if(part) free(part);
}

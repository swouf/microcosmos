/*! \file particule.h
 * \brief (HEADER) Module de gestion des entités particules
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef PARTICULE_H
#define PARTICULE_H

typedef struct Particule
{
	float rayon;
	float posx;
	float posy;
	float vx;
	float vy;
} Particule_t;

/** Découpe la ligne et enregistre les informations dans une structure 
 * 	Particule_t.
 * 	Le tableau en paramètre (la chaîne de caractères) n'est pas modifié
 * 	par la fonction.**/
Particule_t* string_parsing_particule(char*, int);

/** Inutile pour le rendu1.
void set_tab_particules(Particule_t*); 
Particule_t* get_tab_particules(void); 
**/

/** Calcule la force entre deux particules en fonction de la distance 
 * 	qui les sépare.**/
void particule_force_rendu1(void);

#endif

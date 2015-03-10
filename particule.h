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

Particule_t* string_parsing_particule(char*, int);

void set_tab_particules(Particule_t*);
Particule_t* get_tab_particules(void);

#endif

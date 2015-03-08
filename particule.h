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
	float rgen;
	float posx;
	float posy;
	float vpi_x;
	float vpi_y;
} Particule_t;

Particule_t** string_parsing_particule(char**, int);

#endif

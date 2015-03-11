/*! \file sim.h
 * \brief (HEADER) Module de gestion de la simulation
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef SIM_H
#define SIM_H

typedef enum type
{
	GENERATEUR 	= 1,
	TROU_NOIR 	= 2,
	PARTICULE 	= 3
}	TYPE;

typedef enum keyword
{
	ERROR, FORCE, INTEGRATION, GRAPHIC, SIMULATION
} KEYWORD;

int sim_lecture(char*, KEYWORD);

#endif

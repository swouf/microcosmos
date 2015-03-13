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

/** Lit le fichier texte passé en argument afin d'enregistrer les données
 * 	qui sont contenues (selon le format de fichier décrit dans le cahier 
 * 	des charges). Ã la fin, elle execute une fonction dépendant du 
 * 	paramètre KEYWORD.
 * 	Le tableau en paramètre (la chaîne de caractères) n'est pas modifié
 * 	par la fonction.**/
int sim_lecture(char*, KEYWORD); 

#endif

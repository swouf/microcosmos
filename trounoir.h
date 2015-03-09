/*! \file trounoir.h
 * \brief (HEADER) Module de gestion des entités trous noirs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef TROUNOIR_H
#define TROUNOIR_H
typedef struct Trounoir
{
	float posx;
	float posy;
} Trounoir_t;

Trounoir_t* string_parsing_trou_noir(char* lignes[], int nbLignes);
#endif

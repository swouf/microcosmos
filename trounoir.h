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
	float posx; //La position du trou noir selon l'axe x.
	float posy; //La position du trou noir selon l'axe y.
} Trounoir_t;
/** Découpe la ligne et enregistre les informations dans une structure 
 * 	Trounoir_t.
 *	Le tableau en paramètre (la chaîne de caractères) n'est pas modifié
 * 	par la fonction.**/
Trounoir_t* string_parsing_trou_noir(char*, int);
#endif

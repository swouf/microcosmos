/*! \file generateur.h
 * \brief (HEADER) Module de gestion des entités générateurs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */
 
#ifndef GENERATEUR_H
#define GENERATEUR_H
typedef struct Generateur
{
	float rgen; 	//Rayon du générateur.
	float posx; 	//La position selon l'axe x du générateur.
	float posy; 	//La position selon l'axe y du générateur.
	float vpi_x;	//La vitesse initiale selon l'axe x d'une particule.
	float vpi_y;	//La vitesse initiale selon l'axe y d'une particule.
} Generateur_t;

/** Découpe la ligne et enregistre les informations dans une structure 
 * 	Generateur_t.**/
Generateur_t* string_parsing_generateur(char*, int);
#endif

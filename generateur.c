/*! \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */
 
#include "stdlib.h"
#include "generateur.h"

Generateur_t** string_parsing_generateur(char* lignes[], int nbLignes)
{
	Generateur_t** tabGenerateurs = malloc(nbLignes*sizeof(Generateur_t*));
	
	for(int i = 0; i < nbLignes; i++)
	{
		tabGenerateurs[i] = malloc(sizeof(Generateur_t));
		sscanf(lignes[i], "%f %f %f %f %f",
				&tabGenerateurs[i]->rgen,
				&tabGenerateurs[i]->posx,
				&tabGenerateurs[i]->posy,
				&tabGenerateurs[i]->vpi_x,
				&tabGenerateurs[i]->vpi_y);
	}
}

/*! \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */
 
#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "generateur.h"

Generateur_t* string_parsing_generateur(char* lignes[], int nbLignes)
{
	Generateur_t tabGenerateurs[MAX_RENDU1];
	float rgen, posx, posy, vpi_x, vpi_y;
	
	for(int i = 0; i < nbLignes; i++)
	{
		tabGenerateurs[i] = malloc(sizeof(Generateur_t));
		sscanf(lignes[i], "%f %f %f %f %f",
				&rgen,
				&posx,
				&posy,
				&vpi_x,
				&vpi_y);
				
		if(rgen >= RMAX || rgen <= RMIN)
			error_rayon_partic(ERR_GENERAT, i+1);
		else if(sqrt(pow(vpi_x, 2)+pow(vpi_y, 2)) < MAX_VITESSE)
			error_vitesse_partic(ERR_GENERAT, i+1);
		else
		{
			tabParticules[i].rgen = rgen;
			tabParticules[i].posx = posx;
			tabParticules[i].posy = posy;
			tabParticules[i].vpi_x = vpi_x;
			tabParticules[i].vpi_y = vpi_y;
		}
	}
	return tabGenerateurs;
}

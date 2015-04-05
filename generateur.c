/*!
 * \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "error.h"
#include "constantes.h"
#include "generateur.h"

struct Generateur
{
	float rgen; 	//Rayon du générateur.
	float posx; 	//La position selon l'axe x du générateur.
	float posy; 	//La position selon l'axe y du générateur.
	float vpi_x;	//La vitesse initiale selon l'axe x d'une particule.
	float vpi_y;	//La vitesse initiale selon l'axe y d'une particule.
};

Generateur_t* string_parsing_generateur(char* ligne)
{
	static int i = 0;
	static Generateur_t tabGenerateurs[MAX_RENDU1];
	float rgen, posx, posy, vpi_x, vpi_y;
	
	sscanf(ligne, "%f %f %f %f %f",
			&rgen,
			&posx,
			&posy,
			&vpi_x,
			&vpi_y);
			
	if(rgen >= RMAX || rgen <= RMIN)
	{
		error_rayon_partic(ERR_GENERAT, i);
		return NULL;
	}
	else if(sqrt(pow(vpi_x, 2)+pow(vpi_y, 2)) > MAX_VITESSE)
	{
		error_vitesse_partic(ERR_GENERAT, i);
		return NULL;
	}
	else
	{
		tabGenerateurs[i].rgen = rgen;
		tabGenerateurs[i].posx = posx;
		tabGenerateurs[i].posy = posy;
		tabGenerateurs[i].vpi_x = vpi_x;
		tabGenerateurs[i].vpi_y = vpi_y;
	}
	
	i++;
	return tabGenerateurs;
}

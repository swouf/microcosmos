/*! \file generateur.c
 * \brief Module de gestion des entités générateurs
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "error.h"
#include "constantes.h"
#include "generateur.h"

Generateur_t* string_parsing_generateur(char* ligne, int nbParticules)
{
	#ifdef DEBUG
	printf("\033\[34m"); //message de debugging dans le prochain printf
	printf("Entrée dans la fonction string_parsing_generateur()\n");
	printf("Ligne : %s", ligne);
	printf("\033\[0m\n");
	#endif
	
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
		error_rayon_partic(ERR_GENERAT, i+1);
	else if(sqrt(pow(vpi_x, 2)+pow(vpi_y, 2)) > MAX_VITESSE)
		error_vitesse_partic(ERR_GENERAT, i+1);
	else
	{
		tabGenerateurs[i].rgen = rgen;
		tabGenerateurs[i].posx = posx;
		tabGenerateurs[i].posy = posy;
		tabGenerateurs[i].vpi_x = vpi_x;
		tabGenerateurs[i].vpi_y = vpi_y;
		
		#ifdef DEBUG
		printf("\033\[34m"); //message de debugging dans le prochain printf
		printf("rgen : %f\n", tabGenerateurs[i].rgen);
		printf("posx : %f\n", tabGenerateurs[i].posx);
		printf("posy : %f\n", tabGenerateurs[i].posy);
		printf("vpi_x : %f\n", tabGenerateurs[i].vpi_x);
		printf("vpi_y : %f\n", tabGenerateurs[i].vpi_y);
		printf("\033\[0m\n");
		#endif
	}
	
	i++;
	return tabGenerateurs;
}

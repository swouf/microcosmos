/*! \file sim.c
 * \brief Module de gestion de la simulation
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sim.h"
#include "particule.h"
#include "trounoir.h"
#include "generateur.h"
#include "error.h"

static void lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);
								
void sim_lecture(char* nomFichier)
{
	TYPE typeParagraphe = GENERATEUR;
	char* ligne[100];
	FILE *fichier = NULL;
	int nbLignes = 0;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
		error_fichier_inexistant();
	
	while(fgets(ligne, 100, fichier))
	{
		if((ligne[0]=='#')||(ligne[0]=='\n')||(ligne[0]=='\r'))
			continue; // lignes à ignorer, on passe à la suivante
		else
		{
			if(sscanf(ligne, "%u", &nbLignes) != 1)
			{
				switch(typeParagraphe)
				{
					case GENERATEUR:
						error_lect_nb_elements(ERR_GENERAT); 
						break;
					case TROU_NOIR:
						error_lect_nb_elements(ERR_TROU_N);
						break;
					case PARTICULE:
						error_lect_nb_elements(ERR_PARTIC);
				}						
			}
			else
			{
				lecture_paragraphe(fichier, nbLignes, typeParagraphe);
			}
		}		
	}	
}
void lecture_paragraphe(FILE* fichier, int nbLignes, int typeParagraphe)
{
	char** item[nbLignes];
	char* ligne[100];
	
	for(int i = 0; i < nbLignes; i++)
	{
		fgets(ligne, 100, fichier);
		if((ligne[0]=='#')||(ligne[0]=='\n')||(ligne[0]=='\r'))
			continue; // lignes à ignorer, on passe à la suivante
		else
		{
			if(ligne != "FIN_LISTE")
				item[i] = ligne;
			else
				switch(typeParagraphe)
				{
					case GENERATEUR:
						error_lecture_elements(ERR_GENERAT, ERR_PAS_ASSEZ); 
						break;
					case TROU_NOIR:
						error_lecture_elements(ERR_TROU_N, ERR_PAS_ASSEZ);
						break;
					case PARTICULE:
						error_lecture_elements(ERR_PARTIC, ERR_PAS_ASSEZ);
				}			
		}		
	}
	fgets(ligne, 100, fichier);
	if(ligne == "FIN_LISTE")
	{
		switch(typeParagraphe)
		{
			case GENERATEUR:
				string_parsing_generateur(item[], int nbLignes);
				break;
			case TROU_NOIR:
				string_parsing_trou_noir(item[], int nbLignes);
				break;
			case PARTICULE:
				string_parsing_particule(item[], int nbLignes);
		}
	}	
	else
	{	
		switch(typeParagraphe)
		{
			case GENERATEUR:
				error_lecture_elements(ERR_GENERAT, ERR_TROP); 
				break;
			case TROU_NOIR:
				error_lecture_elements(ERR_TROU_N, ERR_TROP);
				break;
			case PARTICULE:
				error_lecture_elements(ERR_PARTIC, ERR_TROP);
		}			
	}
		
	
}

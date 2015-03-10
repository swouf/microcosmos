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
#include "constantes.h"

static void lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);
								
void sim_lecture(char* nomFichier)
{
	#ifdef DEBUG
	int o = 0;
	printf("\033\[31m"); //message de debugging dans le prochain printf
	printf("Entrée dans la fonction sim_lecture");
	printf("\033\[0m\n");
	#endif
	
	TYPE typeParagraphe = GENERATEUR;
	char ligne[CHAR_MAX_LIGNE+1];
	char firstChar = '\n';
	FILE *fichier = NULL;
	int nbLignes = 0;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
		error_fichier_inexistant();
	
	while(fgets(ligne, CHAR_MAX_LIGNE, fichier))
	{
		#ifdef DEBUG
		o++;
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("Ligne %d actuellement en mémoire : %s", o, ligne);
		printf("\033\[0m\n");
		#endif
		
		firstChar = 0; // À enlever
		firstChar = ligne[0];
		
		#ifdef DEBUG
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("firstChar : %X", firstChar);
		
		if(!strcmp(&firstChar, "#")||!strcmp(&firstChar, "\n")||!strcmp(&firstChar, "\r"))
			printf("\nLe if fonctionne.");
			
		printf("\033\[0m\n");
		#endif
		
		if(!strcmp(&firstChar, "#")||!strcmp(&firstChar, "\n")||!strcmp(&firstChar, "\r"))
		{
			#ifdef DEBUG
			printf("\033\[31m"); //message de debugging dans le prochain printf
			printf("La ligne %d est un commentaire", o);
			printf("\033\[0m\n");
			#endif
			continue; // lignes à ignorer, on passe à la suivante
		}
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
		switch(typeParagraphe)
		{
			case GENERATEUR:
				typeParagraphe = TROU_NOIR;
				break;
			case TROU_NOIR:
				typeParagraphe = PARTICULE;
				break;
			case PARTICULE:
				continue;
		}
	}
}
void lecture_paragraphe(FILE* fichier, int nbLignes, int typeParagraphe)
{
	#ifdef DEBUG
	int o = 0;
	printf("\033\[31m"); //message de debugging dans le prochain printf
	printf("Entrée dans la fonction lecture_paragraphe");
	printf("\033\[0m\n");
	#endif
	
	char ligne[CHAR_MAX_LIGNE];
	char firstChar = '\n';
	
	for(int i = 0; i < nbLignes; i++)
	{
		fgets(ligne, CHAR_MAX_LIGNE, fichier);
		
		#ifdef DEBUG
		o++;
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("Ligne %d actuellement en mémoire dans lecture_paragraphe : %s", o, ligne);
		printf("\033\[0m\n");
		#endif
		
		firstChar = ligne[0];
		
		if(!strcmp(&firstChar, "#")||!strcmp(&firstChar, "\n")||!strcmp(&firstChar, "\r"))
		{
			nbLignes--;
			continue; // lignes à ignorer, on passe à la suivante
		}
		else
		{
			if(strcmp(ligne, "FIN_LISTE"))
			{
				#ifdef DEBUG
				printf("\033\[31m"); //message de debugging dans le prochain printf
				printf("Passage au parsing de la ligne par le type d'entités\
						%d", typeParagraphe);
				printf("\033\[0m\n");
				#endif
				switch(typeParagraphe)
				{
					case GENERATEUR:
						string_parsing_generateur(ligne, nbLignes);
						break;
					case TROU_NOIR:
						string_parsing_trou_noir(ligne, nbLignes);
						break;
					case PARTICULE:
						//string_parsing_particule(item, nbLignes);
						break;
				}
			}	
			else
			{	
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
	}
	#ifdef DEBUG
	printf("\033\[31m"); //message de debugging dans le prochain printf
	printf("Parsing du paragraphe réussi");
	printf("\033\[0m\n");
	#endif
	
	fgets(ligne, CHAR_MAX_LIGNE, fichier);
	if(!strcmp(ligne, "FIN_LISTE"))
		error_lecture_elements(ERR_GENERAT, ERR_TROP);
}

/*! \file sim.c
 * \brief Module de gestion de la simulation
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sim.h"
#include "particule.h"
#include "trounoir.h"
#include "generateur.h"
#include "error.h"
#include "constantes.h"

#define NB_TYPES	3

static int lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);																
int sim_lecture(char* nomFichier, KEYWORD modeLancement)
{
	TYPE typeParagraphe = GENERATEUR; //pour changer la façon dont on 
									//enregistre les informations après.
	char ligne[CHAR_MAX_LIGNE+1];
	FILE *fichier = NULL;
	int nbLignes = 0;
	int nbAppelsLectureP = 0;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
		error_fichier_inexistant();
	
	while(fgets(ligne, CHAR_MAX_LIGNE, fichier)) //récupération de la 
												//chaîne de caractères
	{
		if(isspace(ligne[0])||ligne[0] == '#') //ignorer les commentaires
		{
			continue; // lignes à ignorer, on passe à la suivante
		}
		else 
		{
			if(sscanf(ligne, "%u", &nbLignes) != 1) //Récupération et 
							//convertion en int de la première valeur.
			{
				switch(typeParagraphe) 	//Dans le cas où sscanf ne 
										//marcherait pas.
				{
					case GENERATEUR:
						error_lect_nb_elements(ERR_GENERAT); 
						return 1;
					case TROU_NOIR:
						error_lect_nb_elements(ERR_TROU_N);
						return 1;
					case PARTICULE:
						error_lect_nb_elements(ERR_PARTIC);
						return 1;
				}						
			}
			else
			{
				nbAppelsLectureP++;
				if(lecture_paragraphe(fichier, nbLignes, typeParagraphe)) 
										//traitement de l'information.
					return 1;
				switch(typeParagraphe) //change la manière d'enregistrer 
							//l'information car on change de paragraphe
				{
					case GENERATEUR:
						typeParagraphe = TROU_NOIR;
						break;
					case TROU_NOIR:
						typeParagraphe = PARTICULE;
						break;
					case PARTICULE:
						continue; //Traitement de l'information contenue 
									//dans le fichier complète.
				}
			}
		}
	}
	
	if(nbAppelsLectureP != NB_TYPES) //vérifier la lecture des trois 
														//paragraphes.
	{
		error_fichier_incomplet();
		return 1;
	}
	
	if(modeLancement == ERROR)
		error_success();
	else if(modeLancement == FORCE)
		particule_force_rendu1();
	return 0;
}
int lecture_paragraphe(FILE* fichier, int nbLignes, int typeParagraphe)
{
	char ligne[CHAR_MAX_LIGNE];
	
	for(int i = 0; i < nbLignes; i++)
	{
		if(fgets(ligne, CHAR_MAX_LIGNE, fichier) == NULL)
		{
			error_fichier_incomplet();
			return 1;
		}	
		if(isspace(ligne[0])||ligne[0] == '#') //évite les commentaires, 
												//espaces, etc.
		{
			i--;
			continue; 
		}
		else
		{
			if(strcmp(ligne, "FIN_LISTE\n"))//si ligne = FIN LISTE ne 
											//rentre pas dans le bloc 
											//du if.
			{
				switch(typeParagraphe) 	//on active la fonction pour 
										//découper et trier l'information
										//contenue dans chaque ligne 
										//selon le type de paragraphe.
				{
					case GENERATEUR:
						if(string_parsing_generateur(ligne, nbLignes) == NULL)
							return 1;
						break;
					case TROU_NOIR: 
						if(string_parsing_trou_noir(ligne, nbLignes) == NULL)
							return 1;
						break;
					case PARTICULE:
						if(string_parsing_particule(ligne, nbLignes) == NULL)
							return 1;
						break;
				}
			}	
			else
			{	
				switch(typeParagraphe)
				{
					case GENERATEUR:
						error_lecture_elements(ERR_GENERAT, ERR_PAS_ASSEZ); 
						return 1;
					case TROU_NOIR:
						error_lecture_elements(ERR_TROU_N, ERR_PAS_ASSEZ);
						return 1;
					case PARTICULE:
						error_lecture_elements(ERR_PARTIC, ERR_PAS_ASSEZ);
						return 1;
				}
			}
		}		
	}
	while(1)
	{
		if(fgets(ligne, CHAR_MAX_LIGNE, fichier) == NULL)
		{
			error_fichier_incomplet();
			return 1;
		}
		else if(strcmp(ligne, "FIN_LISTE\n") != 0)
		{
			if(!(isspace(ligne[0])||ligne[0] == '#'))
			{
				switch(typeParagraphe)
				{
					case GENERATEUR:
						error_lecture_elements(ERR_GENERAT, ERR_TROP);
						return 1;
					case TROU_NOIR:
						error_lecture_elements(ERR_TROU_N, ERR_TROP);
						return 1;
					case PARTICULE:
						error_lecture_elements(ERR_PARTIC, ERR_TROP);
						return 1;
				}
			}
		}
		else
			break;
	}
	return 0;	
}

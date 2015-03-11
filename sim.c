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

static void lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);
int erreur = 0;																
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
	FILE *fichier = NULL;
	int nbLignes = 0;
	
	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
	{	
		error_fichier_inexistant();
		erreur = 1;
	}	
	
	while(fgets(ligne, CHAR_MAX_LIGNE, fichier)) //On mets la première ligne du fichier dans la variable ligne pour pouvoir la traiter ensuite
	{
		#ifdef DEBUG
		o++;
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("Ligne %d actuellement en mémoire : %s", o, ligne);
		
		printf("firstChar : %X", ligne[0]);
		
		if(isspace(ligne[0])) //On teste la valeur du premier caractère.
			printf("\nLe if fonctionne.");
			
		printf("\033\[0m\n");
		#endif
		
		if(isspace(ligne[0])) //On teste la valeur du premier caractère.
		{
			#ifdef DEBUG
			printf("\033\[31m"); //message de debugging dans le prochain printf
			printf("La ligne %d est un commentaire", o);
			printf("\033\[0m\n");
			#endif
			continue; // lignes à ignorer, on passe à la suivante
		}
		else //Si le premier caractère de la ligne se trouve être une information importante.
		{
			if(sscanf(ligne, "%u", &nbLignes) != 1) //Récupération et convertion en int de la première valeur.
			{
				erreur = 1;
				switch(typeParagraphe) //Dans le cas où sscanf ne marcherait pas.
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
			else //Si la lecture s'est passée sans problème, on traite l'information.
			{
				lecture_paragraphe(fichier, nbLignes, typeParagraphe); //Après avoir TOUTE l'information du paragraphe, on change de
																		//type de paragraphe.
				switch(typeParagraphe)
				{
					case GENERATEUR:
						typeParagraphe = TROU_NOIR;
						break;
					case TROU_NOIR:
						typeParagraphe = PARTICULE;
						break;
					case PARTICULE:
						continue; //Traitement de l'information contenue dans le fichier complète.
				}
			}
		}
	}
	if(erreur != 1)
		error_success();
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
	
	for(int i = 0; i < nbLignes; i++)
	{
		fgets(ligne, CHAR_MAX_LIGNE, fichier);
		
		#ifdef DEBUG
		o++;
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("Ligne %d actuellement en mémoire dans lecture_paragraphe : %s", o, ligne);
		printf("\033\[0m\n");
		#endif
		
		if(isspace(ligne[0])) //On teste la valeur du premier caractère.
		{
			i--;
			continue; // lignes à ignorer, on passe à la suivante
		}
		else //dans le cas où il n'y aurait pas de commentaires:
		{
			if(strcmp(ligne, "FIN_LISTE")) //si ligne = FIN LISTE ne rentre pas dans le bloc du if.
			{
				#ifdef DEBUG
				printf("\033\[31m"); //message de debugging dans le prochain printf
				printf("Passage au parsing de la ligne par le type d'entités\
						%d", typeParagraphe);
				printf("\033\[0m\n");
				#endif
				switch(typeParagraphe) //on active la fonction pour découper et trier l'information contenue dans chaque ligne selon le
										//de paragraphe.
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
			else //si le nombre d'informations lu ne correspond pas au premier caractère donné par la ligne 
				// précédemment, on lance les fonctions d'erreur.
			{	
				erreur = 1;
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
	
	fgets(ligne, CHAR_MAX_LIGNE, fichier); //ATTENTION SI AU LIEU DE FIN LISTE ON TROUVE UN COMMENTAIRE??????
	if(!strcmp(ligne, "FIN_LISTE"))
	{	
		error_lecture_elements(ERR_GENERAT, ERR_TROP);
		erreur = 1;
	}	
}

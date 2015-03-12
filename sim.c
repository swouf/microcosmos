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

static int lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);																
int sim_lecture(char* nomFichier, KEYWORD modeLancement)
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
		error_fichier_inexistant();
	
	while(fgets(ligne, CHAR_MAX_LIGNE, fichier)) //On mets la première ligne du fichier dans la variable ligne pour pouvoir la traiter ensuite
	{
		#ifdef DEBUG
		o++;
		printf("\033\[31m"); //message de debugging dans le prochain printf
		printf("Ligne %d actuellement en mémoire : %s", o, ligne);
		
		printf("firstChar : %X", ligne[0]);
		
		if(isspace(ligne[0])||ligne[0] == '#') //On teste la valeur du premier caractère.
			printf("\nLe if fonctionne.");
			
		printf("\033\[0m\n");
		#endif
		
		if(isspace(ligne[0])||ligne[0] == '#') //On teste la valeur du premier caractère.
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
				switch(typeParagraphe) //Dans le cas où sscanf ne marcherait pas.
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
			else //Si la lecture s'est passée sans problème, on traite l'information.
			{
				if(lecture_paragraphe(fichier, nbLignes, typeParagraphe))
					return 1;//Après avoir TOUTE l'information du paragraphe, on change de
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
	if(modeLancement == ERROR)
		error_success();
	else if(modeLancement == FORCE)
		particule_force_rendu1();
	return 0;
}
int lecture_paragraphe(FILE* fichier, int nbLignes, int typeParagraphe)
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
		
		if(isspace(ligne[0])||ligne[0] == '#') //On teste la valeur du premier caractère.
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
	#ifdef DEBUG
	printf("\033\[31m"); //message de debugging dans le prochain printf
	printf("Parsing du paragraphe réussi");
	printf("\033\[0m\n");
	#endif
	
	fgets(ligne, CHAR_MAX_LIGNE, fichier); //ATTENTION SI AU LIEU DE FIN LISTE ON TROUVE UN COMMENTAIRE??????
	if(!strcmp(ligne, "FIN_LISTE"))
	{	
		error_lecture_elements(ERR_GENERAT, ERR_TROP);
		return 1;
	}
	return 0;	
}

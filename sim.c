/*!
 * \file sim.c
 * \brief Module de gestion de la simulation
 * \date 19.04.2015
 * \version 2
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include "particule.h"
#include "trounoir.h"
#include "generateur.h"
#include "error.h"
#include "constantes.h"
#include "sim.h"
#include "graphic.h"

#define NB_TYPES	3

static int lecture_paragraphe(FILE* fichier, int nb_lignes, \
								int typeParagraphe);
int sim_lecture(const char* nomFichier)
{
	char	ligne[CHAR_MAX_LIGNE+1];
	FILE	*fichier		= NULL;
	int		nbLignes		= 0;
	int		nbAppelsLectureP= 0;
	TYPE	typeParagraphe	= GENERATEUR; //pour changer la façon dont
										  //on enregistre les
										  //informations après.

	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
	{
		error_fichier_inexistant();
		return 1;
	}

	while(fgets(ligne, CHAR_MAX_LIGNE, fichier)) //récupération de la
												//chaîne de caractères
	{
		if(isspace(ligne[0])||ligne[0] == '#') //ignore les commentaires
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
				if(lecture_paragraphe(fichier, nbLignes,
									  typeParagraphe))
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

	print_data_sim();
	set_display_limits();
	print_data_sim();

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
						if(string_parsing_generateur(ligne) == NULL)
							return 1;
						break;
					case TROU_NOIR:
						if(string_parsing_trou_noir(ligne) == NULL)
							return 1;
						break;
					case PARTICULE:
						if(string_parsing_particule(ligne) == NULL)
							return 1;
						break;
				}
			}
			else
			{
				switch(typeParagraphe)
				{
					case GENERATEUR:
						error_lecture_elements(ERR_GENERAT,
											   ERR_PAS_ASSEZ);
						return 1;
					case TROU_NOIR:
						error_lecture_elements(ERR_TROU_N,
											   ERR_PAS_ASSEZ);
						return 1;
					case PARTICULE:
						error_lecture_elements(ERR_PARTIC,
											   ERR_PAS_ASSEZ);
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
		else if(strncmp(ligne, "FIN_LISTE", 9) == 0)
		{
			break;
		}
		else
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
	}
	return 0;
}
int sim_ecriture(const char* nomFichier)
{
	print_data_sim();
	FILE *fichier = NULL;
	fichier = fopen(nomFichier, "wt");
	if(fichier == NULL)
	{
		error_msg("Échec de la sauvegarde de l'état de la simulation.");
		return 1;
	}

/*********************** Récupération des générateurs *************************/

	Generateur_t* genTMP= NULL;
	int nbGenerateurs = get_nb_generateurs();

	fprintf(fichier, "%d\n", nbGenerateurs);

	for(int i=0;i<nbGenerateurs;i++)
	{
		genTMP = get_gen_by_id(i);
		if(genTMP == NULL)
			break;
		fprintf(fichier, "%f %f %f %f %f\n",
				get_gen_rgen(genTMP),
				get_gen_posx(genTMP),
				get_gen_posy(genTMP),
				get_gen_vpix(genTMP),
				get_gen_vpiy(genTMP));
	}
	fprintf(fichier, "FIN_LISTE\n\n");

/*********************** Récupération des trous noirs *************************/

	Trounoir_t* trouNoirTMP= NULL;
	int nbTrousNoirs = get_nb_trous_noirs();

	fprintf(fichier, "%d\n", nbTrousNoirs);

	for(int i=0;i<nbTrousNoirs;i++)
	{
		trouNoirTMP = get_trou_noir_by_id(i);
		if(trouNoirTMP == NULL)
			break;
		fprintf(fichier, "%f %f\n",
				get_trou_noir_posx(trouNoirTMP),
				get_trou_noir_posy(trouNoirTMP));
	}
	fprintf(fichier, "FIN_LISTE\n\n");

/*********************** Récupération des particules **************************/

	Particule_t* partTMP= NULL;
	int nbParticules = get_nb_particules();

	fprintf(fichier, "%d\n", nbParticules);

	for(int i=0;i<nbParticules;i++)
	{
		partTMP = get_part_by_id(i);
		if(partTMP == NULL)
			break;
		fprintf(fichier, "%f %f %f %f %f\n",
				get_part_rayon(partTMP),
				get_part_posx(partTMP),
				get_part_posy(partTMP),
				get_part_vx(partTMP),
				get_part_vy(partTMP));
	}
	fprintf(fichier, "FIN_LISTE\n");

	fclose(fichier);
	return 0;
}
void sim_clean(void)
{
    clean_generateurs();
    clean_particules();
    clean_trous_noirs();
}
void sim_display(void)
{
    display_generateurs();
    display_trous_noirs();
    display_particules();
}
void force(void)
{
    particule_force_rendu1();
}
void integration(void)
{
    particule_integration_rendu2();
}
int** get_3ptr_nb_entite(void)
{
	static int* ptrNbEntite[3];

	ptrNbEntite[0] = get_ptr_nb_part();
	ptrNbEntite[1] = get_ptr_nb_gen();
	ptrNbEntite[2] = get_ptr_nb_trous_noirs();

	return ptrNbEntite;
}
void set_display_limits(void)
{
	double xMax = DBL_MIN;
	double xMin = DBL_MAX;
	double yMax = DBL_MIN;
	double yMin = DBL_MAX;

	double x	= 0;
	double y	= 0;

	int nbGenerateurs	= get_nb_generateurs();
	int nbTrousNoirs	= get_nb_trous_noirs();
	int nbParticules	= get_nb_particules();

	printf("nbGen : %d\nnbTrNoirs : %d\nnbPart : %d\n", nbGenerateurs, nbTrousNoirs, nbParticules);

	Generateur_t*	genTMP		= NULL;
	Trounoir_t*		trouNoirTMP	= NULL;
	Particule_t*	partTMP		= NULL;

	for(int i=0;i<nbGenerateurs;i++)
	{
		genTMP = get_gen_by_id(i);
		if(genTMP == NULL)
			break;
		x = get_gen_posx(genTMP);
		y = get_gen_posy(genTMP);

		printf("Generateur %d : (%f;%f)\n", i, x, y);
		printf("x : %f\ny : %f\n-xMax : %f\n-xMin : %f\n-yMax : %f\n-yMin : %f\n", x, y, xMax, xMin, yMax, yMin);

		if(x >= xMax)
			xMax = x;
		if(x <= xMin)
			xMin = x;

		if(y >= yMax)
			yMax = y;
		if(y <= yMin)
			yMin = y;
	}
	printf("yMin à la sortie de la boucle des generateurs : %f\n", yMin);
	for(int i=0;i<nbTrousNoirs;i++)
	{
		trouNoirTMP = get_trou_noir_by_id(i);
		if(trouNoirTMP == NULL)
			break;
		x = get_trou_noir_posx(trouNoirTMP);
		y = get_trou_noir_posy(trouNoirTMP);

		if(x >= xMax)
			xMax = x;
		if(x <= xMin)
			xMin = x;

		if(y >= yMax)
			yMax = y;
		if(y <= yMin)
			yMin = y;
		printf("Trou noir %d : (%f;%f)\n", i, x, y);
	}
	for(int i=0;i<nbParticules;i++)
	{
		partTMP = get_part_by_id(i);
		if(partTMP == NULL)
			break;
		x = get_part_posx(partTMP);
		y = get_part_posy(partTMP);

		if(x >= xMax)
			xMax = x;
		if(x <= xMin)
			xMin = x;

		if(y >= yMax)
			yMax = y;
		if(y <= yMin)
			yMin = y;

		printf("Particule %d : (%f;%f)\n", i, x, y);
	}

	set_projection_limits(xMax, xMin, yMax, yMin);
}
// FONCTION DE DEBUGGING
void print_data_sim(void)
{

	printf("\033[33m#### DONNÉE DE LA SIMULATION ####\n");

/*********************** Récupération des générateurs *************************/

	printf("# Générateurs #\n");

	Generateur_t* genTMP= NULL;
	int nbGenerateurs = get_nb_generateurs();

	printf("%d\n", nbGenerateurs);

	for(int i=0;i<nbGenerateurs;i++)
	{
		genTMP = get_gen_by_id(i);
		if(genTMP == NULL)
			break;
		printf("%f %f %f %f %f\n",
				get_gen_rgen(genTMP),
				get_gen_posx(genTMP),
				get_gen_posy(genTMP),
				get_gen_vpix(genTMP),
				get_gen_vpiy(genTMP));
	}

/*********************** Récupération des trous noirs *************************/

	printf("# Trous Noirs #\n");

	Trounoir_t* trouNoirTMP= NULL;
	int nbTrousNoirs = get_nb_trous_noirs();

	printf("%d\n", nbTrousNoirs);

	for(int i=0;i<nbTrousNoirs;i++)
	{
		trouNoirTMP = get_trou_noir_by_id(i);
		if(trouNoirTMP == NULL)
			break;
		printf("%f %f\n",
				get_trou_noir_posx(trouNoirTMP),
				get_trou_noir_posy(trouNoirTMP));
	}

/*********************** Récupération des particules **************************/

	printf(" Particules #\n");

	Particule_t* partTMP= NULL;
	int nbParticules = get_nb_particules();

	printf("%d\n", nbParticules);

	for(int i=0;i<nbParticules;i++)
	{
		partTMP = get_part_by_id(i);
		if(partTMP == NULL)
			break;
		printf("%f %f %f %f %f\n",
				get_part_rayon(partTMP),
				get_part_posx(partTMP),
				get_part_posy(partTMP),
				get_part_vx(partTMP),
				get_part_vy(partTMP));
	}
	printf("\033[0m");
}
void start(void)
{
	printf("start()\n");
}
void step(void)
{
	printf("step()\n");
}

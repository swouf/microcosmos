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

static int lecture_paragraphe_generateur(FILE*, int);
static int lecture_paragraphe_trou_noir(FILE*, int);
static int lecture_paragraphe_particule(FILE*, int);

int sim_lecture(const char* nomFichier)
{
	char		ligne[CHAR_MAX_LIGNE+1];
	FILE		*fichier		= NULL;
	int			nbLignes		= 0;
	int			nbAppelsLectureP= 0;
	ERREUR_ORIG	typeErreur	= ERR_GENERAT;

	fichier = fopen(nomFichier, "rt");
	if (fichier == NULL)
	{
		error_fichier_inexistant();
		return 1;
	}
	while(fgets(ligne, CHAR_MAX_LIGNE, fichier))
	{
		if(isspace(ligne[0])||ligne[0] == '#')
			continue;
		else
		{
			if(sscanf(ligne, "%u", &nbLignes) != 1)
			{
				error_lect_nb_elements(typeErreur);
				return 1;
			}
			else
			{
				nbAppelsLectureP++;
				switch(typeErreur)
				{
					case ERR_GENERAT:
						if(lecture_paragraphe_generateur(fichier,\
														nbLignes))
							return 1;
						typeErreur = ERR_TROU_N;
						break;
					case ERR_TROU_N:
						if(lecture_paragraphe_trou_noir(fichier,\
														nbLignes))
						return 1;
						typeErreur = ERR_PARTIC;
						break;
					case ERR_PARTIC:
						if(lecture_paragraphe_particule(fichier,\
														nbLignes))
							return 1;
						continue;
	}	}	}	}
	if(nbAppelsLectureP != NB_TYPES)
	{
		error_fichier_incomplet();
		return 1;
	}
	set_display_limits();
	return 0;
}
int lecture_paragraphe_generateur(FILE* fichier, int nbLignes)
{
	char ligne[CHAR_MAX_LIGNE];
	for(int i = 0; i < nbLignes; i++)
	{
		if(fgets(ligne, CHAR_MAX_LIGNE, fichier) == NULL)
		{
			error_fichier_incomplet();
			return 1;
		}
		if(isspace(ligne[0])||ligne[0] == '#')
		{
			i--;
			continue;
		}
		else
		{
			if(strncmp(ligne, "FIN_LISTE", 9))
			{
				if(string_parsing_generateur(ligne) == NULL)
					return 1;
			}
			else
			{
				error_lecture_elements(ERR_GENERAT,\
										ERR_PAS_ASSEZ);
				return 1;
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
			break;
		else
		{
			if(!(isspace(ligne[0])||ligne[0] == '#'))
			{
				error_lecture_elements(ERR_GENERAT, ERR_TROP);
				return 1;
			}
		}
	}
	return 0;
}
int lecture_paragraphe_trou_noir(FILE* fichier, int nbLignes)
{
	char ligne[CHAR_MAX_LIGNE];
	for(int i = 0; i < nbLignes; i++)
	{
		if(fgets(ligne, CHAR_MAX_LIGNE, fichier) == NULL)
		{
			error_fichier_incomplet();
			return 1;
		}
		if(isspace(ligne[0])||ligne[0] == '#')
		{
			i--;
			continue;
		}
		else
		{
			if(strncmp(ligne, "FIN_LISTE", 9))
			{
				if(string_parsing_trou_noir(ligne) == NULL)
					return 1;
			}
			else
			{
				error_lecture_elements(ERR_TROU_N,\
										ERR_PAS_ASSEZ);
				return 1;
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
			break;
		else
		{
			if(!(isspace(ligne[0])||ligne[0] == '#'))
			{
				error_lecture_elements(ERR_TROU_N, ERR_TROP);
				return 1;
			}
		}
	}
	return 0;
}
int lecture_paragraphe_particule(FILE* fichier, int nbLignes)
{
	char ligne[CHAR_MAX_LIGNE];
	for(int i = 0; i < nbLignes; i++)
	{
		if(fgets(ligne, CHAR_MAX_LIGNE, fichier) == NULL)
		{
			error_fichier_incomplet();
			return 1;
		}
		if(isspace(ligne[0])||ligne[0] == '#')
		{
			i--;
			continue;
		}
		else
		{
			if(strncmp(ligne, "FIN_LISTE", 9))
			{
				if(string_parsing_particule(ligne) == NULL)
					return 1;
			}
			else
			{
				error_lecture_elements(ERR_PARTIC,\
										ERR_PAS_ASSEZ);
				return 1;
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
			break;
		else
		{
			if(!(isspace(ligne[0])||ligne[0] == '#'))
			{
				error_lecture_elements(ERR_PARTIC, ERR_TROP);
				return 1;
			}
		}
	}
	return 0;
}
int sim_ecriture(const char* nomFichier)
{
	FILE *fichier = NULL;
	fichier = fopen(nomFichier, "wt");
	if(fichier == NULL)
	{
		error_msg("Échec de la sauvegarde de l'état de la simulation.");
		return 1;
	}
	Generateur_t*	genTMP			= NULL;
	Trounoir_t*		trouNoirTMP		= NULL;
	Particule_t*	partTMP			= NULL;
	int				nbGenerateurs	= get_nb_generateurs();
	int				nbTrousNoirs	= get_nb_trous_noirs();
	int				nbParticules	= get_nb_particules();
/******************* Récupération des générateurs *********************/
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
/******************* Récupération des trous noirs *********************/
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
/******************* Récupération des particules **********************/
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
int* get_3nb_entite(void)
{
	static int ptrNbEntite[3];

	ptrNbEntite[0] = get_nb_particules();
	ptrNbEntite[1] = get_nb_generateurs();
	ptrNbEntite[2] = get_nb_trous_noirs();

	return ptrNbEntite;
}
void set_display_limits(void)
{
	double			x, y;
	double			xMax			= DBL_MIN;
	double			xMin			= DBL_MAX;
	double			yMax			= DBL_MIN;
	double			yMin			= DBL_MAX;
	int				nbGenerateurs	= get_nb_generateurs();
	int				nbTrousNoirs	= get_nb_trous_noirs();
	int				nbParticules	= get_nb_particules();
	Generateur_t*	genTMP			= NULL;
	Trounoir_t*		trouNoirTMP		= NULL;
	Particule_t*	partTMP			= NULL;

	for(int i=0;i<nbGenerateurs;i++)
	{
		genTMP = get_gen_by_id(i);
		if(genTMP == NULL) break;
		x = get_gen_posx(genTMP);
		y = get_gen_posy(genTMP);
		if(x >= xMax) xMax = x;
		if(x <= xMin) xMin = x;
		if(y >= yMax) yMax = y;
		if(y <= yMin) yMin = y;
	}
	for(int i=0;i<nbTrousNoirs;i++)
	{
		trouNoirTMP = get_trou_noir_by_id(i);
		if(trouNoirTMP == NULL) break;
		x = get_trou_noir_posx(trouNoirTMP);
		y = get_trou_noir_posy(trouNoirTMP);
		if(x >= xMax) xMax = x;
		if(x <= xMin) xMin = x;
		if(y >= yMax) yMax = y;
		if(y <= yMin) yMin = y;
	}
	for(int i=0;i<nbParticules;i++)
	{
		partTMP = get_part_by_id(i);
		if(partTMP == NULL) break;
		x = get_part_posx(partTMP);
		y = get_part_posy(partTMP);
		if(x >= xMax) xMax = x;
		if(x <= xMin) xMin = x;
		if(y >= yMax) yMax = y;
		if(y <= yMin) yMin = y;
	}
	set_projection_limits(xMax, xMin, yMax, yMin);
}
void start(void)
{
	printf("start()\n");
}
void step(void)
{
	printf("step()\n");
}

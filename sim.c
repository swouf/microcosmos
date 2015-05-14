/*!
 * \file sim.c
 * \brief Module de gestion de la simulation
 * \date 14.05.2015
 * \version alpha3
 * \author Minh Truong & Jérémy Jayet
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <time.h>
#include <complex.h>
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

static int				isStarted		= 0;
static Particule_t*		selectedPart	= NULL;
static Generateur_t*	selectedGen		= NULL;
static Trounoir_t*		selectedTN		= NULL;

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
void sim_update(void)
{
	if(isStarted)
	{
		printf("###---### APPELLE DE SIM_UPDATE (started mode) ###---###\n"); // DEBUG
		double		 x, y;
		Particule_t* part              = NULL;
	    Particule_t* updatedParticule  = NULL;
		Particule_t* prevParticule	   = NULL;
		double*		 forceTN		   = NULL;

		for(int i=0;i<get_nb_particules();i++)
	    {
			part = get_part_by_id(i);

			if(part == selectedPart)
			{
				x = get_part_posx(part);
				y = get_part_posy(part);
				updatedParticule = update_particule(part, prevParticule,\
													0, 0);
				set_part_pos(updatedParticule, x, y);
				selectedPart = updatedParticule;
			}
			else
			{
				x = get_part_posx(part);
				y = get_part_posy(part);
				forceTN = force_trous_noirs(x, y);
				updatedParticule = update_particule(part, prevParticule,\
													forceTN[0],\
													forceTN[1]);
			}
			if(is_on_trous_noirs(get_part_rayon(updatedParticule),\
						 get_part_posx(updatedParticule),\
						 get_part_posy(updatedParticule)))
			{
				delete_part(updatedParticule, NULL);
				updatedParticule = prevParticule;
			}
			else prevParticule = updatedParticule;

			//printf("## Computation de la particule : %d, d'adresse d'origine 0x%X et d'adresse actuelle 0x%X ##\n", i, part, updatedParticule); // DEBUG
		}
		clean_particules();
		set_ptrParticules(updatedParticule);

		/***************************************************************
		* Partie qui gère les générateurs !
		***************************************************************/
		int 			canGen	= 1;
		double			rayon	= 0;
		double			rGen	= 0;
		double			xGen	= 0;
		double			yGen	= 0;
		double			vpix	= 0;
		double			vpiy	= 0;
		Generateur_t*	gen		= NULL;

		for(int i=0;i<get_nb_generateurs();i++)
	    {
			gen = get_gen_by_id(i);
			xGen = get_gen_posx(gen);
			yGen = get_gen_posy(gen);
			for(int i=0;i<get_nb_particules();i++)
		    {
				part = get_part_by_id(i);
				rayon = get_part_rayon(part);
				x = get_part_posx(part);
				y = get_part_posy(part);

				if(cabs((x+y*I)-(xGen+yGen*I)) <= rayon)
				{
					canGen = 0;
				}
			}
			//printf("canGen = %d\n", canGen);
			if(canGen)
			{
				if(1)
				{
					rGen = get_gen_rgen(gen);
					vpix = get_gen_vpix(gen);
					vpiy = get_gen_vpiy(gen);

					add_particule(rGen, xGen, yGen, vpix, vpiy);
				}
			}
			else continue;
		}
	}
}
void start(void)
{
	isStarted = !isStarted;
	printf("Simulation started : isStarted = %d\n", isStarted);
	srand(time(NULL));
}
void step(void)
{
	if(!isStarted)
	{
		isStarted = 1;
		sim_update();
		isStarted = 0;
	}
}
void sim_mouse_press(double x, double y)
{
	Particule_t*	part		= NULL;
	Generateur_t*	gen			= NULL;
	Trounoir_t*		trouNoir	= NULL;

	double complex pos	= x+y*I;
	double rayon		= 0;
	double entiteX		= 0;
	double entiteY		= 0;

	for(int i=0;i<get_nb_particules();i++)
	{
		part = get_part_by_id(i);
		rayon = get_part_rayon(part);
		entiteX = get_part_posx(part);
		entiteY = get_part_posy(part);

		/*printf("## 0x%X ##\nrayon = %lf\nposx = %lf\nposy = %lf\n", part,\
																	rayon,\
																	entiteX,\
																	entiteY); // DEBUG*/

		if(cabs(pos-(entiteX+entiteY*I)) <= rayon) selectedPart = part;
	}
	if(selectedPart) printf("Particule d'adresse : 0x%X séléctionnée\n", selectedPart); // DEBUG
	if(selectedPart == NULL)
	{
		rayon = DBL_MAX;
		for(int i=0;i<get_nb_generateurs();i++)
		{
			gen = get_gen_by_id(i);
			entiteX = get_gen_posx(gen);
			entiteY = get_gen_posy(gen);

			if(cabs(pos-(entiteX+entiteY*I)) <= rayon)
			{
				selectedGen = gen;
				rayon = cabs(pos-(entiteX+entiteY*I));
			}
		}
		if(selectedGen) printf("Générateur d'adresse : 0x%X séléctionnée\n", selectedGen); //DEBUG
		for(int i=0;i<get_nb_trous_noirs();i++)
		{
			trouNoir = get_trou_noir_by_id(i);
			entiteX = get_trou_noir_posx(trouNoir);
			entiteY = get_trou_noir_posy(trouNoir);

			if(cabs(pos-(entiteX+entiteY*I)) <= rayon)
			{
				selectedTN = trouNoir;
				rayon = cabs(pos-(entiteX+entiteY*I));
			}
		}
		if(selectedTN) selectedGen = NULL;
		if(selectedTN) printf("Trou noir d'adresse : 0x%X séléctionnée\n", selectedTN); // DEBUG
	}
}
void sim_mouse_release(void)
{
	selectedPart	= NULL;
	selectedGen		= NULL;
	selectedTN		= NULL;
}
void sim_keyboard(unsigned char key)
{
	if(key == 'd')
	{
		int i;

		if(selectedPart)
		{
			for(i=0;get_part_by_id(i) != selectedPart;i++);
			delete_part_by_id(i);
			printf("Deleting selected particle : 0x%X\n", (unsigned int)selectedPart); // DEBUG
			selectedPart = NULL;
		}
		else if(selectedGen)
		{
			for(i=0;get_gen_by_id(i) != selectedGen;i++);
			delete_gen_by_id(i);
			printf("Deleting selected generator : 0x%X\n", (unsigned int)selectedGen); // DEBUG
			selectedGen = NULL;
		}
		else if(selectedTN)
		{
			for(i=0;get_trou_noir_by_id(i) != selectedTN;i++);
			delete_trou_noir_by_id(i);
			printf("Deleting selected black hole : 0x%X\n", (unsigned int)selectedTN); // DEBUG
			selectedTN = NULL;
		}
		else
		{
			printf("Nothing to delete.\n");
		}
	}
}

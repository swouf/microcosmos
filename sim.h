/*!
 * \file sim.h
 * \brief (HEADER) Module de gestion de la simulation
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef SIM_H
#define SIM_H

typedef enum type
{
	GENERATEUR 	= 1,
	TROU_NOIR 	= 2,
	PARTICULE 	= 3
}	TYPE;

/*!
 * \fn int sim_lecture(char* nomFichier)
 * \brief Lit le fichier texte passé en argument
 * \details Lit le fichier texte passé en argument afin d'enregistrer
 * les données qui sont contenues (selon le format de fichier décrit
 * dans le cahier des charges). À la fin, elle execute une fonction
 * dépendant du paramètre KEYWORD.
 * \param nomFichier : nom du fichier à lire. La chaîne de caractères)
 * n'est pas modifié par la fonction.
 * modeLancement : mode dans lequel le programme a été lancé
 * \return Retourne 0 si tout s'est bien passé, 1 en cas d'erreur.
 */
int sim_lecture(const char*);
int sim_ecriture(const char*);
void sim_clean(void);
void sim_display(void);
void force(void);
void integration(void);

#endif

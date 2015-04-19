/*!
 * \file sim.h
 * \brief (HEADER) Module de gestion de la simulation
 * \date 19.04.2015
 * \version 2
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

/*!
 * \fn int sim_ecriture(const char* nomFichier)
 * \brief
 * \param nomFichier : nom du fichier dans lequel sera écrit l'état de
 *						la simulation.
 * \return Retourne 0 si tout c'est passé correctement, 1 en cas
 *			d'erreur.
 */
int sim_ecriture(const char*);

/*!
 * \fn void sim_clean(void)
 * \brief Vide les données de la simulation (libère la mèmoire).
 */
void sim_clean(void);

/*!
 * \fn void sim_display(void)
 * \brief Affiche le modèle de la simulation.
 */
void sim_display(void);

/*!
 * \fn void force(void)
 * \brief Fonction du mode "Force".
 */
void force(void);

/*!
 * \fn void integration(void)
 * \brief Fonction du mode "Integration".
 */
void integration(void);

/*!
 * \fn int** get_3ptr_nb_entite(void)
 * \brief Sert à obtenir un tableau contenant 3 pointeurs sur des
 *			variables (int) contenant chacune le nombre d'entités
 *			enregistrées dans leurs modules respectifs.
 * \return Retourne un tableau (pointeur) contenant des pointeurs :
 *		   	---------------------------------------------
 *		   	+ Case 1 : pointeurs sur nbGenerateurs		+
 *			+ Case 2 : pointeurs sur nbTrousNoirs		+
 *			+ Case 2 : pointeurs sur nbParticules		+
 *			---------------------------------------------
 */
int** get_3ptr_nb_entite(void);

/*!
 * \fn void set_display_limits(void)
 * \brief Trouve les limites du domaine contenant des entités pour
 *			pouvoir définir les limites de la projection.
 */
void set_display_limits(void);

/*!
 * \fn void start(void)
 * \brief Démarre la simulation
 */
void start(void);

/*!
 * \fn void start(void)
 * \brief Fait avancer la simulation d'un pas de temps
 */
void step(void);
#endif

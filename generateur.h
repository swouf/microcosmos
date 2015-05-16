/*!
 * \file generateur.h
 * \brief (HEADER) Module de gestion des entités générateurs
 * \date 17.05.2015
 * \version 3
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef GENERATEUR_H
#define GENERATEUR_H
typedef struct Generateur Generateur_t;

/*!
 * \fn Generateur_t* string_parsing_generateur(char* ligne)
 * \brief Découpe la ligne et enregistre les informations dans une
 * structure Generateur_t.
 * \param ligne : chaîne de caractères qui n'est pas modifiée par la
 * fonction.
 * \return Pointeur sur le tableau contenant le tableau de Generateur_t.
 * Retourne NULL en cas d'erreur.
 */
Generateur_t* string_parsing_generateur(char*);

/*!
 * \fn void display_generateurs(void)
 * \brief Affiche les générateurs
 */
void display_generateurs(void);

/*!
 * \fn void clean_generateurs(void)
 * \brief Vide complètement la liste chaînée contenue dans le module et
 *          remets le pointeur ptrGenerateurs ainsi que la variable
 *          nbGenerateurs respectivement à NULL et à 0 (zéro).
 */
void clean_generateurs(void);

/*!
 * \fn Generateur_t* get_gen_by_id(int id)
 * \brief Récupère un pointeur sur un générateur en donnant son id (sa
 *          place dans la liste contenant les générateurs).
 * \param id : place du générateur dans la liste contenant les
 * 				générateurs.
 * \return Pointeur sur le générateur, ou NULL en cas d'erreur (id trop
 *          grand ou autre)
 */
Generateur_t* get_gen_by_id(int);

/*!
 * \fn get_gen_rgen(Generateur_t* gen)
 * \brief Récupére le rayon d'un générateur.
 * \param gen: pointeur sur le générateur dont on veut récupérer
 *             le rayon.
 * \return Rayon de la particule générée.
 */
double get_gen_rgen(Generateur_t*);

/*!
 * \fn double get_gen_posx(Generateur_t* gen)
 * \brief Récupére la position en x d'un générateur.
 * \param gen : pointeur sur le générateur dont on veut récupérer
 *                   la position x.
 * \return Position en x du générateur.
 */
double get_gen_posx(Generateur_t*);

/*!
 * \fn double get_gen_posy(Generateur_t* gen)
 * \brief Récupére la position en y d'un générateur.
 * \param gen : pointeur sur le générateur dont on veut récupérer
 *                   la position y.
 * \return Position en y du générateur.
 */
double get_gen_posy(Generateur_t*);

/*!
 * \fn get_gen_vpix(Generateur_t* gen)
 * \brief Récupère la vitesse initiale x de la particule générée.
 * \param gen : pointeur sur le générateur dont on veut récupérer
 *                   la vitesse initiale x de la particule.
 * \return La vitesse initiale x de la particule générée.
 */
double get_gen_vpix(Generateur_t*);

/*!
 * \fn get_gen_vpiy(Generateur_t* gen)
 * \brief Récupère la vitesse initiale y de la particule générée
 * \param gen : pointeur sur le générateur dont on veut récupérer
 *                   la vitesse initiale y de la particule.
 * \return La vitesse initiale y de la particule générée.
 */
double get_gen_vpiy(Generateur_t*);

/*!
 * \fn get_nb_generateurs(void)
 * \brief Récupère le nombre de générateurs.
 * \return Le nombre de générateurs.
 */
int get_nb_generateurs(void);

/*!
 * \fn void delete_gen_by_id(int id)
 * \brief   Efface le générateur sélectionné par son identifiant.
 * \param   id : identifiant du générateur (compris entre 0 et
 *          nbGenerateurs - 1).
 */
void delete_gen_by_id(int);

#endif

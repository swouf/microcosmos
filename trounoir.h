    /*!
 * \file trounoir.h
 * \brief (HEADER) Module de gestion des entités trous noirs
 * \date 19.04.2015
 * \version 2
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef TROUNOIR_H
#define TROUNOIR_H

typedef struct Trounoir Trounoir_t;

/*!
 * \fn Trounoir_t* string_parsing_trou_noir(char* ligne)
 * \brief Découpe la ligne et enregistre les informations dans une
 * structure Trounoir_t.
 * \param ligne : chaîne de caractères qui n'est pas modifiée par la
 * fonction.
 * \return Pointeur sur le tableau contenant le tableau de Trounoir_t.
 * Retourne NULL en cas d'erreur.
 */
Trounoir_t* string_parsing_trou_noir(char*);

/*!
 * \fn void clean_trous_noirs(void)
 * \brief Vide complétement la liste chainée contenue dans le module et
 *          remets le pointeur ptrTrousNoirs ainsi que la variable
 *          nbTrousNoirs respectivement à NULL et à 0 (zéro).
 */
void clean_trous_noirs(void);

/*!
 * \fn void display_trous_noirs(void)
 * \brief Affiche les trous noirs
 */
void display_trous_noirs(void);

/*!
 * \fn Trounoir_t* get_trou_noir_by_id(int id)
 * \brief Récupére un pointeur sur un trou noir en donnant son id (sa
 *          place dans la liste contenant les trous noirs).
 * \param id : place du trou noir dans la liste contenant les trous
 *              noirs.
 * \return Pointeur sur le trou noir, ou NULL en cas d'erreur (id trop
 *          grand ou autre)
 */
Trounoir_t* get_trou_noir_by_id(int);

/*!
 * \fn double get_trou_noir_posx(Trounoir_t* trouNoir)
 * \brief Récupére la position en x d'un trou noir.
 * \param trouNoir : pointeur sur le trou noir dont on veut récupérer
 *                   la position.
 * \return Position en x du trou noir
 */
double get_trou_noir_posx(Trounoir_t*);

/*!
 * \fn double get_trou_noir_posy(Trounoir_t* trouNoir)
 * \brief Récupére la position en y d'un trou noir.
 * \param trouNoir : pointeur sur le trou noir dont on veut récupérer
 *                   la position.
 * \return Position en y du trou noir
 */
double get_trou_noir_posy(Trounoir_t*);

/*!
 * \fn double get_trou_noir_posy(Trounoir_t* trouNoir)
 * \brief Récupére le nombre de trous noirs dans la simulation.
 * \return nombre de trous noirs dans la simulation
 */
int get_nb_trous_noirs(void);

#endif

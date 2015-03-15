/*!
 * \file particule.h
 * \brief (HEADER) Module de gestion des entités particules
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

#ifndef PARTICULE_H
#define PARTICULE_H

typedef struct Particule Particule_t;

/*!
 * \fn Particule_t* string_parsing_particule(char* ligne)
 * \brief Découpe la ligne et enregistre les informations dans une
 * structure Particule_t.
 * \param ligne : chaîne de caractères qui n'est pas modifiée par la
 * fonction.
 * \return Pointeur sur le tableau contenant le tableau de Particule_t
 */
Particule_t* string_parsing_particule(char*);

/*!
 * \fn void set_tab_particules(Particule_t* ptrTabPart)
 * \brief Fonction pour définir le pointeur destiné à stocker l'adresse
 * du tableau de Particule_t
 * \param ptrTabPart : Pointeur sur un tableau de Particule_t
 */
void set_tab_particules(Particule_t*);

/*!
 * \fn Particule_t* get_tab_particules(void)
 * \brief Fonction pour récupérer le pointeur stockant l'adresse
 * du tableau de Particule_t
 * \return Pointeur sur un tableau de Particule_t. Retourne NULL en cas
 * d'erreur.
 */
Particule_t* get_tab_particules(void); 

/*!
 * \fn void particule_force_rendu1(void)
 * \brief Calcule la force entre deux particules en fonction de la
 * distance qui les sépare.
 */
void particule_force_rendu1(void);

#endif

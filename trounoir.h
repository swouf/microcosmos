/*!
 * \file trounoir.h
 * \brief (HEADER) Module de gestion des entités trous noirs
 * \date 15.03.2015
 * \version 1
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
#endif

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
 * remets le pointeur ptrTrousNoirs ainsi que la variable nbTrousNoirs
 * respectivement à NULL et à 0 (zéro).
 */
void clean_trous_noirs(void);


void display_trous_noirs(void);
Trounoir_t* get_trou_noir_by_id(int);
double get_trou_noir_posx(Trounoir_t*);
double get_trou_noir_posy(Trounoir_t*);
int get_nb_trous_noirs(void);
int* get_ptr_nb_trous_noirs(void);

#endif

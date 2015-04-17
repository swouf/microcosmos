/*!
 * \file generateur.h
 * \brief (HEADER) Module de gestion des entités générateurs
 * \date 15.03.2015
 * \version 1
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

void display_generateurs(void);

void clean_generateurs(void);

Generateur_t* get_gen_by_id(int);
double get_gen_rgen(Generateur_t*);
double get_gen_posx(Generateur_t*);
double get_gen_posy(Generateur_t*);
double get_gen_vpix(Generateur_t*);
double get_gen_vpiy(Generateur_t*);
int get_nb_generateurs(void);
int* get_ptr_nb_gen(void);

#endif

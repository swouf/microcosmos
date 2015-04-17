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

void clean_particules(void);

int get_nb_particules(void);

void display_particules(void);

void particule_integration_rendu2(void);

/*!
 * \fn void particule_force_rendu1(void)
 * \brief Calcule la force entre deux particules en fonction de la
 * distance qui les sépare.
 */
void particule_force_rendu1(void);

Particule_t* get_part_by_id(int);
double get_part_rayon(Particule_t*);
double get_part_posx(Particule_t*);
double get_part_posy(Particule_t*);
double get_part_vx(Particule_t*);
double get_part_vy(Particule_t*);
int* get_ptr_nb_part(void);

#endif

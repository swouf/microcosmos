/*!
 * \file particule.h
 * \brief (HEADER) Module de gestion des entités particules
 * \date 19.04.2015
 * \version 2
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
 * \fn void clean_particules(void)
 * \brief Vide complétement la liste chainée contenue dans le module et
 *          remets le pointeur ptrParticules ainsi que la variable
 *          nbParticules respectivement à NULL et à 0 (zéro).
 */
void clean_particules(void);

/*!
 * \fn int get_nb_particules(void)
 * \brief Récupére le nombre de particules dans la simulation.
 * \return Nombre de particules dans la simulation
 */
int get_nb_particules(void);

void update_nb_particules(void);

/*!
 * \fn void display_particules(void)
 * \brief Affiche les particules
 */
void display_particules(void);

/*!
 * \fn void particule_force_rendu1(void)
 * \brief Calcule la force à laquelle est soumise la première particule
 *          du fichier. Affiche cette force (sous forme vectorielle)
 *          ainsi que la vitesse et la position calculée après un
 *          instant DELTA_T
 */
void particule_integration_rendu2(void);

/*!
 * \fn void particule_force_rendu1(void)
 * \brief Calcule la force entre deux particules en fonction de la
 * distance qui les sépare.
 */
void particule_force_rendu1(void);

/*!
 * \fn Particule_t* get_part_by_id(int id)
 * \brief Récupére un pointeur sur une particule en donnant son id (sa
 *          place dans la liste contenant les particules).
 * \param id : place de la particule dans la liste contenant les
 *              particules.
 * \return Pointeur sur la particule, ou NULL en cas d'erreur (id trop
 *          grand ou autre)
 */
Particule_t* get_part_by_id(int);

/*!
 * \fn double get_part_rayon(Particule_t* part)
 * \brief Récupére le rayon d'une particule.
 * \param trouNoir : pointeur sur la particule dont on veut récupérer
 *                   le rayon.
 * \return Rayon de la particule
 */
double get_part_rayon(Particule_t*);

/*!
 * \fn double get_part_posx(Particule_t* part)
 * \brief Récupére la position en x d'une particule.
 * \param trouNoir : pointeur sur la particule dont on veut récupérer
 *                   la position.
 * \return Position en x de la particule
 */
double get_part_posx(Particule_t*);

/*!
 * \fn double get_part_posy(Particule_t* part)
 * \brief Récupére la position en y d'une particule.
 * \param trouNoir : pointeur sur la particule dont on veut récupérer
 *                   la position.
 * \return Position en y de la particule
 */
double get_part_posy(Particule_t*);

/*!
 * \fn double get_part_vx(Particule_t* part)
 * \brief Récupére la vitesse en x d'une particule.
 * \param trouNoir : pointeur sur la particule dont on veut récupérer
 *                   la vitesse.
 * \return Vitesse en x de la particule
 */
double get_part_vx(Particule_t*);

/*!
 * \fn double get_part_vy(Particule_t* part)
 * \brief Récupére la vitesse en y d'une particule.
 * \param trouNoir : pointeur sur la particule dont on veut récupérer
 *                   la vitesse.
 * \return Vitesse en y de la particule
 */
double get_part_vy(Particule_t*);

Particule_t* update_particule(Particule_t*, Particule_t*, double, double);

void delete_part(Particule_t*, Particule_t*);

void delete_part_by_id(int);

void set_ptrParticules(Particule_t*);

void add_particule(double, double, double, double, double);

void set_part_next(Particule_t*, Particule_t*);

void set_part_pos(Particule_t*, double, double);

#ifndef OLDCODE
void update_cache_part(void);
#endif

#endif

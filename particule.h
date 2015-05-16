/*!
 * \file particule.h
 * \brief (HEADER) Module de gestion des entités particules
 * \date 17.05.2015
 * \version 3
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

/*!
 * \fn  Particule_t* update_particule(Particule_t* part0,
 *                                      Particule_t* parent,
 *                                      double force0x,
 *                                      double force0y)
 * \brief Met à jour la particule passée comme premier paramètre d'un
 *          pas de temps DELTA_T (ou dt si REALTIME) en lui appliquant
 *          comme force de base le vecteur force0.
 * \param   part0 : particule à mettre à jour.
 *          parent : parent de la particule à mettre à jour (dans la
 *                  liste chaînée)
 *          force0x : composante x de la force de base à appliquer à la
 *                    particule (force0)
 *          force0y : composante y du vecteur force0
 * \return Pointeur sur la particule mise à jour.
 */
Particule_t* update_particule(Particule_t*, Particule_t*,\
                                double, double);

/*!
 * \fn  void delete_part(Particule_t* part, Particule_t* parent)
 * \brief Efface une particule.
 * \param   part : particule à effacer
 *          parent : parent de la particule à effacer (dans la
 *                  liste chaînée)
 */
void delete_part(Particule_t*, Particule_t*);

/*!
 * \fn void delete_part_by_id(int id)
 * \brief   Efface la particule sélectionnée par son identifiant.
 * \param   id : identifiant de la particule (compris entre 0 et
 *          nbParticules - 1).
 */
void delete_part_by_id(int);

/*!
 * \fn void set_ptrParticules(Particule_t* ptr)
 * \brief   Redéfinis le pointeur conservant le début de la liste des
 *          particules.
 * \param   ptr : pointeur sur le premier élément de la liste.
 */
void set_ptrParticules(Particule_t*);

/*!
 * \fn  void add_particule(double rayon, double x, double y,
                     double vx, double vy)
 * \brief Ajoute une particule.
 * \param   rayon : rayon de la particule
 *          x : coordonnée x de la particule
 *          y : coordonnée y de la particule
 *          vx : composante x de la vitesse de la particule
 *          vy : composante y de la vitesse de la particule
 */
void add_particule(double, double, double, double, double);


/*!
 * \fn  void set_part_next(Particule_t* part, Particule_t* next)
 * \brief Modifie le champs next d'une particule
 * \param   part : particule à modifier
 *          next : pointeur à sotcker dans le champs next
 */
void set_part_next(Particule_t*, Particule_t*);

/*!
 * \fn  void set_part_pos(Particule_t* part, double x, double y)
 * \brief Modifie le champs pos d'une particule
 * \param   part : particule à modifier
 *          x : position en x
 *          y : position en y
 */
void set_part_pos(Particule_t*, double, double);

#endif

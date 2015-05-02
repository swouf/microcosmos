/*!
 * \file graphic.h
 * \brief (HEADER) Module de dessin et de gestion de la fenêtre de la
 * 				   simulation
 * \date 19.04.2015
 * \version 2
 * \author Minh Truong & Jérémy Jayet
 */

/*!
 * \fn void fenetre_sim (void)
 * \brief Créé la fenêtre de simulation
 */
void fenetre_sim (void);

/*!
 * \fn void draw_particule (double posx, double posy, double r, double v)
 * \brief Dessine une particule
 * \param 	posx: position x d'une particule,
 * 			posy: position y d'une particule,
 * 			r: rayon d'une particule,
 * 			v: vitesse d'une particule.
 */
void draw_particule (double posx, double posy, double r, double v);

/*!
 * \fn void draw_generateur(double posx, double posy, double vpix,
 * 							double vpiy)
 * \brief Dessine un générateur
 * \param	posx: position x d'un générateur
 * 			posy: position y d'un générateur
 * 			vpix: vitesse initiale x des particules éjectées
 * 			vpiy: vitesse initiale y des particules éjectées
 */
void draw_generateur(double posx, double posy, double vpix, double vpiy);

/*!
 * \fn void draw_trou_noir(double posx, double posy)
 * \brief Dessine un trou noir
 * \param	posx: position x d'un trou noir
 * 		posy: position y d'un trou noir
 */
void draw_trou_noir(double posx, double posy);

/*!
 * \fn void set_display_model_func(void (*display_model_func)(void))
 * \brief 	Définit la fonction de callback qui dessine le modèle de la
 * 			simulation
 * \param void (*display_model_func)(void): pointeur sur la fonction
 * 											 de callback
 */
void set_display_model_func(void (*display_model_func)(void));

void set_idle_model_func(void (*idle_model_func)(void));

/*!
 * \fn void affichage(void)
 * \brief Affiche la simulation
 */
void affichage(void);

/*!
 * \fn void reshape(int w, int h)
 * \brief 	Modifie l'aspect_ration et le viewport lorsque la taille de
 * 		la fenêtre change
 * \param 	w: largeur de la fenêtre
 * 			h:hauteur de la fenêtre
 */
void reshape(int, int);

/*!
 * \fn void initGL(int argc, char** argv)
 * \brief 	Initialise OpenGL
 * \param 	argc: nombre d'arguments passés au programme
 * 			argv: tableau contenant les arguments
 */
void initGL(int, char**);
/*!
 * \fn void idle(void)
 * \brief 	Rafraîchit l'affichage
 */
void idle(int);

/*!
 * \fn graphic_draw_segment (float x1, float y1, float x2, float y2)
 * \brief 	Dessine un segment
 * \param 	x1: coordonnée x du premier point
 * 			y1: coordonnée y du premier point
 * 			x2: coordonnée x du deuxième point
 * 			y2: coordonnée y du deuxième point
 */
void graphic_draw_segment (float, float, float, float);

/*!
 * \fn set_projection_limits(	float xMax, float xMin, float yMax,
 * 							float yMin)
 * \brief 	Définit les limites de la projection
 * \param 	xMax: la plus grande coordonnée sur l'axe x
 * 			xMin: la plus petite coordonnée sur l'axe x
			yMax: la plus grande coordonnée sur l'axe y
 * 			yMin: la plus petite coordonnée sur l'axe y
 */
  void set_projection_limits(float, float, float, float);

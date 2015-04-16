/*!
 * \file graphic.h
 * \brief Module de gestion de la simulation
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

void fenetre_sim (int argc, char **argv);
void draw_particule (double posx, double posy, double r, double v);
void draw_generateur(double posx, double posy, double vx, double vy);
void draw_trou_noir(double posx, double posy);
void set_display_model_func(void (*display_model_func)(void));
void affichage(void);

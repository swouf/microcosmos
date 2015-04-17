/*!
 * \file graphic.h
 * \brief Module de gestion de la simulation
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */

void fenetre_sim (void);
void draw_particule (double posx, double posy, double r, double v);
void draw_generateur(double posx, double posy, double vpix, double vpiy);
void draw_trou_noir(double posx, double posy);
void set_display_model_func(void (*display_model_func)(void));
void affichage(void);
void reshape(int, int);
void initGL(int, char**);
void idle(void);
void graphic_draw_segment (float, float, float, float);
void set_projection_limits(float, float, float, float);

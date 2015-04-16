/*!
 * \file graphic.c
 * \brief Module de gestion de la simulation
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "graphic.h"
#include "constantes.h"

#define WIDTH_DEF   600
#define HEIGHT_DEF  300

static const double PI = 3.14159265358979323846;

static void    (*display_model)(void);
static GLfloat aspect_ratio = (GLfloat)WIDTH_DEF/(GLfloat)HEIGHT_DEF;
static int     width        = WIDTH_DEF;
static int     height       = HEIGHT_DEF;
static int     sim_window   = 0;

static void reshape(int w, int h);

void fenetre_sim (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(WIDTH_DEF, HEIGHT_DEF);
	
	sim_window = glutCreateWindow("Microcosmos");
	
	/*Initialisation Open GL*/
	glutDisplayFunc(affichage);
	glutReshapeFunc(reshape);
    
    affichage();
}
void draw_particule (double posx, double posy, double r, double v)
{ 
	int i;
	const int SIDES = 50;
	float rouge, vert, bleu;
	
	//Couleur en fonction de la vitesse
	rouge = v/MAX_VITESSE;
	vert = rouge - 0.8;
	bleu = vert;
	float couleur[3] = {rouge, vert, bleu};
	
	//Dessin du cercle
	glBegin (GL_LINE_LOOP);
	glColor3fv(couleur);   
	for (i=0; i < SIDES; i++)
    {
		float alpha = i * 2. * PI/SIDES;
		glVertex2f(posx + r*cos(alpha), posy + r*sin(alpha));
    }
	glEnd ();
}
void draw_generateur(double posx, double posy, double r, double vx, double vy)
{
	int i;
	const int SIDES = 50;
	
	glBegin (GL_POLYGON);
	
	for (i=0; i < SIDES; i++)
    {
		float alpha = i * 2. * PI/SIDES;
		glVertex2f(posx + r*cos(alpha), posy + r*sin(alpha));
    }  
      
	glEnd();
	
	glBegin(GL_LINES);
	
	glVertex2f (posx, posy);
    glVertex2f (vx+posx, vy+posy);
	
	glEnd();
	//printf("Exécution de draw_generateur avec comme paramètre: %lf, %lf, %lf, %lf\n", posx, posy, vx, vy);
}
void draw_trou_noir(double posx, double posy)
{
	int i;
	const int SIDES = 50;
	
	glBegin (GL_POLYGON);
	//dessin du losange
	glVertex2f (posx + COTE/2, posy);
    glVertex2f (posx, posy + COTE/2);
    glVertex2f (posx - COTE/2, posy);
    glVertex2f (posx, posy - COTE/2);
    
	glEnd();
	
	glBegin (GL_LINE_LOOP);
	
	for (i=0; i < SIDES; i++)
    {
		float alpha = i * 2. * PI/SIDES;
		glVertex2f(posx + RBLACK*cos(alpha), posy + RBLACK*sin(alpha));
    }  
      
	glEnd();
	//printf("Exécution de draw_trounoir avec comme paramètre: %lf, %lf\n", posx, posy);
}
void affichage(void)
{
    glutSetWindow(sim_window);
    
    glViewport(0, 0, width, height);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
	GLfloat gauche = -200, droite = 200, bas = -100, haut = 100;
	glLoadIdentity();
	if(aspect_ratio <= 1)
		glOrtho(gauche, droite, bas/aspect_ratio, haut/aspect_ratio, -1, 1);
	else
		glOrtho(gauche*aspect_ratio, droite*aspect_ratio, bas, haut, -1, 1);

	(*display_model)();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	//glViewport(0, 0, w, h);
    width   = w;
    height  = h;
	aspect_ratio = (GLfloat) w / (GLfloat) h;
	glutPostRedisplay();
}
void set_display_model_func(void (*display_model_func)(void))
{
	display_model = display_model_func;
}


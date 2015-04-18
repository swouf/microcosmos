/*!
 * \file graphic.c
 * \brief Module de dessin et de gestion de la fenêtre de la simulation
 * \date 19.04.2015
 * \version 2
 * \author Minh Truong & Jérémy Jayet
 */
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "graphic.h"
#include "constantes.h"

#define WIDTH_DEF		640
#define HEIGHT_DEF  	360
#define R_COMP_VMAX		1f
#define G_COMP_VMAX		0.2f
#define B_COMP_VMAX		0.2f

static const double PI = 3.14159265358979323846;

static void    		(*display_model)(void);
static GLfloat 		aspect_ratio	= (GLfloat)WIDTH_DEF/(GLfloat)HEIGHT_DEF;
static int     		width			= WIDTH_DEF;
static int     		height			= HEIGHT_DEF;
static int     		sim_window		= 0;
static const int 	COTE			= COTE_DEF;
static const float 	RAYON			= COTE_DEF/2;
static GLfloat 		gauche			= 0;
static GLfloat 		droite			= 0;
static GLfloat 		bas				= 0;
static GLfloat 		haut			= 0;

void initGL(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer
}
void fenetre_sim (void)
{
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(WIDTH_DEF, HEIGHT_DEF);

	sim_window = glutCreateWindow("Microcosmos");

	glutReshapeFunc(reshape);
	glutDisplayFunc(affichage);

    affichage();
}
void draw_particule (double posx, double posy, double r, double v)
{
	int i;
	const int SIDES = 50;
	float rouge, vert, bleu;

	//Couleur en fonction de la vitesse
	rouge = v/MAX_VITESSE;
	vert = (G_COMP_VMAX/MAX_VITESSE)*v;
	bleu = vert;
	float couleur[3] = {rouge, vert, bleu};

	//Dessin du cercle
	glLineWidth(LINE_WIDTH);
	glColor3fv(couleur);
	glBegin (GL_LINE_LOOP);
	for (i=0; i < SIDES; i++)
    {
		float alpha = i * 2. * PI/SIDES;
		glVertex2f(posx + r*cos(alpha), posy + r*sin(alpha));
    }
	glEnd ();
}
void draw_generateur(double posx, double posy, double vpix, double vpiy)
{
	int i;
	const int SIDES = 50;
	float couleur[3] = {0, 0, 1}; //Générateur de couleur bleu.
	float anglePointe = PI/6;
	float vx = L_FLECHE_GEN*vpix/sqrt(pow(vpix, 2)+pow(vpiy, 2));
	float vy = L_FLECHE_GEN*vpiy/sqrt(pow(vpix, 2)+pow(vpiy, 2));
	float angleVecteur = atan2(vy,vx);
	
	glLineWidth(LINE_WIDTH);
	glColor3fv(couleur);
	//dessin du disque
	glBegin (GL_POLYGON);
	
	for (i=0; i < SIDES; i++)
    {
		float alpha = i * 2. * PI/SIDES;
		glVertex2f(posx + RAYON*cos(alpha), posy + RAYON*sin(alpha));
    }
	
	glEnd();

	//dessin du segment
	glBegin(GL_LINES);

	glColor3fv(couleur);
	glVertex2f (posx, posy);
    glVertex2f (vx+posx, vy+posy);

	glEnd();
	//dessin de premier bout de flèche
	glBegin(GL_LINES);

	glVertex2f(	vx+posx-COTE*cos(angleVecteur-anglePointe),
				vy+posy-COTE*sin(angleVecteur-anglePointe));
	glVertex2f(vx+posx, vy+posy);

	glEnd();

	//dessin du deuxième bout de flèche
	glBegin(GL_LINES);

	glVertex2f(	vx+posx-COTE*cos(angleVecteur+anglePointe),
				vy+posy-COTE*sin(angleVecteur+anglePointe));
	glVertex2f(vx+posx, vy+posy);

	glEnd();
}
void draw_trou_noir(double posx, double posy)
{
	int i;
	const int SIDES = 100;
	float couleur[3] = {0, 1, 0};

	glBegin (GL_POLYGON);

	glColor3fv(couleur);
	//dessin du losange
	glVertex2f (posx + COTE/2, posy);
    glVertex2f (posx, posy + COTE/2);
    glVertex2f (posx - COTE/2, posy);
    glVertex2f (posx, posy - COTE/2);

	glEnd();

	//dessin des traitstillés
	glLineWidth(LINE_WIDTH);
	for (i=0; i < SIDES; i+=2)
    {
		double x1 = posx + RBLACK*cos(i * 2. * PI/SIDES);
		double y1 = posy + RBLACK*sin(i * 2. * PI/SIDES);
		double x2 = posx + RBLACK*cos((i+1) * 2. * PI/SIDES);
		double y2 = posy + RBLACK*sin((i+1) * 2. * PI/SIDES);
		graphic_draw_segment (x1, y1, x2, y2);
    }
}
void graphic_draw_segment (float x1,
                           float y1,
                           float x2,
                           float y2)

{
    glBegin (GL_LINES);

    glVertex2f (x1, y1);
    glVertex2f (x2, y2);

    glEnd ();
}
void affichage(void)
{
    if(sim_window)
		glutSetWindow(sim_window);
	else
		return;

    glViewport(0, 0, width, height);
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

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
void idle(void)
{
	//printf("Fonction idle (module graphic)\n");
}
void set_projection_limits(float xMax, float xMin, float yMax, float yMin)
{
	float diff = abs(xMax-xMin) - abs(yMax-yMin);

	if(diff > 0)
	{
		yMax += diff/2;
		yMin -= diff/2;
	}
	else if(diff < 0)
	{
		xMax -= diff/2;
		xMin += diff/2;
	}

	gauche	= xMin-RMAX;
	droite	= xMax+RMAX;
	bas		= yMin-RMAX;
	haut	= yMax+RMAX;
}

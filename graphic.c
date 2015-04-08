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

static const double PI = 3.14159265358979323846;

void fenetre_sim (int argc, char **argv)
{
	//float aspect_ratio;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(250, 250);
	//aspect_ratio = (GLfloat)250/ (GLfloat)250;
	
	glutCreateWindow("Microcosmos");
	
	/*Initialisation Open GL*/
	glClearColor(1, 1, 1, 0);	
}
void draw_particule (double posx, double posy, double r, double v)
{ 
	int i;
	const int SIDES = 50;
	float rouge, bleu;
	
	//Couleur en fonction de la vitesse
	rouge = v/MAX_VITESSE;
	bleu = 1 - rouge;
	float couleur[3] = {rouge, 0, bleu};
	
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
void draw_generateur(double posx, double posy, double vx, double vy)
{
	printf("Exécution de draw_generateur avec comme paramètre: %lf, %lf, %lf, %lf\n", posx, posy, vx, vy);
}
void draw_trounoir(double posx, double posy)
{
	printf("Exécution de draw_trounoir avec comme paramètre: %lf, %lf\n", posx, posy);
}


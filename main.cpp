/*!
 * \file main.cpp
 * \brief Fichier main du projet
 * \date 15.03.2015
 * \version 1
 * \author Minh Truong & Jérémy Jayet
 */
 
#include <iostream>
#include <cstdlib>
#include <string>
#include <GL/glut.h>
#include <GL/glui.h>
extern "C"
{
	#include "sim.h"
	#include "error.h"
}

//rapport largeur/hauteur de la fenêtre utilisée pour le dessin
static GLfloat aspect_ratio; //avec namespace non nommé en C++

void load_gui(int argc, char **argv);

int main(int argc, char **argv)
{
	load_gui(argc, argv);
		
	if(argc != 3)
	{
		char msg[100] = "Nombre de paramètres invalides.\n";
		error_msg(msg);
	}
	else
	{
		if (std::string(argv[1]) == "Error")
		{
			if(sim_lecture(argv[2], ERROR))
				return 1;
		}
		else if(std::string(argv[1]) == "Force")
		{
			if(sim_lecture(argv[2], FORCE))
				return 1;
		}
		else
			return 1;
	}
	
	return 0;
}

void load_gui (int argc, char **argv)
{
	float aspect_ratio;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //double buffer
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(250, 250);
	aspect_ratio = (GLfloat)250/ (GLfloat)250;
	
	glutCreateWindow("Microcosmos");
	
	/*Initialisation Open GL*/
	glClearColor(1, 1, 1, 0);
	
	/*widgets GLUI*/
	GLUI *glui = GLUI_Master.create_glui((char*) "GLUI");
	//button
	glui->add_button((char*) "Quit", 0, (GLUI_Update_CB)exit);
	
	/*Entrée dans la boucle principale de glut*/
	glutMainLoop();
}

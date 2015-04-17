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
	#include "graphic.h"
}
namespace
{
	GLUI			*glui;
	GLUI_EditText	*edittextload;
	GLUI_EditText	*edittextsave;
	GLUI_EditText	*edittextpart;
	GLUI_EditText	*edittextgen;
	GLUI_EditText	*edittexttrou;
}

typedef enum GLUI_ID
{
	EDITTEXTLOAD_ID,
	EDITTEXTSAVE_ID,
	EDITTEXTPART_ID,
	EDITTEXTGEN_ID,
	EDITTEXTTROU_ID,
	LOADBUTTON_ID,
	SAVEBUTTON_ID
} GLUI_ID;

void load_gui(void);
void glui_idle(void);

void control_cb(int control)
{
	switch(control)
	{
		case (LOADBUTTON_ID):
			sim_clean();
			printf("%s\n", edittextload->get_text());
            if(sim_lecture(edittextload->get_text()))
                break;
            affichage();
			break;
		case (SAVEBUTTON_ID):
            std::cout << "On s'enjaille ma gueule !!! " << edittextsave->get_text() << std::endl;
		    sim_ecriture(edittextsave->get_text());
			break;
	}
}
//rapport largeur/hauteur de la fenêtre utilisée pour le dessin
//static GLfloat aspect_ratio; //avec namespace non nommé en C++

int main(int argc, char **argv)
{
	if(argc == 3)
	{
		if (std::string(argv[1]) == "Error")
		{
			if(sim_lecture(argv[2]))
				return 1;
            else
            {
                error_success();
                return 0;
            }
		}
		else if(std::string(argv[1]) == "Force")
		{
			if(sim_lecture(argv[2]))
				return 1;
            else
            {
                force();
                return 0;
            }
		}
        else if(std::string(argv[1]) == "Integration")
        {
            if(sim_lecture(argv[2]))
                return 1;
            else
            {
                integration();
                return 0;
            }
        }
		else
        {
            error_msg("Paramètres invalides.");
        }
			return 1;
	}
    else if(argc == 2)
    {
        sim_lecture(argv[1]);
    }
    else if(argc > 3)
    {
        error_msg("Nombre de paramètres invalides.");
    }

    printf("Paramètrage de sim_display()\n");
    set_display_model_func(sim_display);
    printf("Paramètrage de sim_display() TERMINÉ\n");

	initGL(argc, argv);
	fenetre_sim();
	load_gui();

	sim_clean();

	return 0;
}

void load_gui(void)
{
	/*widgets GLUI*/
	//Pannel File
	glui = GLUI_Master.create_glui("Microcosmos GUI");

	GLUI_Panel *file_panel = glui->add_panel("File");

	edittextload = glui->add_edittext_to_panel(file_panel,"FileName: ", GLUI_EDITTEXT_TEXT, NULL, EDITTEXTLOAD_ID, control_cb);

	glui->add_button_to_panel(file_panel,"Load", LOADBUTTON_ID, control_cb);

	edittextsave = glui->add_edittext_to_panel(file_panel,"FileName: ", GLUI_EDITTEXT_TEXT, NULL, EDITTEXTSAVE_ID, control_cb);

	glui->add_button_to_panel(file_panel, "Save", SAVEBUTTON_ID, control_cb);

	//Panel Simulation
	GLUI_Panel *simulation_panel = glui->add_panel("Simulation");

	glui->add_button_to_panel(simulation_panel,"Start");

	glui->add_button_to_panel(simulation_panel,"Step");

	//Panel Information
	GLUI_Panel *information_panel = glui->add_panel("Information");

	edittextpart = glui->add_edittext_to_panel(information_panel, "Nb Particule: ", GLUI_EDITTEXT_TEXT, NULL, EDITTEXTPART_ID, control_cb);

	edittextgen = glui->add_edittext_to_panel(information_panel, "Nb Generateur: ", GLUI_EDITTEXT_TEXT, NULL, EDITTEXTGEN_ID, control_cb);

	edittexttrou = glui->add_edittext_to_panel(information_panel, "Nb Trou noir: ", GLUI_EDITTEXT_TEXT, NULL, EDITTEXTTROU_ID, control_cb);

	//button
	glui->add_button((char*) "Exit", 0, (GLUI_Update_CB)exit);

	/*Entrée dans la boucle principale de glut*/

	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutIdleFunc(glui_idle);
	GLUI_Master.set_glutDisplayFunc(affichage);

	glutMainLoop();
}
void glui_idle(void)
{
	int** ptrNbEntite = get_3ptr_nb_entite();

	edittextpart->set_int_val(*ptrNbEntite[0]);
	edittextgen->set_int_val(*ptrNbEntite[1]);
	edittexttrou->set_int_val(*ptrNbEntite[2]);

	idle();
}

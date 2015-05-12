/*!
 * \file main.cpp
 * \brief Fichier main du projet
 * \date 29.04.2015
 * \version 2
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
	GLUI_Button		*startButton;
}

typedef enum GLUI_ID
{
	EDITTEXTLOAD_ID,
	EDITTEXTSAVE_ID,
	EDITTEXTPART_ID,
	EDITTEXTGEN_ID,
	EDITTEXTTROU_ID,
	LOADBUTTON_ID,
	SAVEBUTTON_ID,
	STARTBUTTON_ID,
	STEPBUTTON_ID
} GLUI_ID;

void load_gui(char*);
void glui_idle(void);

void control_cb(int control)
{
	static int isStarted = 0;
	switch(control)
	{
		case (LOADBUTTON_ID):
			sim_clean();
            if(sim_lecture(edittextload->get_text()))
                break;
            affichage();
			break;
		case (SAVEBUTTON_ID):
		    sim_ecriture(edittextsave->get_text());
			break;
		case (STARTBUTTON_ID):
			if(isStarted)
			{
				isStarted = 0;
				startButton->set_name("Start");
			}
			else
			{
				isStarted = 1;
				startButton->set_name("Stop");
			}
			start();
			break;
		case (STEPBUTTON_ID):
			step();
			break;
	}
}
//rapport largeur/hauteur de la fenêtre utilisée pour le dessin
//static GLfloat aspect_ratio; //avec namespace non nommé en C++

int main(int argc, char **argv)
{
	initGL(argc, argv);
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
		else if(std::string(argv[1]) == "Graphic")
        {
            if(sim_lecture(argv[2]))
                return 1;
            else
				load_gui(argv[2]);
        }
		else
            error_msg((char*)"Paramètres invalides.");
	}
    else if(argc == 2)
    {
        if(sim_lecture(argv[1]))
			return 1;
		else
			load_gui(argv[1]);
    }
    else if(argc > 3)
        error_msg((char*)"Nombre de paramètres invalides.");
	else
		load_gui((char*)"");


    set_display_model_func(sim_display);
	set_idle_model_func(sim_update);
	set_keyboard_model_func(sim_keyboard);
	set_mouse_model_release_func(sim_mouse_release);
	set_mouse_model_press_func(sim_mouse_press);
	fenetre_sim();
	glutMainLoop();
	sim_clean();
	return 0;
}
void load_gui(char* nomFichier)
{
	/*widgets GLUI*/
	//Pannel File
	glui = GLUI_Master.create_glui("Microcosmos");

	GLUI_Panel *file_panel = glui->add_panel("File");

	edittextload = glui->add_edittext_to_panel(file_panel,"FileName: ",\
												GLUI_EDITTEXT_TEXT,\
												NULL, EDITTEXTLOAD_ID,\
												control_cb);
	edittextload->set_text(nomFichier);

	glui->add_button_to_panel(file_panel,"Load", LOADBUTTON_ID,\
								control_cb);

	edittextsave = glui->add_edittext_to_panel(file_panel,"FileName: ",\
												GLUI_EDITTEXT_TEXT,\
												NULL, EDITTEXTSAVE_ID,\
												control_cb);
	edittextsave->set_text("save.txt");

	glui->add_button_to_panel(file_panel, "Save", SAVEBUTTON_ID,\
								control_cb);

	//Panel Simulation
	GLUI_Panel *simulation_panel = glui->add_panel("Simulation");

	startButton = glui->add_button_to_panel(simulation_panel,"Start", STARTBUTTON_ID,\
								control_cb);

	glui->add_button_to_panel(simulation_panel,"Step", STEPBUTTON_ID,\
								control_cb);

	//Panel Information
	GLUI_Panel *information_panel = glui->add_panel("Information");

	edittextpart = glui->add_edittext_to_panel(information_panel,\
												"Nb Particule: ",\
												GLUI_EDITTEXT_TEXT,\
												NULL, EDITTEXTPART_ID,\
												control_cb);

	edittextgen = glui->add_edittext_to_panel(information_panel,\
												"Nb Generateur: ",\
												GLUI_EDITTEXT_TEXT,\
												NULL, EDITTEXTGEN_ID,\
												control_cb);

	edittexttrou = glui->add_edittext_to_panel(information_panel,\
												"Nb Trou noir: ",\
												GLUI_EDITTEXT_TEXT,\
												NULL, EDITTEXTTROU_ID,\
												control_cb);

	//button
	glui->add_button((char*) "Exit", 0, (GLUI_Update_CB)exit);

	GLUI_Master.set_glutIdleFunc(glui_idle);
}
void glui_idle(void)
{
	int* ptrNbEntite = get_3nb_entite();

	edittextpart->set_int_val(ptrNbEntite[0]);
	edittextgen->set_int_val(ptrNbEntite[1]);
	edittexttrou->set_int_val(ptrNbEntite[2]);

}

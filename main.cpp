/*! \file main.cpp
 * \brief Fichier main du projet
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */
 
#include <iostream>
#include <cstdlib>
#include <string>

extern "C"
{
	#include "sim.h"
	#include "error.h"
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		char msg[100] = "Nombre de paramètres invalides.\n";
		error_msg(msg);
	}
	else
	{
		if (strcmp(argv[1]), "Error"))
			sim_lecture(argv[2]);
		else if(strcmp(argv[1], "Force"))
			std::cout << "Do something." << std::endl;
		else
			std::cout << "Don't do something." << std::endl;
	}
	
	
	
	return 0;
}

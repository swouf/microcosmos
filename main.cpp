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
	#ifdef DEBUG
	std::cout << "\033\[1;31m ***MODE DEBUG ACTIVÉ***\
				  \033\[0m" << std::endl;
	#endif
	
	if(argc != 3)
	{
		char msg[100] = "Nombre de paramètres invalides.\n";
		error_msg(msg);
	}
	else
	{
		if (std::string(argv[1]) == "Error")
		{
			if(sim_lecture(argv[2]))
				return 1;
		}
		else if(std::string(argv[1]) == "Force")
			std::cout << "Do something." << std::endl;
		else
			std::cout << "Don't do something." << std::endl;
	}
	
	return 0;
}

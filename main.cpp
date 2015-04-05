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
        else if(std::string(argv[1]) == "Integration")
        {
            if(sim_lecture(argv[2], INTEGRATION))
                return 1;
        }
		else
			return 1;
	}
	
	return 0;
}

/*! \file main.cpp
 * \brief Fichier main du projet
 * \date
 * \version 0.1
 * \author Minh Truong & Jérémy Jayet
 */
#include <iostream>
#include <cstdlib>

extern "C"
{
	#include "sim.h"
	#include "error.h"
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		error_msg("Nombre de paramètres invalides.\n");
	}
	
	
	
	return 0;
}

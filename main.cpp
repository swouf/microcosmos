#include <iostream>

extern "C"
{
	#include "sim.h"
	#include "error.h"
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		error_msg("Nombre de paramètres invalides.\n \
					")
	}
	
	
	
	return 0;
}

#ifndef GENERATEUR_H
#define GENERATEUR_H
typedef struct Generateur
{
	float rgen;
	float posx;
	float posy;
	float vpi_x;
	float vpi_y;
} Generateur_t;

Generateur_t** string_parsing_generateur(char* lignes[], int nbLignes);
#endif

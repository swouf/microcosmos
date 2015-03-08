#ifndef TROUNOIR_H
#define TROUNOIR_H
typedef struct Trounoir
{
	float posx;
	float posy;
} Trounoir_t;

Trounoir_t** string_parsing_trou_noir(char* lignes[], int nbLignes);
#endif

/* Nom: error.c
 * Description: module qui gère les messages d'erreur. NE PAS MODIFIER.
 * Date: 04.02.2014
 * version : 1.1
 * auteur : PROG II
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// chaînes prédéfinies pour composer les messages d'erreur

const static char nom_orig[][20]={"generateur","trou noir","particule"};
const static char nom_type[][20]={"trop","pas assez"};

//---------------------------------------------------------------------
// utilisable pour afficher des messages d'erreurs qui ne font pas
// partie de la liste des erreurs testées pour le rendu1
void error_msg(char* msg)
{
	printf("erreur : %s\n", msg);
	exit(EXIT_FAILURE);
}

//---------------------------------------------------------------------
// Erreurs testées en mode Error pour le rendu1 (et les rendus suivants)
//   ----> le paramètre indice commence à zéro 

//---------------------------------------------------------------------
// A appeler pour le rendu1 en mode Error en cas d'absence d'erreur
void error_success(void)
{
	printf("Fichier correct\n");
}

//---------------------------------------------------------------------
// impossible d'ouvrir le fichier, fichier inexistant
void error_fichier_inexistant(void)
{
	printf("Erreur : Fichier inexistant\n");
}

//---------------------------------------------------------------------
// si la lecture d'une ligne du fichier échoue (on reçoit EOF) 
// alors que la lecture des entités n'est pas terminée
void error_fichier_incomplet(void)
{
	printf("Erreur : Fichier incomplet (EOF inattendu)\n");
}

//---------------------------------------------------------------------
// vitesse de particule trop grande / pour generateur ou particule
void error_vitesse_partic(ERREUR_ORIG origine, int indice)
{
	printf("Erreur : vitesse de %s d'indice %d dépasse MAX_VITESSE\n", 
		   nom_orig[origine], indice);
}

//---------------------------------------------------------------------
// rayon de particule incorrect / pour generateur ou particule										 
void error_rayon_partic(ERREUR_ORIG origine, int indice)
{
	printf("Erreur : rayon de %s d'indice %d n'est pas compris entre "
		   "RMIN et RMAX\n", nom_orig[origine], indice);
}

//---------------------------------------------------------------------
// échec lecture du nombre d'élément: particule, trou noir, generateur
void error_lect_nb_elements(ERREUR_ORIG origine)
{
	printf("Erreur : lecture du nb de %s\n", nom_orig[origine]);
}

//---------------------------------------------------------------------
// échec de la lecture des paramètres : trop, pas assez, ou syntaxe
void error_lecture_elements(ERREUR_ORIG origine, ERREUR_TYPE type)
{
	printf("Erreur : lecture de %s : %s ou erreur de syntaxe\n", 
		   nom_orig[origine], nom_type[type]);
}



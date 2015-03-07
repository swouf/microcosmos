/* Nom: error.h
 * Description: module qui gère les messages d'erreur. NE PAS MODIFIER
 * Date: 04.02.2014
 * version : 1.1
 * auteur : PROG II
 */

#ifndef ERROR_H
#define ERROR_H

//---------------------------------------------------------------------
// ces déclarations combinent deux outils du langage C : enum et typedef
// enum : déclare une liste de symboles équivalents à des entiers
//        le premier symbole vaut 0, le suivant vaut 1, etc...
// typedef : the nom de type rend le code plus lisible

//---------------------------------------------------------------------
// liste des symboles à utiliser pour appeler les fonctions d'erreur 
// selon l'entité qui produit l'erreur: générateur, trou noir, particule
typedef enum ErreurOrig {
	ERR_GENERAT, ERR_TROU_N, ERR_PARTIC 
} ERREUR_ORIG;

//---------------------------------------------------------------------
// liste des symboles à utiliser pour appeler les fonctions d'erreur 
// pour les cas où on a trop ou pas assez d'entité dans la liste
typedef enum ErreurType {
	ERR_TROP, ERR_PAS_ASSEZ 
} ERREUR_TYPE;

// exemple d'appel: echec de la lecture des paramètres d'une particule
// le symbole ERR_PAS_ASSEZ est aussi utilisé en cas d'erreur de syntaxe
// car le programme ne peut pas faire la différence entre les deux cas.
//
// error_lecture_elements(ERR_PARTIC , ERR_PAS_ASSEZ)

//---------------------------------------------------------------------
// cette fonction est utilisable pour afficher des messages d'erreurs 
// qui ne font pas partie de la liste des erreurs testées pour le rendu1
void error_msg(char* msg);

//---------------------------------------------------------------------
// Erreurs testées en mode Error pour le rendu1 (et les rendus suivants)
//   ----> le paramètre indice commence à zéro 

//---------------------------------------------------------------------
// A appeler pour le rendu1 en mode Error en cas d'absence d'erreur
void error_success(void);

//---------------------------------------------------------------------
// impossible d'ouvrir le fichier, fichier inexistant
void error_fichier_inexistant(void);

//---------------------------------------------------------------------
// si la lecture d'une ligne du fichier échoue (on reçoit EOF) 
// alors que la lecture des entités n'est pas terminée
void error_fichier_incomplet(void);

//---------------------------------------------------------------------
// vitesse de particule trop grande / pour generateur ou particule
void error_vitesse_partic(ERREUR_ORIG origine, int indice);

//---------------------------------------------------------------------
// rayon de particule incorrect / pour generateur ou particule										 
void error_rayon_partic(ERREUR_ORIG origine, int indice);

//---------------------------------------------------------------------
// échec lecture du nombre d'élément: particule, trou noir, generateur
void error_lect_nb_elements(ERREUR_ORIG origine);

//---------------------------------------------------------------------
// échec de la lecture des paramètres : trop, pas assez ou syntaxe
void error_lecture_elements(ERREUR_ORIG origine, ERREUR_TYPE type);

#endif


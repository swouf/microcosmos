#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <math.h>

#include "../constantes.h"

void print_help(void);
void generate(int, int, int, FILE*);
void generate_random(FILE* fichier);

const double PI = 3.141592653589793238463;

int main(int argc, char** argv)
{
    FILE* fichier = NULL;
    int nbGenerateur = 0;
    int nbTrouNoir = 0;
    int nbParticule = 0;
    
    printf("It WORKS !!!\n argc = %d\n", argc);
    
    for(int i=0;i<argc;i++)
    {
        printf("argv[%d] : %s\n", i, argv[i]);
    }
    
    if(argc > 1)
    {
        printf("2 It WORKS !!!\n");
        if(0==1)
        {
            if(argc >= 3)
                fichier = fopen(argv[2],"w");
            if(!fichier)
                print_help();
            
            generate_random(fichier);
        }
        else if(argc = 5)
        {
            char* p = NULL;
            char** pp = &p;
            
            printf("3 It WORKS !!!\n");
            
            nbGenerateur = strtoul(argv[1], &p, 10);
            
            printf("3.1 It WORKS !!!\n");
            
            nbTrouNoir = strtoul(argv[2], &p, 10);
            
            printf("3.2 It WORKS !!!\n");
            
            nbParticule = strtoul(argv[3], &p, 10);
            
            printf("3.3 It WORKS !!!\n");
            
            fichier = fopen(argv[4],"w");
            if(!fichier)
                print_help();
            
            printf("3.4 It WORKS !!! Opening file : %s\n", argv[4]);
            
            generate(nbGenerateur, nbTrouNoir, nbParticule, fichier);
        }
        else
            print_help();
    }
    else
    {
        print_help();
    }
    
    fclose(fichier);
}

void print_help(void)
{
    printf("Manuel d'utilisation :\n");
    
    exit(0);
}
void generate(int nbGenerateur, int nbTrouNoir, int nbParticule, FILE* fichier)
{
    long double* y = malloc(1024*sizeof(long double));
    if(!y)
        printf("Allocation échouée...");
    srand(5743657854336);
    
    printf("4 It WORKS !!!\n");
    
    for(int i=0;i<=72;i++)
        fprintf(fichier, "#");
        
    fprintf(fichier, "\n# Ce fichier a été généré automatiquement par l'outil generateur_test.\n");
    
    for(int i=0;i<=72;i++)
        fprintf(fichier, "#");
    
    fprintf(fichier, "\n");
        
    float rayon = 0;
    float posx = 0;
    float posy = 0;
    float vx = 0;
    float vy = 0;
    double v = 0;
    
    double phi = 0;
    
    printf("5 It WORKS !!!\n");
    
/*--------------------------------------------------------------------*/
/*------------------ GENERATEUR --------------------------------------*/
    fprintf(fichier, "%d\n", nbGenerateur);
    for(int i=0;i<=nbGenerateur;i++)
    {
        rayon = ((rand()/RAND_MAX)-0.5)*2*(RMAX-RMIN) + RMIN;
        posx = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        posy = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        
        v = (rand()/RAND_MAX)*MAX_VITESSE;
        
        phi = (rand()/RAND_MAX)*2*PI;
        
        vx = cos(phi)*v;
        vy = sin(phi)*v;
        
        fprintf(fichier, "%8.3f %8.3f %8.3f %8.3f %8.3f\n",
                rayon,
                posx,
                posy,
                vx,
                vy);
    }
    fprintf(fichier, "FIN_LISTE\n\n");
    
    printf("6 It WORKS !!!\n");
    
    fflush(fichier);
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*------------------- TROU NOIR --------------------------------------*/
    fprintf(fichier, "%d\n", nbTrouNoir);
    for(int i=0;i<=nbTrouNoir;i++)
    {
        posx = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        posy = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        
        fprintf(fichier, "%8.3f %8.3f\n", posx, posy);
    }
    fprintf(fichier, "FIN_LISTE\n\n");
    
    printf("7 It WORKS !!!\n");
    
    fflush(fichier);
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*------------------- PARTICULE --------------------------------------*/
    fprintf(fichier, "%d\n", nbParticule);
    for(int i=0;i<=nbParticule;i++)
    {
        rayon = ((rand()/RAND_MAX)-0.5)*2*(RMAX-RMIN) + RMIN;
        posx = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        posy = ((rand()/RAND_MAX)-0.5)*4*RMAX;
        
        v = (rand()/RAND_MAX)*MAX_VITESSE;
        
        phi = (rand()/RAND_MAX)*2*PI;
        
        vx = cos(phi)*v;
        vy = sin(phi)*v;
        
        fprintf(fichier, "%8.3f %8.3f %8.3f %8.3f %8.3f\n",
                rayon,
                posx,
                posy,
                vx,
                vy);
    }
    fprintf(fichier, "FIN_LISTE\n\n");
    
    printf("8 It WORKS !!!\n");
/*--------------------------------------------------------------------*/
    
    fclose(fichier);
}
void generate_random(FILE* fichier)
{
    printf("Calling generate_random()...\n");
    generate(0,0,0,fichier);
}

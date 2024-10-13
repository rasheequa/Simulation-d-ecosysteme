#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
// on a modifié les parametres pour observer l'evolution dans l'ecosysteme
float p_ch_dir=0.5;
float p_reproduce_proie=0.150;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-25;
int energie = 10;
int energie_pre = 20;

int main(void) {
  
  //Part 2:

  int i = 0;  
  unsigned int tabProies[200];
  unsigned int tabPred[200];
  for(int i = 0 ; i < 200 ; i++){
    tabProies[i] = 0;
    tabPred[i] = 0;
  }
  
  /*
  Animal *liste_animal = NULL;
  Animal *an = creer_animal(0,10, energie);
  liste_animal = ajouter_en_tete_animal(liste_animal, an);

  printf("exercice 4, questions 2 et 4\n");

    while(i<8){
    bouger_animaux(liste_animal);
    reproduce(&liste_animal,1);
    bouger_animaux(liste_animal);
    afficher_ecosys(liste_animal,NULL);
    bouger_animaux(liste_animal);
    i++;
  }

  liberer_liste_animaux(liste_animal);
 */
  printf("exercice 5, questions 2 et 4\n");

  Animal *liste_proie = NULL;
  srand(time(NULL));

  for(int k = 0 ; k<20 ; k++){
    int x = rand()%20;
    int y = rand()%50;
    ajouter_animal(x,y, energie, &liste_proie);
  }

  int iteration = 0;
  int monde[SIZE_X][SIZE_Y];

  /*while (iteration < 200 && liste_proie != NULL) {
    rafraichir_proies(&liste_proie,monde);
    afficher_ecosys(NULL,liste_proie);
    usleep(T_WAIT);
    iteration++;
  }*/

  Animal *liste_predateur = NULL;

  for(int j = 0 ; j<40 ; j++){
    int x = rand()%20;
    int y = rand()%50;
    ajouter_animal(x,y, energie_pre, &liste_predateur);
  }

  //afficher_ecosys(liste_predateur,liste_proie);

  printf("exercice 6, question 2\n");

  iteration = 0;

  /*while(iteration < 200 && liste_proie != NULL && liste_predateur != NULL) {
    bouger_animaux(liste_predateur);
    bouger_animaux(liste_proie);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    bouger_animaux(liste_predateur);
    bouger_animaux(liste_proie);
    usleep(T_WAIT);
    afficher_ecosys(liste_predateur,liste_proie);
    bouger_animaux(liste_predateur);
    bouger_animaux(liste_proie);
    iteration++;
  }
  */
  
   //exercice 7, question 3

   for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      monde[i][j]=0;
    }
  }

  /*while(i<4){
    bouger_animaux(liste_predateur);
    reproduce(&liste_predateur,1);
    reproduce(&liste_proie,p_reproduce_proie);
    bouger_animaux(liste_proie);
    i++;
  }*/

  while(iteration < 100 && liste_proie != NULL && liste_predateur != NULL) {
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    usleep(T_WAIT);
    rafraichir_proies(&liste_proie, monde);
    usleep(T_WAIT);
    rafraichir_monde(monde);
    /*for (int i = 0; i < SIZE_X; i++){
      for (int j = 0; j < SIZE_Y; j++){
        printf("%d", monde[i][j]);
      }
    }*/
    usleep(T_WAIT);    
    afficher_ecosys(liste_predateur,liste_proie);
    tabProies[iteration] = compte_animal_it(liste_proie); 
    tabPred[iteration] = compte_animal_it(liste_predateur); 
    iteration++;
  }
  afficher_ecosys(liste_predateur,liste_proie);

   //exercice 8, question 1

  FILE *file = fopen("Evol_Pop.txt", "w");
  

  //Ecris dans le fichier 
  for(int i = 0 ; i < 200 ; i++){
    fprintf(file, "%d ", i+1);
    fprintf(file, "%d ", tabProies[i]);
    fprintf(file, "%d\n ", tabPred[i]);
  }

  /*
  Si on veut afficher un graphique
  1. Générer les données dans un .txt
  2. Executer "gnuplot plot_script.gp" dans le terminal
  */
  
  fclose(file);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

    return 0;
}


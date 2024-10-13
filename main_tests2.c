#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"
#include <string.h>

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

int main(){

  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie=10;
  srand(time(NULL));
  
  for(int i = 0 ; i<20 ; i++){
    int x = rand()%20;
    int y = rand()%50;
    ajouter_animal(x,y, energie, &liste_proie);
  }
  
  for(int j = 0 ; j<20 ; j++){
    int x = rand()%20;
    int y = rand()%50;
    ajouter_animal(x,y, energie, &liste_predateur);
  }
  
  if(liste_proie==NULL){
    exit(1);
  }
  else if(liste_predateur==NULL){
    exit(0);
  }
  
  afficher_ecosys(liste_predateur, liste_proie);

  ecrire_ecosys("mon_fichier", liste_proie ,liste_predateur);
  liste_predateur=NULL;
  liste_proie=NULL;
  lire_ecosys("mon_fichier", &liste_proie, &liste_predateur);

  afficher_ecosys(liste_predateur, liste_proie);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  /*Animal *liste_animal = NULL;
  
  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  liste_animal = ajouter_en_tete_animal(liste_animal, a1);
  liste_animal = ajouter_en_tete_animal(liste_animal, a2);
  liste_animal = ajouter_en_tete_animal(liste_animal, a3);
  liste_animal = ajouter_en_tete_animal(liste_animal, a4);
  
  afficher_ecosys(liste_animal, liste_animal);
  
  enlever_animal(&liste_animal,a1);
  enlever_animal(&liste_animal,a3);
  
  afficher_ecosys(liste_animal, liste_animal);
  
  liberer_liste_animaux(liste_animal);
  */

  return 0;
}

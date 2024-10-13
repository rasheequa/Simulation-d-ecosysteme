#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <string.h>

//Richard ENG
//Rasheequa BAGADAD SAIB

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  //Si energie > 0 => animal est vivant
  if(energie>0.0){
    //Crée un animal à la position (x,y) et le met en tête de liste
    Animal *na = creer_animal(x,y,energie);
    *liste_animal = ajouter_en_tete_animal(*liste_animal,na);
  }
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  if(!*liste) return;
  Animal *courant = *liste;
  Animal *precedent = NULL;
  while(courant){
    //Si l'élément à supprimer est le premier élément de la liste
    if((animal==courant)&&(precedent==NULL)){
      //alors la tête de liste devient le deuxième élément
      *liste = courant->suivant;
      free(courant); break;
    }
    //Si l'élément à supprimer n'est pas le premier élément de la liste
    else if((animal==courant)&&(precedent!=NULL)){
      //alors le pointeur précédent l'élément à supprimer pointe vers l'élément suivant l'élément à supprimer
      precedent->suivant = courant->suivant;
      free(courant); break;
    }
    //On passe à l'élément suivant
    precedent = courant;
    courant = courant->suivant;
  }
  return;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
   while(liste){
    Animal *tmp = liste;
    liste=liste->suivant;
    free(tmp);
   }
  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

void ecrire_ecosys(const char *mon_fichier, Animal *liste_proies, Animal *liste_predateurs) {

    FILE *f = fopen(mon_fichier, "w"); // ouvrir un fichier en mode ecriture
    if (f == NULL) {
        printf("Erreur d'ouverture : %s\n", mon_fichier);
        return;
    }

    // Écriture des proies
    fprintf(f, "<proies>\n");
    Animal *courant_proie = liste_proies;
    while (courant_proie) {
        fprintf(f, "x = %d  y = %d  dir = [%d %d] e = %f\n", courant_proie->x, courant_proie->y, courant_proie->dir[0], courant_proie->dir[1], courant_proie->energie);
        courant_proie = courant_proie->suivant;
    }
    fprintf(f, "</proies>\n");
    // fin de ligne

    // Écriture des prédateurs
    fprintf(f, "<predateurs>\n");
    Animal *courant_predateur = liste_predateurs;
    while (courant_predateur) {
        fprintf(f, "x = %d  y = %d  dir = [%d %d] e = %f\n", courant_predateur->x, courant_predateur->y, courant_predateur->dir[0], courant_predateur->dir[1], courant_predateur->energie);
        courant_predateur = courant_predateur->suivant;
    }
    fprintf(f, "</predateurs>\n");
    // fin de ligne
    fclose(f);
}

void lire_ecosys(const char *mon_fichier, Animal **liste_predateur, Animal **liste_proie) {
    // Libérez la liste existante de proies et de prédateurs avant de lire les nouvelles données

    FILE *f = fopen(mon_fichier, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture : %s\n", mon_fichier);
        return;
    }

    char buffer[256];
    int x, y, dir[2];
    float e;
    fgets(buffer, 256, f); // recupere le curseur sur la ligne sur buffer
    assert(strncmp(buffer, "<proies>", 8) == 0); // on compare le nombre de caractere
    fgets(buffer, 256, f);
    while (strncmp(buffer, "</proies>", 8) != 0) {
      sscanf(buffer, "x = %d  y = %d  dir = [%d %d] e = %f\n", &x, &y, &dir[0], &dir[1], &e);
      // Créez un nouvel animal et initialisez ses propriétés
      Animal *nouvelle_proie = creer_animal(x, y, e);
      nouvelle_proie->dir[0] = dir[0];
      nouvelle_proie->dir[1] = dir[1];
      // Ajoutez l'animal à la liste des proies
      *liste_proie = ajouter_en_tete_animal(*liste_proie, nouvelle_proie);
      fgets(buffer, 256, f);
  }
    
    fgets(buffer, 256, f);
    assert(strncmp(buffer, "<predateurs>", 12) == 0);
    fgets(buffer, 256, f);
    while (strncmp(buffer, "</predateurs>", 13) != 0) {
        sscanf(buffer, "x = %d  y = %d  dir = [%d %d] e = %f\n", &x, &y, &dir[0], &dir[1], &e);
        // Créez un nouvel animal et initialisez ses propriétés
        Animal *nouveau_predateur = creer_animal(x, y, e);
        nouveau_predateur->dir[0] = dir[0];
        nouveau_predateur->dir[1] = dir[1];
        // Ajoutez l'animal à la liste des prédateurs
        *liste_predateur = ajouter_en_tete_animal(*liste_predateur, nouveau_predateur);
        fgets(buffer, 256, f);
    }
    fclose(f); //sauvegarder les ecritures du fichiers afn de pas perdre de donnees
}

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    while(la){
      la->x=(la->x+la->dir[0]+SIZE_X)%SIZE_X; // on modifie la position de sorte à ce que l'animal ne depasse pas le tableau
      la->y=(la->y+la->dir[1]+SIZE_Y)%SIZE_Y;
      if((float)rand()/RAND_MAX<=p_ch_dir){ // on genere une direction aleatoire entre -1 et 1 de propabilité p_ch_dir
        la->dir[0]=(rand()%3)-1;
        la->dir[1]=(rand()%3)-1;
      }
      la = la->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
   Animal *courant = *liste_animal;
   while(courant){
    if((float)rand()/RAND_MAX<=p_reproduce){ // on ajoute un animal avec une propabilité p_reproduce
      ajouter_animal(courant->x, courant->y, (courant->energie)/2.0, liste_animal);
      courant->energie/=2.0;
   }
   courant=courant->suivant;
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/

  bouger_animaux(*liste_proie);
  Animal *proie = *liste_proie;
  //assert(proie);

  while (proie){
    int herbe = monde[proie->x][proie->y]; // on recupere la valeur de l'herbe à la position de l'animal

    if(herbe>0){ // l'animal mange l'herbe
      proie->energie+=herbe;
      monde[proie->x][proie->y]=temps_repousse_herbe;
    }

    if((proie->energie) <= 0.0){ // si l'animal n'a plus d'nergie on l'enlève
      Animal * tmp = proie;
      proie=proie->suivant;
      enlever_animal(liste_proie,tmp);
    }
    else{
      proie = proie->suivant;
    }
  }
  
  reproduce(liste_proie,p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/

  while (l){
    if(l->x==x && l->y==y){
      return l;
    }
    l=l->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/

  Animal *predateur = *liste_predateur;
  //assert(predateur);

  bouger_animaux(predateur);

  while (predateur){
    (predateur->energie) -= 1.0;
    Animal *proie = animal_en_XY(*liste_proie, predateur->x,predateur->y); //on recupere le pointeur de la proie presente sur la même case que le ppredateur
    if (proie!=NULL){
      predateur->energie+=proie->energie; //le predateur prend l'energie à la proie qui est enlevé apres
      enlever_animal(liste_proie,proie);
    }

    if((predateur->energie) <= 0.0){
      Animal *tmp = predateur;
      predateur= predateur->suivant;
      enlever_animal(liste_predateur,tmp);
    }

    else{
      predateur = predateur->suivant;
    }
  }
  reproduce(liste_predateur,p_reproduce_predateur);
}

/* Part 2. Exercice 7, question 2 */

void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

   /*A Completer*/
  for (int i = 0; i < SIZE_X; i++){
    for (int j = 0; j < SIZE_Y; j++){
      monde[i][j]++; // on augmente de 1 l'herbe à chaque appelle de la fonction
    }
  }
}

/* Part 2. Exercice 8 */

int compter_animaux(Animal *la){
  int taille = 0;
  while(la){
    taille++;
    la = la->suivant;
  }
  return taille;
}

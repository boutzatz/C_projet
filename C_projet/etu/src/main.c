#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char *argv[]){
  FILE * fichier = NULL;
  if (argc > 1){

    fichier = fopen(argv[1], "rb");
  }
  if (fichier != NULL){
    int largeur ;
    int hauteur;
    int format = 0;
    int nbre_couleurs;
    char format_str[3];
    char largeur_hauteur[4];
    char nbre_couleurs_str[4];
    fgets(format_str, 3, fichier);
    format = atoi(format);
    printf("%u\n", format);
    getc(fichier);
    fgets(largeur_hauteur, 4, fichier);
    largeur = largeur_hauteur[0];
    hauteur = largeur_hauteur[1];
    printf("%u\n", hauteur);
    getc(fichier);
    fgets(nbre_couleurs_str, 4, fichier);
    nbre_couleurs = atoi(nbre_couleurs_str);
    printf("%u\n", nbre_couleurs);

    }
  return 0;
  }

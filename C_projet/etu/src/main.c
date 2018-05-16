#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc , char *argv[]){
  FILE * fichier = NULL;
  if (argc > 1){

    fichier = fopen(argv[1], "rb");
  }
  if (fichier != NULL){
    char format[3];
    char largeur_hauteur[4];
    char *largeur;
    char *hauteur;
    char nbre_couleurs[4];
    fgets(format, 3, fichier);
    printf("%s\n", format);
    getc(fichier);
    fgets(largeur_hauteur, 4, fichier);
    printf("%c\n", largeur_hauteur[0]);
    getc(fichier);
    fgets(nbre_couleurs, 4, fichier);
    printf("%s\n", nbre_couleurs);

    }
  return 0;
  }

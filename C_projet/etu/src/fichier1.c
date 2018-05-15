#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char *argv[]){
  FILE * fichier = NULL;
  if (argc > 1){

    fichier = fopen(argv[1], "rb");
  }
  if (fichier != NULL){
    int caractere = 0;
    int compteur = 0;
    while(compteur != 10){
      caractere = fgetc(fichier);
      printf("%c", caractere);
      compteur ++;
    }
    printf("\n");
  }
  return 0;
}

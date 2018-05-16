#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct entete_PPM { 
    char format[3];
    uint32_t  largeur;
    uint32_t  hauteur;
    uint32_t nbre_couleurs;
};
struct entete_PPM *lecture_entete_PPM(FILE* fichier){
    struct entete_PPM *entete = calloc(1, sizeof(struct entete_PPM));
    
    uint32_t largeur ;
    uint32_t hauteur;
    uint32_t nbre_couleurs;
    char format_str[3];
    char largeur_hauteur[4];
    char nbre_couleurs_str[4];
    fgets(format_str, 3, fichier);
    getc(fichier);
    fgets(largeur_hauteur, 4, fichier);
    largeur = largeur_hauteur[0] - '0';
    hauteur = largeur_hauteur[2] - '0';
    getc(fichier);
    fgets(nbre_couleurs_str, 4, fichier);
    nbre_couleurs = atoi(nbre_couleurs_str);
    strcpy(entete->format, format_str);
    entete->largeur = largeur;
    entete->hauteur = hauteur;
    entete->nbre_couleurs = nbre_couleurs;
    return entete;

}    
    

int main(int argc , char *argv[]){
    FILE * fichier = NULL;
     if (argc > 1){

        fichier = fopen(argv[1], "rb");
 }
 if (fichier != NULL){
     struct entete_PPM *entete = lecture_entete_PPM(fichier);
     printf("%s\n", entete->format);
  }
  return 0;
  }

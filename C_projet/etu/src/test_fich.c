#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
struct entete_PPM {
    char format[3];
    uint32_t  largeur;
    uint32_t  hauteur;
    uint32_t nbre_couleurs;
};
/*
         recuperation de l'entete d'un fichier PPM et les stocker puis
         retourner dans un type struct entete_PPM.

*/
struct entete_PPM *lecture_entete_PPM(FILE* fichier){
    struct entete_PPM *entete = calloc(1, sizeof(struct entete_PPM));

    uint32_t largeur ;
    uint32_t hauteur;
    uint32_t nbre_couleurs;
    char format_str[3];
    char largeur_hauteur[4];
    char nbre_couleurs_str[5];
    fgets(format_str, 3, fichier);
    getc(fichier);
    fgets(largeur_hauteur, 4, fichier);
    largeur = largeur_hauteur[0] - '0';
    hauteur = largeur_hauteur[2] - '0';
    getc(fichier);
    fgets(nbre_couleurs_str, 5, fichier);
    nbre_couleurs = atoi(nbre_couleurs_str);
    strcpy(entete->format, format_str);
    entete->largeur = largeur;
    entete->hauteur = hauteur;
    entete->nbre_couleurs = nbre_couleurs;




    return entete;

}
uint8_t** mcu_table(FILE* fichier) {
    struct entete_PPM *entete =  lecture_entete_PPM(fichier);
    uint32_t nbr_samples = ceil(entete->largeur / 8 ) *ceil(entete->hauteur / 8 );
    //printf("%u\n", nbr_samples);
    uint8_t** table_des_mcu = calloc(nbr_samples,sizeof(uint32_t* ));
    for (uint8_t i = 0; i < nbr_samples; i++){
        table_des_mcu[i] = calloc(64, sizeof(uint32_t));
    }
    // uint32_t nv_largeur = ceil(entete->largeur / 8)*8;
    // uint32_t nv_hauteur = ceil(entete->hauteur / 8)*8;
    // for (uint32_t i = 0; i < nbr_samples*64; i++){
    //     uint32_t i_sample_number = ceil(entete->largeur/8)/8 + ceil(entete->hauteur/8)/8;
    // }
    uint32_t i = 0;
    int32_t c = fgetc(fichier);
    while (c != EOF ){
          table_des_mcu[0][i] = c;
          ++i;
          c = fgetc(fichier);
        }

    return table_des_mcu;

}

void afficher_table88(uint8_t *tableau) {
  for (uint8_t i = 0; i < 64; i++) {
    printf("%06x\t", tableau[i]);
    if ( (i+1) % 8 == 0){
      printf("\n");
    }
  }
}

int main(int argc , char *argv[]){

FILE * fichier = NULL;

     if (argc > 1){

        fichier = fopen(argv[1], "rb");

 }
 if (fichier != NULL){
   uint8_t **mcus = mcu_table(fichier);
   afficher_table88(mcus[0]);
   printf("%x\n", mcus[0][3] >> 3);

  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "../include/htables.h"
#include "../include/qtables.h"
#include "../include/huffman.h"
#include "../include/jpeg_writer.h"
#include "../include/htables.h"

#define PI 3.1415927

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




void ecriture_entete_jpeg(char* fichier){
  //FILE *fichier_sortie = NULL;
  // fichier_sortie = fopen(fichier_sortie, "wb")
  struct entete_PPM *entete = lecture_entete_PPM(fopen(fichier, "rb"));
  struct jpeg_desc *jdesc = jpeg_desc_create ();
  jpeg_desc_set_ppm_filename (jdesc , fichier);
  jpeg_desc_set_jpeg_filename (jdesc , "fichier_sortie.jpg");
  jpeg_desc_set_image_width (jdesc , entete->largeur);
  jpeg_desc_set_image_height (jdesc , entete->hauteur);
  jpeg_desc_set_nb_components(jdesc, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, H, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, V, 1);
  struct huff_table *table_de_huff_Y_AC = huffman_table_build(&htables_nb_symb_per_lengths[AC][Y][16],
                                                              htables_symbols[AC][Y],
                                                              htables_nb_symbols[AC][Y]);
  jpeg_desc_set_huffman_table(jdesc,AC, Y, table_de_huff_Y_AC);
  struct huff_table *table_de_huff_Y_DC = huffman_table_build(&htables_nb_symb_per_lengths[DC][Y][16],
                                                              htables_symbols[DC][Y],
                                                              htables_nb_symbols[DC][Y]);
  jpeg_desc_set_huffman_table(jdesc,DC, Y, table_de_huff_Y_DC);
  jpeg_desc_set_quantization_table(jdesc, Y, compressed_Y_table);
  jpeg_write_header (jdesc );
}




/*
    Recupération des MCU's du fichier PPM et les retourner dans un tabelau
*/
int8_t** mcu_table(FILE* fichier) {
    struct entete_PPM *entete =  lecture_entete_PPM(fichier);
    int32_t nbr_samples = ceil(entete->largeur / 8 ) *ceil(entete->hauteur / 8 );
    //printf("%u\n", nbr_samples);
    int8_t** table_des_mcu = calloc(nbr_samples,sizeof(int32_t* ));
    for (int8_t i = 0; i < nbr_samples; i++){
        table_des_mcu[i] = calloc(64, sizeof(int32_t));
    }
    // uint32_t nv_largeur = ceil(entete->largeur / 8)*8;
    // uint32_t nv_hauteur = ceil(entete->hauteur / 8)*8;
    // for (uint32_t i = 0; i < nbr_samples*64; i++){
    //     uint32_t i_sample_number = ceil(entete->largeur/8)/8 + ceil(entete->hauteur/8)/8;
    // }
    int32_t i = 0;
    int32_t c = fgetc(fichier);
    while (c != EOF ){
          table_des_mcu[0][i] = c;
          ++i;
          c = fgetc(fichier);
        }

    return table_des_mcu;

}

void afficher_table88(int8_t *tableau) {
  for (int8_t i = 0; i < 64; i++) {
    printf("%i\t", tableau[i]);
    if ( (i+1) % 8 == 0){
      printf("\n");
    }
  }
}


float C(int i){
  if (i == 0){
    return (1/sqrt(2));
  }
  else{
    return 1;
  }
}

int8_t * DCT_table(int8_t** mcu_table){
  int i,j,x,y;
  int8_t *table = calloc(64, sizeof(int8_t));
  for (i=0; i<8; i++){
    for(j=0; j<8; j++){
      for (x=0;x<8;x++){
        for(y=0;y<8;y++){
          int8_t valeur_decalee = mcu_table[0][8*x+y] - 128;
          table[8*i+j] += valeur_decalee*cos(((2*x+1)*i*PI)*0.0625)* cos(((2*y+1)*j*PI)*0.0625);
        }
      }
      table[8*i+j] = 0.25*C(i)*C(j) *table[8*i+j];
    }
  }
  return table;
}

int main(int argc , char *argv[]){

FILE * fichier = NULL;

     if (argc > 1){

        fichier = fopen(argv[1], "rb");

 }
 if (fichier != NULL){
   int8_t **mcus = mcu_table(fichier);
   //afficher_table88(mcus[0]);
   printf("\n");
   int8_t *table = DCT_table(mcus);
   printf("%f\n", C(0));
   afficher_table88(table);
  }

  ecriture_entete_jpeg(argv[1]);
  return 0;
  }

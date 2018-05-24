#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../include/htables.h"
#include "../include/qtables.h"
#include "../include/huffman.h"
#include "../include/jpeg_writer.h"
#include "../include/htables.h"
#include "../include/bitstream.h"
#include "creation_jpeg.h"
/*
    Recupération des MCU's du fichier PPM et les retourner dans un tabelau
*/

struct image{
  uint16_t **mcu_table;
  int16_t **dct_table;
  int16_t **table_zz;

  uint32_t size;
  int16_t **table_quantif;
};

struct image *decoupage_8x8(FILE* fichier) {
    struct image *mcu = malloc(sizeof(struct image));

    struct entete_PPM *entete =  lecture_entete_PPM(fichier);
    uint16_t nbr_samples = ceil(entete->largeur / 8 ) * ceil(entete->hauteur / 8 );
    //printf("%u\n", nbr_samples);
    mcu->mcu_table = calloc(nbr_samples,sizeof(uint16_t* ));
    mcu->size = nbr_samples;
    for (uint16_t i = 0; i < nbr_samples; i++){
        mcu->mcu_table[i] = calloc(64, sizeof(uint16_t));
    }
    // uint32_t nv_largeur = ceil(entete->largeur / 8)*8;
    // uint32_t nv_hauteur = ceil(entete->hauteur / 8)*8;
    // for (uint32_t i = 0; i < nbr_samples*64; i++){
    //     uint32_t i_sample_number = ceil(entete->largeur/8)/8 + ceil(entete->hauteur/8)/8;
    // }
    uint32_t i = 0;
    int16_t c = fgetc(fichier);
    while (c != EOF ){
          uint32_t sample_number = (i%entete->largeur)/8 + (entete->hauteur/8)*((i/entete->hauteur)/8);
          uint16_t index_in_mcu = 8*((i/entete->hauteur)%8) + (i%entete->largeur)%8;
          //printf("%i\t%i\t %i\n", sample_number, index_in_mcu, i);
          mcu->mcu_table[sample_number][index_in_mcu] = c;
          i++;
          c = fgetc(fichier);
        }

    return mcu;

}

void afficher_mcu(int16_t *tableau) {
  for (int16_t i = 0; i < 64; i++) {
    printf("%04hx\t", tableau[i]);
    if ( (i+1) % 8 == 0){
      printf("\n");
    }
  }
}

void afficher(struct image *mcus){
  for (uint16_t i=0; i < mcus->size ; i++){
   printf(" ITER %u\n", i );
    afficher_mcu(mcus->table_quantif[i]);
    printf("\n\n");
  }
}

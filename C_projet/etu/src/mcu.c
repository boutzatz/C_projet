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
    uint16_t nbr_samples = ceil((float) entete->largeur / 8 ) * ceil((float) entete->hauteur / 8 );
    // printf("%u  %u   %u\n",entete->largeur/8, entete->hauteur/8, nbr_samples);
    mcu->mcu_table = calloc(nbr_samples,sizeof(uint16_t* ));
    mcu->size = nbr_samples;
    for (uint16_t i = 0; i < nbr_samples; i++){
        mcu->mcu_table[i] = calloc(64, sizeof(uint16_t));
    }
    uint32_t nv_largeur = ceil((float) entete->largeur / 8)*8;
    uint32_t nv_hauteur = ceil((float) entete->hauteur / 8)*8;
    // for (uint32_t i = 0; i < nbr_samples*64; i++){
    //     uint32_t i_sample_number = ceil(entete->largeur/8)/8 + ceil(entete->hauteur/8)/8;
    // }
    uint32_t sample_number;
    uint16_t index_mcu;
    uint32_t i = 0;
    int16_t c = 0;

    while ( i < nv_largeur*nv_hauteur ){
          if (i% nv_largeur < entete->largeur && i/nv_largeur < entete->hauteur){
            /* code */
          sample_number = (i%nv_largeur)/8 + (nv_largeur/8)*((i/nv_largeur)/8);
          index_mcu = 8*((i/nv_largeur)%8) + (i%nv_largeur)%8;
          //printf("%i\t%i\t %i\n", sample_number, index_in_mcu, i);
          c = fgetc(fichier);

          mcu->mcu_table[sample_number][index_mcu] = c;
          i++;


        }  else if (i%nv_largeur >= entete->largeur && i/nv_largeur < entete->hauteur) {
          mcu->mcu_table[sample_number][index_mcu+1] = mcu->mcu_table[sample_number][index_mcu];
          index_mcu++;
          i++;
        } else {
          uint32_t i_bis = i - nv_largeur;
          uint32_t sample_number_bis = (i_bis%nv_largeur)/8 + (nv_largeur/8)*((i_bis/nv_largeur)/8);
          uint16_t index_mcu_bis = 8*((i_bis/nv_largeur)%8) + (i_bis%nv_largeur)%8;
          mcu->mcu_table[sample_number_bis][index_mcu_bis + 8] = mcu->mcu_table[sample_number_bis][index_mcu_bis];
          i++;
        }


        }

    return mcu;

}

void afficher_mcu(uint16_t *tableau) {
  for (int16_t i = 0; i < 64; i++) {
    printf("%04hx\t", tableau[i]);
    if ( (i+1) % 8 == 0){
      printf("\n");
    }
  }
}

void afficher(struct image *mcus){
  for (uint16_t i=60; i < 65 ; i++){
   printf(" ITER %u\n", i );
    afficher_mcu(mcus->mcu_table[i]);
    printf("\n\n");
  }
}

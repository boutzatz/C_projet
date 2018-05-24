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
#include "mcu.h"
#include "DCT.h"
#include "zig_zag.h"
#include "quantification.h"
#include "compression_ACDC.h"




#define PI 3.1415927

extern uint16_t nbr_samples;
int main(int argc , char *argv[]){

FILE * fichier = NULL;

     if (argc > 1){

        fichier = fopen(argv[1], "rb");

 }
 if (fichier != NULL){
   struct image* mcus = decoupage_8x8(fichier);
  //  afficher(mcus);
   DCT_table(mcus);
   free(mcus->mcu_table);
   image_zz(mcus);
   free(mcus->dct_table);
   image_quantification(mcus);
   free(mcus->table_zz);
   afficher(mcus);
   ecriture_entete_jpeg(argv[1], mcus, "fichier_sortie.jpg");





  //  printf("\n");
  //  int16_t *table = DCT_table(mcus);
  //  afficher_DCT_ZZ(table);
  //  printf("\n");
  //  int16_t * table_zz= table_ZZ(table);
  //  afficher_DCT_ZZ(table_zz);
  //  printf("\n");
  //  int16_t *table_quantif = quantif(table_zz);
  //  afficher_DCT_ZZ(table_quantif);
  //  printf("%i\n", codage_diff(table_quantif));
  // // struct AC_RLE * tableau = codage_AC_RLE(table_quantif);
  // //  int i;
  // //  for(i= 0; i<63; i++){
  // //    printf("%i\t%i\t%i\t%i\n", tableau[i].indice, tableau[i].magn, tableau[i].nbr_zeros_prec, tableau[i].symbole);
  // //  }
  // //  printf("%i", magnitude(-4));
  //  ecriture_entete_jpeg(argv[1], table_quantif, "fichier_sortie.jpg");
  }



  return 0;
  }

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
#include "mcu.h"

#define PI 3.1415927

void afficher_DCT_ZZ(int16_t *tableau) {
  for (int16_t i = 0; i < 64; i++) {
    printf("%04hx\t", tableau[i]);
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

void DCT_table(struct image * mcus){
  int i,j,x,y;
  mcus->dct_table = calloc(mcus->size, sizeof(int16_t *));
  for (uint32_t k = 0; k < mcus->size; k++){
    mcus->dct_table[k] = calloc(64, sizeof(int16_t));
  }
  for (uint32_t k = 0; k < mcus->size; k++){
    for (i=0; i<8; i++){
      for(j=0; j<8; j++){
        for (x=0;x<8;x++){
          for(y=0;y<8;y++){
            mcus->dct_table[k][8*i+j] +=(mcus->mcu_table[k][8*x+y] - 128)*cos(((2*x+1)*i*PI)*0.0625)* cos(((2*y+1)*j*PI)*0.0625);
        }

      }
      mcus->dct_table[k][8*i+j] = 0.25*C(i)*C(j)*mcus->dct_table[k][8*i+j];
    }
  }
}
}

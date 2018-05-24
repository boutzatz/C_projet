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

int16_t *quantif(int16_t * ZZ){
  int16_t * table= calloc(64, sizeof(int16_t));
  int i,j;
  for (i=0; i<8; i++){
    for(j=0; j<8; j++){
      table[8*i+j] = ZZ[8*i+j] / compressed_Y_table[8*i+j];
    }
  }
  return table;
}

void image_quantification(struct image *mcus){
  mcus->table_quantif = calloc(mcus->size, sizeof(struct int16_t * ));
  for (uint32_t k =0; k < mcus->size; k++){
    mcus->table_quantif[k] = quantif(mcus->table_zz[k]);
  }
}

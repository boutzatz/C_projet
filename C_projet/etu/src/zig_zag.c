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

int16_t * table_ZZ(int16_t *dct_tableau){
  int i = 0;
  int j = 0;
  int croiss = 0;
  int index = 0;
  int16_t * table = calloc(64,sizeof(int16_t));
  while (i < 8 && j < 8) {
   table[index] = dct_tableau[8*i+j];
      ++index;
      //printf("%d \t",dct_table[8*i+j]);
      if (i == 0 || i == 7) {
  	     if (j == 7){
              j = j - 1;
              i = i + 1;
  		   }
          j = j + 1;
          table[index] = dct_tableau[8*i+j];
          ++index;
          //printf("%d \t",dct_table[8*i+j]);
  	      }
      else {
          if (j == 0 || j == 7) {
              if (i ==7) {
                  i = i - 1;
                  j = j + 1;
  			          }
              i = i + 1;
              table[index] = dct_tableau[8*i+j];
              ++index;
              //printf("%d \t",dct_table[8*i+j]);
  		        }
  	        }
  		if (i == 0 || j == 7) { croiss = 0;}
  		if (j == 0 || i == 7)  { croiss = 1;}
      if (croiss==1){
          i = i - 1;
          j = j + 1;
  	   }
  	else {
  	     i = i + 1;
        j = j - 1;
  	}
  }
  return table;
  }

void image_zz(struct image* mcus){
  mcus->table_zz = calloc(mcus->size ,sizeof(int16_t *));
  for (uint32_t k = 0; k < mcus->size; k++){
    mcus->table_zz[k] = table_ZZ(mcus->dct_table[k]);
  }

}

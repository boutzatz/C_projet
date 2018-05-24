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

int16_t magnitude(int16_t valeur_composante){
  return floor(log(abs(valeur_composante))/log(2))+1;
}

int16_t indice(int16_t valeur_composante){
  if (valeur_composante == 0){
    return 0;
  }
  else {
  int16_t magn = magnitude(valeur_composante);
  int16_t borne_1 = 1<<(magn-1);
  int16_t borne_2 = (1<<magn) -1;
  int16_t indice;
  if (valeur_composante >= borne_1){
      indice = borne_2 - borne_1 + 1 + valeur_composante - borne_1 ;
  } else {
      indice = valeur_composante + borne_2;
  }

  return indice;
}
}

int16_t codage_diff(int16_t *composante){
    int16_t DC = composante[0];
    return indice(DC);
}

struct AC_RLE{
  int16_t magn;
  int16_t indice;
  int16_t nbr_zeros_prec;
  int32_t symbole ;
};

uint32_t concatenation(int16_t nbr1, int16_t nbr2){

  return 16*nbr1 + nbr2 ;
}


struct AC_RLE * codage_AC_RLE(int16_t *composante){
  struct AC_RLE *tableau_sortie = calloc(63, sizeof(struct AC_RLE));
  int compteur = 0;
  int i;
  for(i=1; i<64; i++){
    if (composante[i] == 0){
      compteur++;
    }
    else {
      tableau_sortie[i-1].magn = magnitude(composante[i]);
      tableau_sortie[i-1].indice = indice(composante[i]);
      tableau_sortie[i-1].nbr_zeros_prec = compteur;
      tableau_sortie[i-1].symbole = concatenation(tableau_sortie[i-1].nbr_zeros_prec, tableau_sortie[i-1].magn);
      compteur=0;
    }
  }
  return tableau_sortie;
}
uint16_t decimale(uint32_t value) {
 char str[10];

 sprintf(str, "%d", value);
 uint32_t len = strlen(str);
 uint32_t hexa = 0;
 uint32_t index = 0;
 while (len > 0 ){
   hexa += (str[index]-'0')*pow(16, len - 1);
   ++index;
   --len;
 }
   return hexa;
}

struct huffman {
    uint32_t code_huffman;
    uint8_t nbits;
};

struct huffman *code_huffman(int16_t valeur, enum sample_type NB_SAMPLE_TYPES) {
  struct huff_table *ht= huffman_table_build((uint8_t *)htables_nb_symb_per_lengths[NB_SAMPLE_TYPES][Y],
                                                              htables_symbols[NB_SAMPLE_TYPES][Y],
                                                              htables_nb_symbols[NB_SAMPLE_TYPES][Y]);

  struct huffman * hf = calloc(1, sizeof(struct huffman ));
  uint8_t *nbits = malloc(sizeof(uint8_t));
  hf->code_huffman = huffman_table_get_path( ht,valeur, nbits);
  hf->nbits = *nbits;
  huffman_table_destroy(ht);

  return hf;
}

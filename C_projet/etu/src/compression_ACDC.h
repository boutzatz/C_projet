#ifndef COMPRESSION_ACDC_H
#define COMPRESSION_ACDC_H

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

struct AC_RLE{
  int16_t magn;
  int16_t indice;
  int16_t nbr_zeros_prec;
  int32_t symbole ;
};
struct huffman {
    uint32_t code_huffman;
    uint8_t nbits;
};
/*
calcule la magnitude de la valeur passée en parametre */

extern int16_t magnitude(int16_t valeur_composante);

/*
retourne l'indice de la valeur passée en parametre */

extern int16_t indice(int16_t valeur_composante);

/*
retourne un entier qui est la concaténation des deux entiers passés en paramètres
*/

extern uint32_t concatenation(int16_t nbr1, int16_t nbr2);

/*
Construit un tableau des structures du codage RLE correpondant au élements du bloc 8x8 passé en paramètre
*/

extern struct AC_RLE * codage_AC_RLE(int16_t *composante);


/*
Retourne une structure huffman de la valeur passée en argument : son code de huffman et sa longueur en bits
*/

extern struct huffman *code_huffman(int16_t valeur, enum sample_type NB_SAMPLE_TYPES);

#endif /* COMPRESSION_ACDC_H */

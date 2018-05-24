#ifndef MCU_H
#define MCU_H




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

struct image{
  uint16_t **mcu_table;
  int16_t **dct_table;
  int16_t **table_zz;

  uint32_t size;
  int16_t **table_quantif;
};

/*
    Recupération des MCU's du fichier PPM et les retourner dans un tabelau
*/
extern struct image* decoupage_8x8(FILE* fichier);

/*
Affiche les elements d'un bloc 8X8 en hexadécimal
*/
extern void afficher_mcu(int16_t *tableau);
extern void afficher(struct image *mcu);

#endif /* MCU_H */

#ifndef DCT_H
#define DCT_H

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

 /*
 Affiche un bloc 8X8 contenant des valeurs négatifs en hexadécimal
 */

extern void afficher_DCT_ZZ(int16_t *tableau);

/*
Construit un Bloc 8X8 de la transformée en cos discret du premier bloc 8X8 de la table des MCUS tableau
*/
extern void DCT_table(struct image * mcus);

#endif /* DCT_H */

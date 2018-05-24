#ifndef QUANTIFICATION_H
#define QUANTIFICATION_H


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
Construit un bloc 8X8 quantifié aprés l'étape l'étape du zigzag
*/


extern int16_t *quantif(int16_t * ZZ);

extern void image_quantification(struct image *mcus);

#endif /* QUANTIFICATION_H */

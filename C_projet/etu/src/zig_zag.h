#ifndef ZIG_ZAG_H
#define ZIG_ZAG_H


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
Construit une table 8X8 qui correspond au parcours en zigzag du bloc fréquentiel dct_table 8x8
*/
extern int16_t * table_ZZ(int16_t *dct_table);
extern void image_zz(struct image* mcus);

#endif /* ZIG_ZAG_H */

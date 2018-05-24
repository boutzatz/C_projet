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
#include "compression_ACDC.h"
#include "mcu.h"
struct entete_PPM {
    char format[3];
    uint32_t  largeur;
    uint32_t  hauteur;
    uint32_t nbre_couleurs;
};
/*
         recuperation de l'entete d'un fichier PPM et les stocker puis
         retourner dans un type struct entete_PPM.

*/

struct entete_PPM *lecture_entete_PPM(FILE *fichier){
    struct entete_PPM *entete = calloc(1, sizeof(struct entete_PPM));
    uint32_t nbre_couleurs = 0;
    char* format_str = calloc(3, sizeof(char));
    uint16_t largeur = 0;
    uint16_t hauteur = 0;
    fgets(format_str, 3, fichier);
    getc(fichier);
    int16_t c = getc(fichier);
    while ( c != 0x20){
        largeur =10*largeur+ c - '0';
        c = getc(fichier);
    }
    c = getc(fichier);
    while ( c != 0x0a){
        hauteur = hauteur * 10 + (c - '0');
        c = getc(fichier);
    }
    c = getc(fichier);
    while ( c!= 0x0a){
        nbre_couleurs += 10*(c - '0');
        c = getc(fichier);
    }
    strcpy(entete->format, format_str);
    entete->largeur = largeur;
    entete->hauteur = hauteur;
    entete->nbre_couleurs = nbre_couleurs;

    return entete;
}

// bool reste_null(int debut, struct AC_RLE * table_AC){
//   int k = debut;
//   while (k<63 && table_AC[k].magn == 0){
//     k++;
//   }
//   return true;
// }

void ecriture_flow(struct image *mcus, struct jpeg_desc *jdesc){
  int16_t predicateur = 0;
  struct bitstream *stream = jpeg_desc_get_bitstream(jdesc);
  for(uint32_t k =0; k < mcus->size ; k++){
    struct huffman * c_huffman = code_huffman(magnitude(mcus->table_quantif[k][0]-predicateur), DC);
     uint32_t valeur_huff = c_huffman->code_huffman;
      //printf("iter : %u\t", k );
      //printf("magnitude :%u   index : %i\t", magnitude(mcus->table_quantif[k][0] - predicateur), indice(mcus->table_quantif[k][0] - predicateur));
      //printf("valeur DC: %i\t", mcus->table_quantif[k][0]-predicateur);
      //printf("huffman path : %u\t nbits= %u\n ", valeur_huff, c_huffman->nbits );
     bitstream_write_nbits(stream, valeur_huff,c_huffman->nbits, false);
     free(c_huffman);

     bitstream_write_nbits(stream,  indice(mcus->table_quantif[k][0]-predicateur), magnitude(mcus->table_quantif[k][0]-predicateur), false);
     predicateur = mcus->table_quantif[k][0];
     struct AC_RLE * table_AC = codage_AC_RLE(mcus->table_quantif[k]);
     //printf( "iter %u\n",k );
     for(int i = 0; i<63; i++){
       if (table_AC[i].magn != 0 ){
         while (table_AC[i].nbr_zeros_prec >= 16){
           table_AC[i].nbr_zeros_prec -= 16;
           bitstream_write_nbits(stream, 2041, 11, false);

           //printf("ZRL\n");
         }
         uint16_t valeur_symbole = concatenation(table_AC[i].nbr_zeros_prec,table_AC[i].magn);
         struct huffman *ac_huffman = code_huffman(valeur_symbole, AC);
         uint32_t huffman_symbole = ac_huffman->code_huffman;
         bitstream_write_nbits(stream, huffman_symbole,ac_huffman -> nbits, false);
         //printf(" valeur AC: %i\t code huffman: %u\t nbits =%u\t RLE = %u indice = %u nb_zeros_prec = %u MAGN = %u concat = %u\n",mcus->table_quantif[k][i+1],huffman_symbole, ac_huffman->nbits, valeur_symbole, table_AC[i].indice, table_AC[i].nbr_zeros_prec, table_AC[i].magn, concatenation(table_AC[i].nbr_zeros_prec,table_AC[i].magn)  );
         bitstream_write_nbits(stream, table_AC[i].indice, table_AC[i].magn, false);
         free(ac_huffman);

      }
      }

         if (mcus->table_quantif[k][63] == 0){
         bitstream_write_nbits(stream, 10, 4, false);
         //printf("EOB\n");
       }
      //printf("\n");
     }
}

void ecriture_entete_jpeg(char* fichier, struct image *mcus,const char *fichier_de_sortie ){
  //FILE *fichier_sortie = NULL;
  // fichier_sortie = fopen(fichier_sortie, "wb")
  struct entete_PPM *entete = lecture_entete_PPM(fopen(fichier, "rb"));
  struct jpeg_desc *jdesc = jpeg_desc_create ();
  jpeg_desc_set_ppm_filename (jdesc , fichier);
  jpeg_desc_set_jpeg_filename (jdesc , fichier_de_sortie);
  jpeg_desc_set_image_width (jdesc , entete->largeur);
  jpeg_desc_set_image_height (jdesc , entete->hauteur);
  jpeg_desc_set_nb_components(jdesc, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, H, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, V, 1);
  struct huff_table *table_de_huff_Y_AC = huffman_table_build((uint8_t *)htables_nb_symb_per_lengths[AC][Y],
                                                              htables_symbols[AC][Y],
                                                              htables_nb_symbols[AC][Y]);
  jpeg_desc_set_huffman_table(jdesc,AC, Y, table_de_huff_Y_AC);
  struct huff_table *table_de_huff_Y_DC = huffman_table_build((uint8_t *)htables_nb_symb_per_lengths[DC][Y],
                                                              htables_symbols[DC][Y],
                                                              htables_nb_symbols[DC][Y]);
  jpeg_desc_set_huffman_table(jdesc,DC, Y, table_de_huff_Y_DC);
  jpeg_desc_set_quantization_table(jdesc, Y, compressed_Y_table);
  jpeg_write_header (jdesc );
  ecriture_flow(mcus, jdesc);
  jpeg_write_footer(jdesc);
}

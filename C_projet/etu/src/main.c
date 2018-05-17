#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "jpeg_writer.h"
#include "htables.h"
#include "qtables.h"
#include "huffman.h"
struct entete_PPM {
    char format[3];
    uint32_t  largeur;
    uint32_t  hauteur;
    uint32_t nbre_couleurs;
};
struct entete_PPM *lecture_entete_PPM(FILE* fichier){
    struct entete_PPM *entete = calloc(1, sizeof(struct entete_PPM));

    uint32_t largeur ;
    uint32_t hauteur;
    uint32_t nbre_couleurs;
    char format_str[3];
    char largeur_hauteur[4];
    char nbre_couleurs_str[4];
    fgets(format_str, 3, fichier);
    getc(fichier);
    fgets(largeur_hauteur, 4, fichier);
    largeur = largeur_hauteur[0] - '0';
    hauteur = largeur_hauteur[2] - '0';
    getc(fichier);
    fgets(nbre_couleurs_str, 4, fichier);
    nbre_couleurs = atoi(nbre_couleurs_str);
    strcpy(entete->format, format_str);
    entete->largeur = largeur;
    entete->hauteur = hauteur;
    entete->nbre_couleurs = nbre_couleurs;
    return entete;

}




void ecriture_entete_jpeg(char* fichier){
  //FILE *fichier_sortie = NULL;
  // fichier_sortie = fopen(fichier_sortie, "wb")
  struct entete_PPM *entete = lecture_entete_PPM(fopen(fichier, "rb"));
  struct jpeg_desc *jdesc = jpeg_desc_create ();
  jpeg_desc_set_ppm_filename (jdesc , fichier);
  jpeg_desc_set_jpeg_filename (jdesc , "fichier_sortie.jpg");
  jpeg_desc_set_image_width (jdesc , entete->largeur);
  jpeg_desc_set_image_height (jdesc , entete->hauteur);
  jpeg_desc_set_nb_components(jdesc, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, H, 1);
  jpeg_desc_set_sampling_factor(jdesc, Y, V, 1);
  struct huff_table *table_de_huff_Y_AC = huffman_table_build(&htables_nb_symb_per_lengths[AC][Y][16],
                                                              htables_symbols[AC][Y],
                                                              htables_nb_symbols[AC][Y]);
  jpeg_desc_set_huffman_table(jdesc,AC, Y, table_de_huff_Y_AC);
  struct huff_table *table_de_huff_Y_DC = huffman_table_build(&htables_nb_symb_per_lengths[DC][Y][16],
                                                              htables_symbols[DC][Y],
                                                              htables_nb_symbols[DC][Y]);
  jpeg_desc_set_huffman_table(jdesc,DC, Y, table_de_huff_Y_DC);
  jpeg_desc_set_quantization_table(jdesc, Y, compressed_Y_table);
  jpeg_write_header (jdesc );
}

int main(int argc , char *argv[]){
    FILE * fichier = NULL;
     if (argc > 1){

        fichier = fopen(argv[1], "rb");
 }
 if (fichier != NULL){
     struct entete_PPM *entete = lecture_entete_PPM(fichier);
     printf("%s\n", entete->format);
  }
  ecriture_entete_jpeg(argv[1]);
  return 0;
  }

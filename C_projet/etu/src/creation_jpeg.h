#ifndef CREATION_JPEG_H
#define CREATION_JPEG_H



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


struct entete_PPM {
    char format[3];
    uint32_t  largeur;
    uint32_t  hauteur;
    uint32_t nbre_couleurs;
};
/*
Prend le fichier PPM de l'entrée en paramètre et renvoie une structure qui contient les élements qui définissent l'entête
*/
extern struct entete_PPM *lecture_entete_PPM(FILE* fichier);

/*
Prend le bloc 8*8 après l'étape de quantification et la structure jpeg desc du module jpeg_writer et écrit les données dans le fichier sortie
*/

extern void ecriture_flow(struct image *mcus, struct jpeg_desc *jdesc);

/*
prend en arguments respectifs le fichier PPM d'entrée, la table quantifiée et le nom de fichier de sortie et écrit l'entête, le footer et les données dans ce dernier,
elle appelle la fonction précedemment mentionée
*/

extern void ecriture_entete_jpeg(char* fichier, struct image *mcus,const char *fichier_de_sortie );

#endif /* CREATION_JPEG_H */

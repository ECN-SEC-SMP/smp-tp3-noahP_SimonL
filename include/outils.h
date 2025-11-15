#pragma once
#include "image.h"
#include "string"
#include <vector>
using namespace std;


const int tailleMaxMatrice = 16; //taille maximale de l'élément structurant
typedef  bool t_MatStructurante[tailleMaxMatrice][tailleMaxMatrice]; 

typedef struct{ //élèment structurant
    u_int16_t size; //largeur de l'élèment structurant
	t_MatStructurante em; //tableau des niveaux de gris de le l'élèment structurant
}t_structurant; 

//prototypes :
void differencePgm(t_Image * imgMod, t_Image *  img1, t_Image *  img2);
void erosionPgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
void fill_M(t_structurant * Struct);


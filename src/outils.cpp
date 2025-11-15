#include "../include/outils.h"
#include <cassert>
#include <cmath>
#include <iostream>

const short NOIR = 0;
const short BLANC = 255;

/**
 * @brief Calcule la valeur absolue de la différence entre deux images.
 *  
 * @param imgMod Pointeur vers l'image de sortie (modifiée).
 * @param img1 Pointeur vers la première image d'entrée.
 * @param img2 Pointeur vers la deuxième image d'entrée.
 * 
 * @pre Les trois pointeurs sont non nuls.
 * @pre Les images img1 et img2 doivent avoir les mêmes dimensions (w et h).
 */
void differencePgm(t_Image * imgMod, t_Image *  img1, t_Image *  img2){
    //Vérifie  que les img ne sont pas null
    assert(img1 != nullptr && img2 != nullptr && imgMod != nullptr);
    //Vérifie que les images font la même tailles
    assert(img1->h == img2->h && img1->w == img2->w && imgMod->h == img1->h && imgMod->w == img1->w);

    //Parcours tous les pixels de l'image
    for (unsigned short y = 0; y < img1->h; y++){
        for (unsigned short x = 0; x < img1->w; x++)
        {
            //Calcul la valeur absolue de la différence entre les 2 pixels des 2 images:
            imgMod->im[y][x] = abs((int)(img1->im[y][x]) - (int)(img2->im[y][x]));
        }
    }
}

void seuil(t_Image * Image,unsigned int sueil){
    assert(Image != nullptr);
    
    for (int i = 0; i < (*Image).h;i++){
        for(int j = 0; j<(*Image).w;j++){
            if(Image->im[i][j] < sueil){
                Image->im[i][j] = NOIR;
            }else{
                Image->im[i][j] = BLANC;
            }
        }
    }   
}


void dilatation(t_Image * Image, t_Image * Image_D, t_structurant * Struct){
    assert(Image != nullptr);
    
    
    for (int i = 0; i < (*Image).h;i++){
        for(int j = 0; j<(*Image).w;j++){
            if(Image->im[i][j] == 255){

                Image_D->im[i-1][j-1] = Struct->em[0][0];
                Image_D->im[i-1][j]   = Struct->em[0][1];
                Image_D->im[i-1][j+1] = Struct->em[0][2];

                Image_D->im[i][j-1]   = Struct->em[1][0];
                Image_D->im[i][j]     = Struct->em[1][1];
                Image_D->im[i][j+1]   = Struct->em[1][2];

                Image_D->im[i+1][j-1] = Struct->em[2][0];
                Image_D->im[i+1][j]   = Struct->em[2][1];
                Image_D->im[i+1][j+1] = Struct->em[2][2];

            }


        }
    }

}


/**
 * @brief Effectue l'opération d'érosion morphologique sur une image binaire.
 * 
 * @param imgMod Pointeur vers l'image de sortie (modifiée).
 * @param img Pointeur vers l'image binaire d'entrée.
 * @param elStructurant Pointeur vers l'élément structurant (ES) à utiliser.
 * @param couleurFond Booléen définissant la convention de couleur : 
 * - false (0) : Fond Noir (0) / Forme Blanche (255).
 * - true (1) : Fond Blanc (255) / Forme Noire (0).
 * 
 * @pre Les trois pointeurs sont non nuls.
 * @pre L'image de sortie doit être allouée et avoir la même taille que l'image d'entrée.
 */
void erosionPgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond){
    assert(img != nullptr && imgMod != nullptr && elStructurant != nullptr);
    assert(img->w == imgMod->w && img->h == imgMod->h); // L'image de sortie doit faire la même taille que l'image d'entrée

    unsigned short centre_offset = elStructurant->size/2;//Offset pour centrer la matrice structurante

    for (short y = 0; y < img->h; y++){
        for (short x = 0; x < img->w; x++){

            bool fits = true;

            //Vérification si la matrice structurante rentre
            for (short hM = 0; hM < elStructurant->size; hM++){
                for (short wM = 0; wM < elStructurant->size; wM++){

                    if (elStructurant->em[hM][wM] == 1 ){
                        short hMatrice = y + (hM - centre_offset);
                        short wMatrice = x + (wM - centre_offset);

                        //Vérification des bords et de la correspondance des pixels
                        if (hMatrice < 0 || wMatrice < 0 || hMatrice >=  img->h || wMatrice >= img->w || img->im[hMatrice][wMatrice] != (couleurFond ? NOIR : BLANC))
                        {
                            fits = false;
                            break;
                        }
                    }    
                }
            }

            //Gestion en fonction de la couleur de fond
            if (couleurFond){
                imgMod->im[y][x] = fits ? NOIR : BLANC;
            } else{
                imgMod->im[y][x] = fits ? BLANC : NOIR;
            }
        }
    }
}



void fill_M(t_structurant * Struct, int size){
    for (int i = 0; i < size; i++){
        for(int j = 0; j<size;j++){
            Struct->em[i][j] = 1;
        }
    }
}



void fermeturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond){
    
    erosionPgm(imgMod, img, elStructurant, couleurFond);
    dilatation(imgMod, img, elStructurant);
}


void ouverturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond){
    
    dilatation(imgMod, img, elStructurant);
    erosionPgm(imgMod, img, elStructurant, couleurFond);
    
}



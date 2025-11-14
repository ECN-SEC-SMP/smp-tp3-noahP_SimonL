#include "../include/outils.h"
#include <cassert>
#include <cmath>
#include <iostream>



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
    //Vérifie  que mes img ne sont pas null
    assert(img1 != nullptr && img2 != nullptr && imgMod != nullptr);
    //Vérifie que les images font la même tailles
    assert(img1->h == img2->h && img1->w == img2->w);

    //Parcours tous les pixels de l'image
    for (unsigned short y = 0; y < img1->h; y++){
        for (unsigned short x = 0; x < img1->w; x++)
        {
            //Calcul la valeur absolue de la différence entre les 2 pixels des 2 images:
            imgMod->im[y][x] = abs((int)(img1->im[y][x]) - (int)(img2->im[y][x]));
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
                        if (hMatrice < 0 || wMatrice < 0 || hMatrice >=  img->h || wMatrice >= img->w || img->im[hMatrice][wMatrice] != (couleurFond ? 0 : 255))
                        {
                            fits = false;
                            break;
                        }
                    }    
                }
            }

            //Gestion en fonction de la couleur de fond
            if (couleurFond){
                imgMod->im[y][x] = fits ? 0 : 255;
            } else{
                imgMod->im[y][x] = fits ? 255 : 0;
            }
        }
    }
}

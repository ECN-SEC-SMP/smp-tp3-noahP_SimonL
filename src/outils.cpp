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

/**
 * @brief Binarisation de l'image en noir et blanc
 * 
 * @param Image Pointeur vers l'image à binariser 
 * @param sueil valeur comprise 0 et 255 qui met le seuil pour choisir et entre passer le gis en blanc ou noir.
 *              gris < seuil = noir,
 *              gris > seuil = blanc
 * 
 * @pre Les trois pointeurs sont non nuls.
 * @pre 0 =< seuil <= 255
 * 
 */
void seuil(t_Image * Image,unsigned int seuil){
    assert(Image != nullptr);
    assert(seuil>=0 && seuil<=255);
    
    for (int i = 0; i < (*Image).h;i++){
        for(int j = 0; j<(*Image).w;j++){
            if(Image->im[i][j] < seuil){
                Image->im[i][j] = NOIR;
            }else{
                Image->im[i][j] = BLANC;
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




/**
 * @brief Effectue l'opération de dilatation morphologique sur une image binaire.
 * 
 * @param Image Image sur la quelle effectuer l'operation
 * @param Image_D Image à renvoyer avec l'opération effectuer
 * @param COULEUR Couleur avec la quelle travailler, Blanc ou Noir.
 * 
 * @pre Les trois pointeurs sont non nuls.
 * @pre L'image de sortie doit être allouée et avoir la même taille que l'image d'entrée.
 */
void dilatation(t_Image * Image, t_Image * Image_D, short COULEUR){
    assert(Image != nullptr);
    assert(Image->h == Image_D->h && Image->w == Image_D->w);
    
    for (int i = 1; i < (*Image).h ;i++){
        for(int j = 0; j<(*Image).w ;j++){
            if(Image->im[i][j] == COULEUR){

                Image_D->im[i-1][j-1] = COULEUR;
                Image_D->im[i-1][j]   = COULEUR;
                Image_D->im[i-1][j+1] = COULEUR;

                Image_D->im[i][j-1]   = COULEUR;
                Image_D->im[i][j]     = COULEUR;
                Image_D->im[i][j+1]   = COULEUR;

                Image_D->im[i+1][j-1] = COULEUR;
                Image_D->im[i+1][j]   = COULEUR;
                Image_D->im[i+1][j+1] = COULEUR;

            }
        }
    }
}



/**
 * @brief Réalise l'ouverture d'une image par un élément structurant (erosion -> dilatation).
 * 
 * @param imgMod Pointeur vers l'image résultante (modifiée après ouverture).
 * @param img Pointeur vers l'image d'origine.
 * @param elStructurant Pointeur vers l'élément structurant utilisé pour l'érosion/dilatation.
 * @param couleurFond Couleur du fond : true pour noir, false pour blanc.
 */
void ouverturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond){
    short COULEUR = couleurFond ? NOIR:BLANC;
    t_Image*  imgTemp = new t_Image;
    fill_IMAGE(imgTemp, img->w, img->h, couleurFond ? BLANC : NOIR);
    erosionPgm(imgTemp, img, elStructurant, couleurFond);
    dilatation(imgTemp,imgMod, COULEUR);
    delete imgTemp;
}


/**
 * @brief Réalise la fermeture d'une image par un élément structurant (dilatation -> erosion).
 * 
 * @param imgMod Pointeur vers l'image résultante (modifiée après fermeture).
 * @param img Pointeur vers l'image d'origine.
 * @param elStructurant Pointeur vers l'élément structurant utilisé pour la dilatation/érosion.
 * @param couleurFond Couleur du fond : true pour noir, false pour blanc.
 */
void fermeturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond){
    short COULEUR = couleurFond ? NOIR:BLANC;
    t_Image*  imgTemp = new t_Image;
    fill_IMAGE(imgTemp, img->w, img->h, couleurFond ? BLANC : NOIR);
    dilatation(img, imgTemp, COULEUR);
    erosionPgm(imgMod, imgTemp, elStructurant, couleurFond);
    delete imgTemp;
}

/**
 * @brief Remplit une image avec une valeur uniforme.
 * 
 * @param img Pointeur vers l'image à remplir.
 * @param width Largeur de l'image.
 * @param height Hauteur de l'image.
 * @param value Valeur à appliquer pour chaque pixel.
 */
void fill_IMAGE(t_Image * img, int width, int height, short value){
    img->w = width;
    img->h = height;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            img->im[i][j] = value;
        }
    }
}

/**
 * @brief Remplit un élément structurant avec une valeur uniforme.
 * 
 * L'élément structurant est supposé carré (width == height).
 * 
 * @param es Pointeur vers l'élément structurant.
 * @param size Taille de l'élément structurant.
 * @param value Valeur booléenne à appliquer pour chaque cellule.
 */
void fill_ES(t_structurant* es, uint16_t size, bool value){
    es->size = size; // On suppose que width == height
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            es->em[i][j] = value;
        }
    }
}


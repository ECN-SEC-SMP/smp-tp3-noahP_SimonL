#include "./include/outils.h"
#include "./include/chargesauve.h"

//Constantes pour les chemins d'accès aux images;
const string pathBasic = "./assets/pgmBasic/";
const string pathMod = "./assets/pgmMod/";
const string size1 = "512x512";
const string size2 = "21x17";
const string endFile = ".pgm";

#define FOND_NOIR  false
#define FOND_BLANC true


//Prototypes privées:
void test_difference();
void test_erosion();


int main(void) {
    test_difference();
    test_erosion();


}

void test_difference(){

    //Allocation dynamique des images
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_img2 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"plane"+size1+endFile,ptr_img2,success);
    loadPgm(pathBasic+"noir"+size1+endFile,ptr_imgMod,success);

    //Calcul de la différence :
    differencePgm(ptr_imgMod,ptr_img1,ptr_img2);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"lenaplane"+size1+endFile,ptr_imgMod);

    //Libération de la mémoire :
    delete ptr_img1;
    delete ptr_img2;
    delete ptr_imgMod;
}

void test_erosion(){

    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;

    //Initialisation de l'élément structurant (matrice 3x3 pleine) :
    ptr_elementStructurant->size = 3;
    for (unsigned int i = 0; i < 3; i++){
        for (unsigned int j = 0; j < 3; j++){
            ptr_elementStructurant->em[i][j] = 1;
        }
    }

    //Image 1 avec fond blanc
    //Chargement des images :
    loadPgm(pathBasic+"visageBinaire"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size2+endFile,ptr_imgMod,success);

    //Erosion :
    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"visageErosion"+size2+endFile,ptr_imgMod);

    //Image 2 avec fond noir
    loadPgm(pathBasic+"visageBinaire2"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"noir"+size2+endFile,ptr_imgMod,success);

    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_NOIR);

    savePgm(pathMod+"visageErosion2"+size2+endFile,ptr_imgMod);

    //Libération de la mémoire :
    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
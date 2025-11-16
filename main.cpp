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
#define NOIR  0
#define BLANC 255

//Prototypes privées:
void test_difference();
void test_erosion();
void test_dilatation();


int main(void) {
    //test_difference();
    //test_erosion();
    test_dilatation();


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
            ptr_elementStructurant->em[i][j] = 255;
        }
    }

    //Image 1 avec fond blanc
    //Chargement des images :
    loadPgm(pathBasic+"visageBinaire2"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"noir"+size1+endFile,ptr_imgMod,success);



    //Erosion :
    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    
    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"visageSeuil"+size2+endFile,ptr_img1);
    savePgm(pathMod+"visageDilatation"+size2+endFile,ptr_img1);

    //Image 2 avec fond noir
    

    //Libération de la mémoire :
    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}


void test_dilatation(){

    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_img2 = new t_Image;
    t_Image* ptr_imgMod_1 = new t_Image;
    t_Image* ptr_imgMod_2 = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement des images :
    loadPgm(pathBasic+"peppers"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"plane"+size1+endFile,ptr_img2,success);
    loadPgm(pathBasic+"noir"+size1+endFile,ptr_imgMod_1,success);
    loadPgm(pathBasic+"noir"+size1+endFile,ptr_imgMod_2,success);


    seuil(ptr_img1,125);
    seuil(ptr_img2,125);

    dilatation(ptr_img1,ptr_imgMod_1,BLANC);
    dilatation(ptr_img2,ptr_imgMod_2,BLANC);

    savePgm(pathMod+"peppers_Dilatation"+size1+endFile,ptr_imgMod_1);
    savePgm(pathMod+"plane_Dilatation"+size1+endFile,ptr_imgMod_2);
    //Libération de la mémoire :
    delete ptr_img1;
    delete ptr_img2;

    delete ptr_imgMod_1;
    delete ptr_imgMod_1;


}

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
void test_seuil();
void test_difference();
void test_erosion();
void test_dilatation();
void test_dilatation2();
void test_ouverture();
void test_fermeture();


int main(void) {
    test_seuil();
    test_difference();
    test_erosion();
    test_dilatation();
    test_dilatation2();
    test_fermeture();
    test_ouverture();
}


void test_seuil(){

    //Allocation dynamique de l'image
    t_Image* ptr_img1 = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement de l'image :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);

    //Binarisation de l'image avec un seuil de 125
    seuil(ptr_img1,125);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"lenaSeuil125"+size1+endFile,ptr_img1);

    //Libération de la mémoire :
    delete ptr_img1;
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
    fill_ES(ptr_elementStructurant,3,1);

    //Image 1 avec fond blanc
    //Chargement des images :
    loadPgm(pathBasic+"visageBinaireOriginal"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size2+endFile,ptr_imgMod,success);

    //Erosion :
    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    //Sauvegarde de l'image modifiée :
    savePgm(pathMod+"visageErosion"+size2+endFile,ptr_imgMod);

    //Image 2 avec fond noir
    loadPgm(pathBasic+"visageBinaireOriginalN"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"noir"+size2+endFile,ptr_imgMod,success);

    erosionPgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_NOIR);

    savePgm(pathMod+"visageErosionN"+size2+endFile,ptr_imgMod);

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
    delete ptr_imgMod_2;
}


void test_dilatation2(){

    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod_2 = new t_Image;
    bool success = false; //Indicateur de succès du chargement

    //Chargement des images :
    loadPgm(pathBasic+"visageBinaireOriginal"+size2+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size2+endFile,ptr_imgMod_2,success);

    dilatation(ptr_img1,ptr_imgMod_2,NOIR);

    savePgm(pathMod+"visageBinaireDilatation"+size2+endFile,ptr_imgMod_2);
    //Libération de la mémoire :
    delete ptr_img1;

    delete ptr_imgMod_2;
}




void test_fermeture(){
    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;
    //Initialisation de l'élément structurant (matrice 3x3 pleine) :
    fill_ES(ptr_elementStructurant,3,1);

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size1+endFile,ptr_imgMod,success);

    seuil(ptr_img1,125);


    fermeturePgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    savePgm(pathMod+"lenaFermeture"+size1+endFile,ptr_imgMod);

    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}


void test_ouverture(){

    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    bool success = false; //Indicateur de succès du chargement
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;
    //Initialisation de l'élément structurant (matrice 3x3 pleine) :
    fill_ES(ptr_elementStructurant,3,1);

    //Chargement des images :
    loadPgm(pathBasic+"lena"+size1+endFile,ptr_img1,success);
    loadPgm(pathBasic+"blanc"+size1+endFile,ptr_imgMod,success);


    seuil(ptr_img1,125);

    ouverturePgm(ptr_imgMod,ptr_img1,ptr_elementStructurant,FOND_BLANC);

    savePgm(pathMod+"lenaOuverture"+size1+endFile,ptr_imgMod);

    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
/*********************************************
fichier entete image.h
----------------------
Auteurs : Equipe pédagogique ALGPR
Date : 18 novembre 2003
Fichier : image.h
But : définir la structure de données t_Image 
pour représenter une image au format PGM
*********************************************/

#ifndef __secsmp_image
#define __secsmp_image 

//on fixe la taille maximale des images
const int TMAX = 800;

//on définit un type matrice d'entiers 
//pour rentrer les niveaux de gris des pixels de l'image 
typedef unsigned int t_MatEnt[TMAX][TMAX]; 

//on définit la structure de données pour représenter une image
struct t_Image
{
	int w; //largeur de l'image
    int h; //hauteur de l'image
	t_MatEnt im; //tableau des niveaux de gris de l'image
};

#endif

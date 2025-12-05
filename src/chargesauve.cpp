/*****************************************************************
Auteurs : Equipe pédagogique ALGPR
Date : 18 novembre 2003
Fichier : chargesauve.cxx
But : définir les actions ChargeImage et SauveImage
qui liront et écriront des fichiers PGM
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "image.h"
#include "chargesauve.h"


/*
Action ChargeImage(NomImage,Image,Ok)
Paramètre d'entrée : t-Chaine NomImage
Paramètres de sortie : t_Image Image, booléen Ok
But : charge, dans la variable Image, l'image donnée au format PGM 
dans le fichier NomImage. Le booléen Ok indique si le chargement
s'est effectué normalement.
*/
void loadPgm(string NomImage, t_Image * Image, bool & Ok)
{
  char c1,c2;
  int MaxGris,i,j;
  fstream Fic;
	
  Ok = true;
  Fic.open(NomImage,ios::in);
  Fic >> c1 >> c2; 
  if ((c1 == 'P')&&(c2=='2'))
    {
      Fic >> Image->w >> Image->h;
      if ((Image->w <= TMAX) && (Image->h <= TMAX))
	{
	  Fic >> MaxGris;
	  if (MaxGris == 255)
	    {
	      for (i=0;i<Image->h; i=i+1)
		{
		  for (j=0;j<Image->w;j=j+1)
		    {
		      Fic >> Image->im[i][j];
		    }
		}
	      cout << "chargement terminé." << endl;
	    }
	  else
	    {
	      cout << "la plus grande valeur de niveau de gris ne vaut pas 255" << endl;
	      Ok = false;
	    }
	}
      else
	{
	  cout << "la taille de l'image est trop grande" << endl;
	  Ok = false;
	}
    }
  else
    {
      cout << "le fichier n'est pas au format PGM" << endl;
      Ok = false;
    }
  Fic.close();
}

/*
Action SauveImage(NomImage, Image)
Paramètres d'entrée : t_Chaine NomImage, t_Image Image
Rq : Image, qui occupe beaucoup de place en mémoire, sera passée par adresse 
pour éviter de doubler cette place mémoire pendant l'exécution de l'action.
But : enregistre au format PGM, dans le fichier NomImage, l'image représentée
dans la variable Image.
*/
void savePgm(string NomImage, t_Image * Image)
{
  int k,i,j;
  fstream Fic;
	
  Fic.open(NomImage,ios::out);
  Fic << "P2" << endl;
  Fic << Image->w << ' ' << Image->h << endl;
  Fic << "255" << endl;
  k = 0;
  for (i=0;i<Image->h;i=i+1)
    {
      for (j=0;j<Image->w;j=j+1)
	{
	  Fic << Image->im[i][j] << ' ';
	  k=k+4;
	  if (k > 67)
	    {
	      Fic << endl;
        k = 0;
	    }
	}
    }
  Fic.close();
  cout << "sauvegarde terminée." << endl;
}



				
	

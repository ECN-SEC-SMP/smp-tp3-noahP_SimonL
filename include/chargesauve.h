/*****************************************************************
Fichier entete de chargesauve.cxx
---------------------------------
Auteurs : Equipe pédagogique ALGPR
Date : 18 novembre 2003
Fichier : chargesauve.h
But : définir les prototypes des actions ChargeImage et SauveImage
qui liront et écriront des fichiers PGM
*****************************************************************/

#ifndef __secsmp_chargesauve
#define __secsmp_chargesauve
/*
Action ChargeImage(NomImage,Image,Ok)
Paramètre d'entrée : t-Chaine NomImage
Paramètres de sortie : t_Image Image, booléen Ok
But : charge, dans la variable Image, l'image donnée au format PGM 
dans le fichier NomImage. Le booléen Ok indique si le chargement
s'est effectué normalement.
*/
void loadPgm(string NomImage, t_Image * Image, bool & Ok);

/*
Action SauveImage(NomImage, Image)
Paramètres d'entrée : t_Chaine NomImage, t_Image Image
Rq : Image, qui occupe beaucoup de place en mémoire, sera passée par adresse 
pour éviter de doubler cette place mémoire pendant l'exécution de l'action.
But : enregistre au format PGM, dans le fichier NomImage, l'image représentée
dans la variable Image.
*/
void savePgm(string NomImage, t_Image * Image);

#endif


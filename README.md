# Rapport de TP3 - raitements d’image PGM

**Nom :** PERRET Noah & L'HINGUERAT Simon 

**Groupe :** SEC1

**Date :** 13 novembre 2025  

## Compilation et exécution

```bash
# Compilation normale
make

# Exécution du main 

./main


# Nettoyage
make clean
```

## Préambule : Représentation des images .PGM

### Choix de représentation :

Pour représenter une image, nous utilisons la structure `t_Image`, qui s'appuie sur une taille maximale fixe et une matrice pour stocker les pixels

```cpp
const int TMAX = 800; // taille maximale des images

// Matrice d'entier pour representer les niveaux de gris des pixels de l'image 
typedef unsigned int t_MatEnt[TMAX][TMAX]; 

// On définit la structure de données pour représenter une image
struct t_Image
{
    int w; // largeur de l'image
    int h; // hauteur de l'image
    t_MatEnt im; // tableau des niveaux de gris de l'image
};
```


**Justification du choix :**
- **Capacité Maximale** : Une constante TMAX = 800 définit les dimensions maximales (800x800 pixels). <br> Ce choix simplifie la gestion de la mémoire.
- **Dimensions Réelles** : Les champs w (largeur) et h (hauteur) stockent les dimensions de l'image chargée. 
- **Stockage des Pixels** : La matrice im (de type t_MatEnt) est un tableau 2D qui stocke la valeur (niveau de gris) de chaque pixel.
- **Type de Données** : Le type unsigned int est utilisé pour les niveaux de gris. Il permet de stocker les valeurs PGM standards (typiquement comprises entre 0 et 255) tout en offrant une plage supérieure si nécessaire.

### Exemple de représentation :

Une petite image PGM de 2 pixels de large (w=2) et 2 pixels de haut (h=2):

```pgm
# Fichier : imgBsc.pgm (format P2 - ASCII)
P2
2 2
255
255 100
50 0
```

Zoom (vue agrandie, représentation pixel par pixel) :

<table>
    <tr>
        <td style="padding:6px">
            <div style="width:140px;height:140px;display:flex;align-items:center;justify-content:center;
                                    background:rgb(255,255,255);color:#000;border:1px solid #999;">
                (x=0, y=0) : 255
            </div>
        </td>
        <td style="padding:6px">
            <div style="width:140px;height:140px;display:flex;align-items:center;justify-content:center;
                                    background:rgb(100,100,100);color:#fff;border:1px solid #999;">
                (x=1, y=0) : 100
            </div>
        </td>
    </tr>
    <tr>
        <td style="padding:6px">
            <div style="width:140px;height:140px;display:flex;align-items:center;justify-content:center;
                                    background:rgb(50,50,50);color:#fff;border:1px solid #999;">
                (x=0, y=1) : 50
            </div>
        </td>
        <td style="padding:6px">
            <div style="width:140px;height:140px;display:flex;align-items:center;justify-content:center;
                                    background:rgb(0,0,0);color:#fff;border:1px solid #999;">
                (x=1, y=1) : 0
            </div>
        </td>
    </tr>
</table>


En mémoire (structure t_Image) serait représentée en mémoire comme cela :

```cpp
t_Image imgBsc;
imgBsc.w = 2;
imgBsc.h = 2;
imgBsc.im[0][0] = 255;   // pixel (x=0,y=0)
imgBsc.im[1][0] = 100; // pixel (x=1,y=0)
imgBsc.im[0][1] = 50; // pixel (x=0,y=1)
imgBsc.im[1][1] = 0;  // pixel (x=1,y=1)
```

## Q1) Fonctions seuillage et différence :

### Fonction  de seuillage `nom`

#### Algorithmes


<img src="./assets/UML_seuil.png" alt="Diagramme UML de differencePgm" width="300" />


#### Description du principe :
ce que fait le seuillage ...


#### Prototypes
```cpp
void seuil(t_Image * Image,unsigned int sueil);
```

#### Jeux d'essais 

```cpp
void test_seuil(){
    //mettre le code du test ici
}
```
![test_seuil](assets/seuil.png)

---
### Fonction  de différence `differencePgm()`

#### Algorithmes

<img src="./assets/UML_difference.png" alt="Diagramme UML de differencePgm" width="300" />


#### Description du principe :
Calcule l'image de la différence entre les images `img1` et `img2`.         L'algorithme calcule la valeur absolue de la différence entre chaque pixels des images d'entrer puis stocke ce résultat dans le pixel correspondant de l'image de sortie `imgMod`.


#### Prototypes
```cpp
void differencePgm(t_Image * imgMod, t_Image *  img1, t_Image *  img2);
```

#### Jeux d'essais 

```cpp
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
```
![test_difference](assets/lenaplage.png)

---


## Q2) Choix de la structure de l'élément structurant:

### Choix de représentation :

Pour représenter l’élément structurant, nous nous sommes appuyés sur la structure `t_Image`. <br> Toutefois, comme notre projet ne manipule que des images binaire noir et blanc, nous avons adapté cette structure : chaque pixel de l’élément structurant est désormais représenté par un booléen (true ou false).<br> Cette simplification permet de réduire la taille de stockage de la structure.

```cpp
const int tailleMaxMatrice = 16; //taille maximale de l'élément structurant

typedef  bool t_MatStructurante[tailleMaxMatrice][tailleMaxMatrice]; 

typedef struct{ //élèment structurant
    u_int16_t size; //largeur de l'élèment structurant
	t_MatStructurante em; //tableau des niveaux de gris de le l'élèment structurant
}t_structurant; 
```
## Q3) Fonctions dilatation et érosion :


### Fonction  `erosionPgm()`

#### Algorithmes

<img src="./assets/UML_erosion.png" alt="Diagramme UML de l'érosion" width="300" />


#### Description du principe :
L’érosion est une opération fondamentale de traitement d’image binaire utilisée pour réduire les objets blancs (ou noirs) et éliminer les petits détails dans une image. Elle s’appuie sur un élément structurant `t_structurant` qui définit la forme et la taille de l’érosion.


#### Prototypes
```cpp
void erosionPgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_erosion(){
    //Allocation dynamique des images :
    t_Image* ptr_img1 = new t_Image;
    t_Image* ptr_imgMod = new t_Image;
    //Allocation dynamique de l'élément structurant :
    t_structurant* ptr_elementStructurant = new t_structurant;

    bool success = false; //Indicateur de succès du chargement

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
    /**Voir Code Main pour plus de détails**/
   
    //Libération de la mémoire :
    delete ptr_img1; delete ptr_imgMod; delete ptr_elementStructurant;
}
```
![test_seuil](assets/erosion.png)

---


### Fonction  `dilatation()`

#### Algorithmes

<img src="./assets/UML_erosion.png" alt="Diagramme UML de dilatation" width="300" />


#### Description du principe :
ce que fait le dilatation ...


#### Prototypes
```cpp
void dilatation(t_Image * Image,unsigned int sueil);
```

#### Jeux d'essais 

```cpp
void test_dilatation(){
    //Ce que fait le test ici
}
```
![test_seuil](assets/dilatation.png)

---




## Q4) Fonctions d'ouverture et de fermeture :


### Fonction  `ouverturePgm()`

#### Algorithmes

<img src="./assets/UML_ouverture.png" alt="Diagramme UML de l'érosion" width="250" />


#### Description du principe :
L’ouverture est une opération morphologique qui combine une érosion suivie d’une dilatation. Elle est utilisée pour supprimer les petites structures ou bruits dans une image tout en préservant la forme générale des objets plus grands.


#### Prototypes
```cpp
void ouverturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_erosion(){
    //mettre le code du test ici
}
```
![test_seuil](assets/erosion.png)

---


### Fonction  `fermeturePgm()`

#### Algorithmes

<img src="./assets/UML_fermeture.png" alt="Diagramme UML de dilatation" width="250" />


#### Description du principe :
La fermeture est l’opération inverse de l’ouverture, qui combine une dilatation suivie d’une érosion. Elle est utilisée pour combler les petites trous ou fissures dans les objets tout en conservant leur forme globale.


#### Prototypes
```cpp
void fermeturePgm(t_Image * imgMod, t_Image *  img, t_structurant* elStructurant, bool couleurFond);
```

#### Jeux d'essais 

```cpp
void test_fermeture(){
    //Ce que fait le test ici
}
```
![test_seuil](assets/dilatation.png)

---















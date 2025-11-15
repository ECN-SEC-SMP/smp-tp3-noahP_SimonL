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

En mémoire (structure t_Image) :

```cpp
t_Image imgBsc;
imgBsc.w = 2;
imgBsc.h = 2;
imgBsc.im[0][0] = 255;   // pixel (x=0,y=0)
imgBsc.im[1][0] = 100; // pixel (x=1,y=0)
imgBsc.im[0][1] = 50; // pixel (x=0,y=1)
imgBsc.im[1][1] = 0;  // pixel (x=1,y=1)
```

serait représentée en mémoire comme suit :



## Q1) Fonctions seuillage et différence :

### Fonction  de seuillage `nom`

#### Algorithmes


#### Prototypes
```cpp
t_EntierLong convertInt_Entierlong(long long intToConvert);
```

#### Description du principe
Convertie un entier  ``` t_EntierLong```. Utilise `to_string()` pour obtenir la représentation décimale, puis stocke chaque chiffre dans l'ordre inverse.

#### Jeux d'essais simples avec Unity

```cpp
void test_convertInt_Entierlong(void) {
    // Test: conversion de 12345
    long input1 = 12345;
    int expected[5] = {5,4,3,2,1};
    t_EntierLong result = convertInt_Entierlong(input1);
    TEST_ASSERT_EQUAL(0, result.negatif); //vérification du signe
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, 5); //Vérification des chiffres

    // Test: conversion de -12345 → même chiffres, signe négatif
    long input2 = -12345;
    t_EntierLong result_neg = convertInt_Entierlong(input2);
    TEST_ASSERT_EQUAL(1, result_neg.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result_neg.chiffres, 5);
}//... 
```
---

### Fonction  de différence `differencePgm()`

#### Algorithmes

<img src="./assets/UML_difference.png" alt="Diagramme UML de differencePgm" width="200" />


#### Description du principe :
Calcule l'image de la différence entre les images `img1` et `img2`.         L'algorithme calcule la valeur absolue de la différence entre chaque pixels des images d'entrer puis stocke ce résultat dans le pixel correspondant de l'image de sortie `imgMod`.


#### Prototypes
```cpp
void differencePgm(t_Image * imgMod, t_Image *  img1, t_Image *  img2);
```

#### Jeux d'essais 

```cpp
void test_convertInt_Entierlong(void) {
    // Test: conversion de 12345
    long input1 = 12345;
    int expected[5] = {5,4,3,2,1};
    t_EntierLong result = convertInt_Entierlong(input1);
    TEST_ASSERT_EQUAL(0, result.negatif); //vérification du signe
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, 5); //Vérification des chiffres

    // Test: conversion de -12345 → même chiffres, signe négatif
    long input2 = -12345;
    t_EntierLong result_neg = convertInt_Entierlong(input2);
    TEST_ASSERT_EQUAL(1, result_neg.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result_neg.chiffres, 5);
}//... 
```
---
### - Fonction `EntierLongIsEqual`

#### Spécification
```cpp
bool EntierLongIsEqual(t_EntierLong a, t_EntierLong b);
```

#### Description du principe
La fonction vérifie l’égalité de deux entiers longs en commençant par comparer leur signe, puis en comparant chaque chiffre du tableau. Une optimisation a été rajoutée, on interrompt la comparaison dès qu’une différence est détectée.

#### Jeux d'essais avec Unity

```cpp
void test_EntierLongIsEqual(void) {
    // EntierLong de tests :
    t_EntierLong a = {0, {123}};
    t_EntierLong b = {1, {456}};

    //Test 1 : égalité (mêmes chiffres, même signe)
    TEST_ASSERT_TRUE(EntierLongIsEqual(a, c));

    //Test 2 : inégalité signe et chiffres différents)
    TEST_ASSERT_FALSE(EntierLongIsEqual(a, b));
}//...
```
---

### - Fonction `EntierLongAbsComparison`

#### Spécification
```cpp
bool EntierLongAbsComparison(t_EntierLong n1, t_EntierLong n2);
```

#### Description du principe
Comparaison des valeurs absolues en parcourant les chiffres de gauche à droite (poids fort vers poids faible) pour déterminer l'ordre de grandeur. (n1 <= n2)

#### Jeux d'essais avec Unity

```cpp
void test_abs_comparison(void) {
    // Test 1: Comparaison avec nombres identiques (5 >= 5)
    t_EntierLong same_a = {0, {5}};
    t_EntierLong same_b = {1, {5}}; // Même valeur absolue, signe différent
    TEST_ASSERT_TRUE(EntierLongAbsComparison(same_a, same_b));
    TEST_ASSERT_TRUE(EntierLongAbsComparison(same_b, same_a));

    // Test 2: Comparaison nombres avec plusieurs chiffres
    t_EntierLong multi = {0, {0, 0, 1}}; // 100 (selon ton format)
    t_EntierLong single = {0, {9}};      // 9
    TEST_ASSERT_FALSE(EntierLongAbsComparison(multi, single));
    TEST_ASSERT_TRUE(EntierLongAbsComparison(single, multi));
}//...
```
---

### - Fonction `initializeEntierLong`

#### Spécification
```cpp
void initializeEntierLong(t_EntierLong &n);
```


#### Description du principe
Initialisation par défaut d'une structure `t_EntierLong`. Met tous les éléments du tableau `chiffres[]` à 0

#### Jeux d'essais avec Unity

```cpp
void test_initializeEntierLong(void) {
    //Variables :
    t_EntierLong n;
    initializeEntierLong(n);
    int expected[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

    // Vérifie que toutes les valeurs du tableau sont bien initialisées à 0
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, n.chiffres, MAXCHIFFRES);
}//...
```

## Fonctions des Opérations Arithmétiques

### - Fonction `addSameSign`

#### Spécification
```cpp
t_EntierLong addSameSign(t_EntierLong n1, t_EntierLong n2);
```

#### Description du principe
addition de deux entiers longs ayant le même signe. Chaque chiffre est additionné avec la retenue de l’étape précédente. L'algorithme parcourt le tableau `chiffres[]` depuis l'index 0 (unités) jusqu'à MAXCHIFFRES-1, en propageant les retenues.

#### Jeux d'essais avec Unity


```cpp
void test_addSameSign(void) {
    // Test: 124 + 456 = 580 (positif)
    t_EntierLong a = convertInt_Entierlong(124);
    t_EntierLong b = convertInt_Entierlong(456);
    t_EntierLong result = addSameSign(a, b);

    int expected_pos[] = {0, 8, 5}; // 124 + 456 = 580 
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_pos, result.chiffres, 3);
    TEST_ASSERT_EQUAL(false, result.negatif); // positif

    // Test: -124 + -456 = -580 (négatif)
    t_EntierLong c = convertInt_Entierlong(-124);
    t_EntierLong d = convertInt_Entierlong(-456);
    t_EntierLong result_neg = addSameSign(c, d);

    int expected_neg[] = {0, 8, 5}; // même chiffres que pour le positif
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_neg, result_neg.chiffres, 3);
    TEST_ASSERT_EQUAL(true, result_neg.negatif); // négatif
}//...
```
---

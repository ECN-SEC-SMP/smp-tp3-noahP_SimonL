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

## Préambule : Représentation des Grands Entiers

### Choix de représentation :

Pour représenter des nombres dépassant les limites des types primitifs, nous utilisons la structure `t_EntierLong` :

```cpp
const int MAXCHIFFRES = 18;

struct t_EntierLong {
    bool negatif;               // true si le nombre est négatif
    int chiffres[MAXCHIFFRES];  // Chiffres stockés de droite à gauche
};
```


**Justification du choix :**
- **Capacité** : Variaibles grâce à la variables ```cpp const int MAXCHIFFRES = 18;``` (limite pratique pour éviter les débordements)
- **Stockage** : Les chiffres sont stockés dans l'ordre inverse (unités à l'index 0)
- **Signe** : Booléen `negatif` pour indiquer le signe
- **Format** : Chaque élément du tableau contient un seul chiffre (0-9)

### Exemple de représentation :

Le nombre `123456` est représenté comme :
```cpp
t_EntierLong n;
n.negatif = false;
n.chiffres = {6, 5, 4, 3, 2, 1, 0, 0, ..., 0};
//            ^unités      ^dizaines de milliers
```
## Présentation de la démarche Unity 

### Stratégie de test effectué

- **Tests de cas normaux** : Validation du comportement attendu
- **Tests de cas limites** : Valeurs particulières (0, nombres maximaux)
- **Tests d'erreur** : Vérification des conditions d'échec

### Fonctions Unity utilisées

```cpp
TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, MAXCHIFFRES);  // Comparaison tableaux
TEST_ASSERT_EQUAL(expected, actual);                         // Comparaison valeurs
TEST_ASSERT_TRUE(condition);                                 // Test booléen
TEST_ASSERT_FALSE(condition);                                // Test booléen inverse
```

#### Fonctions nécessaires aux tests
```cpp
void setUp(void) {
    exit_called = 0;
    cerr.rdbuf(nullptr); // Désactive les sorties d'erreur pendant les tests
}

void tearDown(void) {
    // Nettoyage après chaque test
}
```

### Avantages de Unity pour ce projet

1. **Simplicité d'utilisation** : Syntaxe claire et intuitive
2. **Portabilité** : Compatible avec tous les environnements C/C++
3. **Granularité** : Tests unitaires isolés et reproductibles
4. **Fonctions spécialisées** : `TEST_ASSERT_EQUAL_INT_ARRAY` parfait pour nos tableaux
5. **Gestion d'erreurs** : Capture possible des `exit()` avec `setjmp/longjmp`
6. **Étendue des tests** : Grand nombre de cas différents vérifiers et testés

Cette approche avec Unity augmente la fiabilité et la robustesse de toutes les fonctionss implémentées.


## Fonctions Utilitaires :

### - Fonction `convertInt_Entierlong`


#### Spécification
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

### - Fonction `subtractionSameSign`

#### Spécification
```cpp
t_EntierLong subtractionSameSign(t_EntierLong n1, t_EntierLong n2);
```

#### Description du principe
Soustraction de deux entiers longs ayant le même signe avec gestion des emprunts. L'algorithme parcourt les chiffres de gauche à droite, en empruntant à la position supérieure quand nécessaire (diff < 0).

#### Jeux d'essais avec Unity

```cpp
void test_subtractionSameSign(void) {
    // Test: 456 - 123 = 333 
    t_EntierLong a = convertInt_Entierlong(456);
    t_EntierLong b = convertInt_Entierlong(123);
    t_EntierLong result = subtractionSameSign(a, b);

    int expected[] = {3, 3, 3}; // chiffres inversés : 333
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, 3);
    TEST_ASSERT_EQUAL(false, result.negatif); // positif

    // Test: 402 - 158 = 244 (nécessite emprunt)
    t_EntierLong c = convertInt_Entierlong(402);
    t_EntierLong d = convertInt_Entierlong(158);
    t_EntierLong result_borrow = subtractionSameSign(c, d);

    int expected_borrow[] = {2, 4, 4}; // 244 → chiffres inversés
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_borrow, result_borrow.chiffres, 3);
    TEST_ASSERT_EQUAL(false, result_borrow.negatif); // positif
}//...
```
---

### - Fonction `add`

#### Spécification
```cpp
t_EntierLong add(t_EntierLong n1, t_EntierLong n2);
```

#### Description du principe
Addition générale gérant tous les cas de signes. Délègue à `addSameSign` pour même signe, ou convertit en soustraction pour signes différents.

#### Jeux d'essais avec Unity
```cpp
void test_add_general(void) {
    // Test 1: Addition négatif + positif (-5 + 8 = 3)
    t_EntierLong neg_first = {1, {5}};
    t_EntierLong pos_second = {0, {8}};
    int expected_gen5[1] = {3};
    //calcul :
    t_EntierLong add_result3 = add(neg_first, pos_second);
    TEST_ASSERT_EQUAL(0, add_result3.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen5, add_result3.chiffres, 1);
}//...
```
---

### - Fonction `sub`

#### Spécification
```cpp
t_EntierLong sub(t_EntierLong n1, t_EntierLong n2);
```


#### Description du principe
Soustraction générale gérant tous les cas de signes. Convertit en addition pour signes différents, ou utilise `subtractionSameSign`.

#### Jeux d'essais avec Unity

```cpp
void test_sub_general(void) {
    // Test 1: Soustraction positif - négatif (5 - (-3) = 8)
    t_EntierLong pos_num = {0, {5}};
    t_EntierLong neg_num = {1, {3}};
    int expected_sub_gen3[1] = {8};
    
    t_EntierLong sub_result1 = sub(pos_num, neg_num);
    TEST_ASSERT_EQUAL(0, sub_result1.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen3, sub_result1.chiffres, 1);
}//...
```
---

### - Fonction `multiplication`

#### Spécification
```cpp
t_EntierLong multiplication(t_EntierLong n1, t_EntierLong n2);
```

#### Description du principe
Multiplication par l'algorithme classique. Pour chaque chiffre de n1 à la position i, multiplie par chaque chiffre de n2 à la position j, et additionne le résultat à la position i+j avec gestion des retenues.

#### Jeux d'essais avec Unity

```cpp
void test_multiplication(void) {
    // Test 1: Multiplication positifs simples (5 × 4 = 20)
    t_EntierLong mult_a = {0, {0,5}};
    t_EntierLong mult_b = {0, {7,4}};
    int expected_mult1[4] = {0,5,3,2};

    //calcul:
    t_EntierLong mult_result1 = multiplication(mult_a, mult_b);
    TEST_ASSERT_EQUAL(0, mult_result1.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult1, mult_result1.chiffres, 4);
}//...
```
---

### - Fonction `divisionEuclidienne`

#### Spécification
```cpp
void divisionEuclidienne(t_EntierLong dividende, t_EntierLong diviseur, 
                        t_EntierLong &quotient, t_EntierLong &reste);
```

#### Description du principe
Division euclidienne par soustraction répétée non optimisée. Construction du quotient chiffre par chiffre en déterminant combien de fois le diviseur peut être soustrait du dividende partiel.

#### Jeux d'essais avec Unity

```cpp
void test_divisionEuclidienne(void) {
    // Test 1: Division positif ÷ négatif (-152 ÷ 3 = -5 reste 0)
    t_EntierLong dividende3 = {1, {2,5,1}};  // -152
    t_EntierLong diviseur3 = {0, {3}};      // 3
    t_EntierLong quotient3, reste3;
    //Calcul de la division
    divisionEuclidienne(dividende3, diviseur3, quotient3, reste3);
    
    TEST_ASSERT_EQUAL(1, quotient3.negatif); // Quotient négatif
    int expected_quotient3[2] = {0,5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient3, quotient3.chiffres, 2);
    
    TEST_ASSERT_EQUAL(1, reste3.negatif);   // Reste a le signe du dividende
    int expected_reste3[1] = {2};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste3, reste3.chiffres, 1);
}//...
```

## Application Pratique : Suite de Fibonacci

Afin de réaliser le calcul de la suite de Fibonacci pour des indices très élevés (jusqu'à 2000), je me suis basée sur le programme du TP précédent en y incorporant les fonctions d'arithmétique sur grands entiers implémentées durant ce TP.

### Calcule et afficage de la suite de Fibonacci

#### Spécification
```cpp
void  calculFibonnachi(t_EntierLong u0,t_EntierLong  u1, t_EntierLong * tabFibonnachi);
```

### Description du principe
 La fonction calculFibonnachi calcule les termes de la suite de Fibonacci en utilisant des entiers longs. Elle initialise les deux premiers termes, puis calcule chaque terme suivant par addition des deux termes précédents, en stockant les résultats dans un tableau. Les trois derniers termes sont affichés pour vérification et la relation de Fibonacci est contrôlée avec de très grand nombres.

La fonction est testé avec plusieurs valeurs de n, dont une très élevée de l'ordre de 2000.

### Warning 

il faut modifier la valeurs ```const int MAXCHIFFRES = 420;```   pour pouvoir calculer de grandes valeurs de Fibonacci sans débordement.

Pour cela, il faut aller dans le fichier [`entierlong.h`](./include/entierlong.h) et modifier la section de code suivante :

```cpp
//#define TEST_UNITY
```


### Résultats obtenus :

**F(1998) :**
```
1613690407208803110368054655512385458104297651135837630613006906830534714332207399493712880325169219450288448308295759737042197230572665380604023286891373247401696785508319080928645347611356230348985485765701044050512455172224518702511435579887743259875485129874105990640258275618868473552367070769298850271876109808326945609587521220740165418675860877711839171679169466490340360129402065732948246476990402668440811624
```

**F(1999) :**
```
2611005926183501768338670946829097324475555189114843467397273230483773870037923307730410719313972291638157639230613843870597997481070930648667960025707364078851859017098672504986584144842548768373271309551281830431960537091677315014266625027123872238011234749984205478230617988978500613170516952885123444971471854671812569739975450866912490650853945622130138277040986146312325044424769652148982077548213909414076005501
```

**F(2000) :**
```
4224696333392304878706725602341482782579852840250681098010280137314308584370130707224123599639141511088446087538909603607640194711643596029271983312598737326253555802606991585915229492453904998722256795316982874482472992263901833716778060607011615497886719879858311468870876264597369086722884023654422295243347964480139515349562972087652656069529806499841977448720155612802665404554171717881930324025204312082516817125
```

### Vérification : u₂₀₀₀ - u₁₉₉₉ = u₁₉₉₈

**Résultat de la soustraction u₂₀₀₀ - u₁₉₉₉ :**
```
1613690407208803110368054655512385458104297651135837630613006906830534714332207399493712880325169219450288448308295759737042197230572665380604023286891373247401696785508319080928645347611356230348985485765701044050512455172224518702511435579887743259875485129874105990640258275618868473552367070769298850271876109808326945609587521220740165418675860877711839171679169466490340360129402065732948246476990402668440811624
```

**Vérification réussie** : Ce résultat est exactement égal à F(1998), confirmant la propriété fondamentale de la suite de Fibonacci.

---






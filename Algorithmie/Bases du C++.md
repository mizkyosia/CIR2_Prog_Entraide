# Bases du C++

<font color="gray">_Écrit par Léo Lewandowski_</font>

> [!IMPORTANT]
> Ce document C++ est donné pour toute version >= C++23
>
> Si le code ci-dessous ne marche pas sur votre machine, vérifiez votre version du langage

## Introduction

Comme vous l'aurez remarqué, le C++ comporte beaucoup de similitudes avec le C, ce qui est logique puisque l'un est construit à partir de l'autre. \
D'ailleurs, tout code (au niveau que l'on a fait en tout cas) qui marche en C, marchera aussi en C++ (oui oui, même `scanf` et `printf`, même si on préfère utiliser `cin` et `cout`), à l'exception de quelques choses très spécifiques, telles que les `bool`, qui sont un type à part entière en C++.\
En C, les `bool` n'étaient que des simples `int` avec un cast de type.

Les pointeurs peuvent aussi marcher légèrement différemment en C++ avec l'utilisation implicite, mais peuvent tout de même être utilisés comme en C, avec `malloc`, `*`, `&` etc.

> [!CAUTION]
> Il existe tout de même _une_ différence majeure avec le C : un pointeur `void*` ne peut pas être casté en un pointeur d'un autre type. Ainsi, des codes types `char* str = (char*) malloc(n)` sont **invalides**, car `malloc` renvoie un pointeur `void*`, qui est ensuite transformé en pointeur `char*`

Pour simplifier ce document (cours ? tutoriel ?), je vais partir du principe que vous connaissez déjà bien le C (et surtout, que vous vous en souvenez encore). Si non, j'ai posté quelques cours et corrections de DS/Annales sur mon GitHub, vous pouvez aller les voir.

Pour ce premier document, je vais reprendre les points donnés dans le document donné par le prof [[1]](#cours), en tentant de les expliquer un peu mieux

> [!NOTE]
> Je vais utiliser beaucoup les termes "constante" et "variable" dans ce document, donc pour mettre au clair :
> 
> - Une _variable_ peut changer
> - Une _constante_ ne peut pas changer
>
> Outre cette différence, une constante _est_ une variable "spéciale"\
> Ainsi, je dirais "variable" pour parler des variables ***et*** des constantes, sauf mention contraire

Le début de ce document est déjà beaucoup trop long, alors rentrons dans le vif du sujet !

## Nouveau types

Le C++ introduit le système des `class` qui rajoute beaucoup de libertés aux programmeurs, mais a aussi quelques nouveaux types par rapport au C :

### Type `bool`

Un `bool` est une valeur booléenne, c'est à dire vraie ou fausse.\
Une variable booléenne ne peut être comparée qu'à 2 valeurs : `true` (vrai) ou `false` (faux)\
Tenter de comparer un `bool` à une variable d'un autre type renverra ainsi une erreur

Cependant, faire un cast de type à une valeur booléenne est possible, avec les types classiques ! (`char`, `int`, etc.)
- `false` deviendra `0`
- `true` deviendra `1`

Inversement, des casts de type sont possibles vers `bool` :
- Une valeur de `0` deviendra `false`
- N'importe quelle autre valeur deviendra `true` (même un nombre négatif !)

> [!IMPORTANT]
> Toutes les opérations ***relationnelles*** (`>`, `>=`, `<`, `<=`, `==`) ainsi que les opérateurs logiques (`&&`, `||`, `!`) renvoient un `bool` en C++

Exemple :

```cpp
bool b = true;
int n = 0;
n = b; // Désormais, n == (int)true == 1

b = false;
n = -5;
b = n; // Désormais, b == (bool)-5 == true

std::cout << b == n; // Erreur : b et n sont de types différents

std::cout << (int)b == n; // Comparaison possible
                    // Affiche `false` : (int)true == 1 --> (int)true != n

std::cout << b == (bool)n;  // Comparaison possible
            // Affiche `true` : (bool)-5 == true --> b == (bool)-5
```

Tableau récapitulatif ligne par ligne :

| Expression                  |   `b`   |  `n`  | Commentaire |
| :-------------------------- | :-----: | :---: | :------------------------------------------------------------------------------------------------------------------------------------------ |
| `bool b = true`             | `true`  |       | `b` initialisé |
| `int n = 0`                 | `true`  |  `0`  | `n` initialisé |
| `n = b`                     | `true`  |  `1`  | `n` obtient la même valeur que `b`, mais transformée en `int` |
| `b = false`                 | `false` |  `1`  | `b` devient faux |
| `n = -5`                    | `false` | `-5`  | `n` devient -5 |
| `b = n`                     | `true`  | `-5`  | `b` obtient la même valeur que `n`, mais transformée en `bool` |
| `std::cout << b == n`       | `true`  |  `-5`  | Erreur : impossible de comparer deux variables de types différents |
| `std::cout << (int)b == n`  | `true`  |  `-5`  | On compare `n` (un `int`) et la _valeur de `b`_ transformée en `int`. Les deux sont de même type et de valeurs différentes : comparaison possible et fausse |
| `std::cout << b == (bool)n` | `true`  |  `-5`  | On compare `b` (un `bool`) et la _valeur de `n`_ transformée en `bool`. Les deux sont de même type et de même valeur : comparaison possible et vraie |

### Type `auto`

Le mot-clé `auto` est un peu spécial. Bien qu'il ne soit pas lui-même un type, il agit comme un mot-clé de type, et permet au programme de détecter le type d'une variable.

Cela permet notamment de gagner du temps lors de la déclaration de variables ayant un type très long

> [!IMPORTANT]
> Comme `auto` détecte et assigne un type à une variable, cette variable ***doit*** être initialisée. Concrètement :
> ```cpp
> auto a = 5; // Valide : variable déclarée & initialisée
> auto b; // Invalide : variable déclarée, mais non initializée
> ```
> Une variable n'est pas forcément initialisée avec un `=`, par exemple :
> ```cpp
> auto a { 5.7f } // a est désormais un `float`
> ```

## Références

> [!IMPORTANT]
> Les références ne sont _pas_ des pointeurs.\
> Les pointeurs existent aussi en C++, mais ont un comportement un peu différent des références

Les références sont un moyen, en C++, d'avoir accès à une variable spécifique, et de la modifier "à distance".\
On peut les voir comme des "alias" à cette variable

Les références ont 2 gros avantages sur les pointeurs :
- Sûreté du code : une référence est liée à une variable _spécifique_, et non pas à un emplacement mémoire quelconque. Ainsi, aucune chance d'accéder à un emplacement de mémoire interdit et de faire planter le programme
- Facilité d'utilisation : la référence se fait automatiquement, plus besoin d'utiliser `*` ou `&` comme avec les pointeurs (excepté lors de la déclaration)

Pour déclarer une référence, c'est un peu comme un pointeur :
```cpp
type_t* pointeur = &variable; // Pointeur
type_t& reference = variable; // Référence
```

> [!WARNING]
> Une référence doit être _initialisée_ avec la variable pour laquelle elle sert d'alias. Plus concrètement :
> ```cpp
> type_t* pointeur; // Valable, un pointeur peut ne pas être initialisé
> type_t& ref; // Erreur : Une référence DOIT être initialisée
> ```

Une référence agit comme un pointeur _implicite_, et a la même syntaxe qu'une variable. Ainsi, toute _opération_ effectuée sur une variable est aussi effectuable sur une référence :

```cpp
int n = 10;
int& i = n;

n++; // n == 11
i++; // n == 12

std::cout << i; // Affichera : 12

i /= 2; // n == 12 / 2 == 6
i = i % 5; // n == 6 % 5 == 1
```

Dans le cas où l'on a une référence d'une instance de classe, l'opérateur `.` est aussi utilisable :

```cpp
class classe_t {
    public:
        int x = 0;
        int square(){ return this.x * this.x; }
}

classe_t obj(); // Nouvelle instance de classe
classe_t& alias = obj; // Alias de `obj`

std::cout << obj.x << " == " << alias.x;
// Affiche : 0 == 0

std::cout << alias.square();
// Affiche : 25
```

### Passage par référence

En C, on peut passer les paramètres d'une fonction soit par valeur, soit par adresse (avec des pointeurs).\
En C++, on peut _aussi_ les passer par référence !\
Cependant, contrairement aux pointeurs, aucun caractère spécial `&` ou `*` ne doit être ajouté pour passer un paramètre par référence

Exemple : 
```cpp
int x = 1, y = 2, z = 3;

int fonction1(int a, int* b, int& c){
    a = 2 // a est une copie de x, x n'est pas modifié 
    *b = 3 // b est un pointeur vers y, y est modifié
    c = 5 // c est un alias vers z, z est modifié
    return a + *b + c;
}

// Pendant la fonction : x non modifié, y et z modifiés
int resultat = fonction1(x, &y, z);

std::cout << x << "  " << y << "  " << z << " | " << resultat;
// Affichera : 1  3  5 | 9
```

## Expressions constantes

Il y a 3 types d'expressions constantes. Ces expressions peuvent être des variables (appellées _constantes_ à la place de _variables_ du coup), ou des méthodes (fonctions)

> [!NOTE]
> Aucun de ces modificateurs n'est un _type_. Ils servent juste à spécifier un certain "comportement" de la fonction ou la variable à laquelle ils sont appliqués\
> Ces modificateurs peuvent d'ailleurs être ajoutés à n'importe quelle variable de (quasiment) n'importe quel type !

Les trois modificateurs `const` sont assez étroitement liés, et pour bien comprendre ce qu'ils font, on va d'abord découper la "vie" d'un programme en 3 grandes étapes :
- La programmation
- La compilation
- L'exécution

Tout d'abord, la programmation. Rien de spécial à ce moment-là, l'ordi n'intervient pas

Puis, la compilation. Ici, le compilateur va vérifier si des erreurs existent, puis va optimiser le code et le transformer en exécutable (oui les 🤓 il y a plus d'étapes que ça, je simplifie)

Enfin, l'exécution du programme. Une fois que le programme est compilé en exécutable, on peut l'exécuter n'importe quand, sans avoir à le re-compiler (excepté si on a modifié le code). La plupart du code écrit est _**évalué**_ à ce moment-là.

### Le modificateur `const`

Le C++ étant un langage assez étrange, la plupart des mots-clés ont des utilisations assez diverses, c'est notamment le cas de `const`. Mais pour le moment, on verra seulement son utilisation sur les _variables_.

Quand on voit const, on pense tout de suite à "constante", ce qui est l'entièreté de ce que ce mot-clé fait. Il rend une variable _constante_, c'est-à dire **non modifiable**.\
Une fois qu'une constante est déclarée, on ne peut plus la modifier.\
Ainsi, il faut ***obligatoirement*** l'initialiser avec une valeur

Exemple :

```cpp

const int n = 10; // Marche !
const long a = uneFonction(); // Marche aussi !
const int b; // Erreur : `b` doit être initialisée avec une valeur

for(int i = 0; i < n; i++) a++ // Erreur de compilation
```

On tente de modifier une _constante_, ainsi le compilateur nous transmet une erreur

### Le modificateur `constexpr`

Comme `const`, mais avec un ajout majeur et une restriction :

Pour les constantes, on va **tenter** de leur attribuer une valeur à la _compilation_, plutôt qu'à _l'exécution_. \
Cependant, si la valeur ne peut pas être attribuée à la compilation et peut l'être à l'exécution, le code ne renverra pas d'erreur\

> [!CAUTION]
> Les constantes `constexpr` ne ***PEUVENT PAS*** être des instances de classe.\
> _Quelques_ dérogations à cette règle existent, mais c'est trop complexe pour ce qu'on voit, si ça vous intéresse allez regarder la docu CPPreference [[2]](#constexpr)

Pour les fonctions (et méthodes), c'est la même théorie, mais un peu plus compliqué.\
Si la valeur de sortie de la fonction `constexpr` est donnée à une constante `constexpr`, alors cette constante sera évaluée lors de la compilation.\
S'il s'agit d'une variable/constante non `constexpr`, alors tant pis, la fonction sera évaluée à l'exécution.

Prenons l'exemple suivant :

```cpp
int square(n){ return n * n; } // Fonction classique
constexpr int squareCE(n){ return n * n; } // Fonction constexpr

constexpr int n = 10; // Marche à la compilation

constexpr int a = square(n); // `square` n'est pas `constexpr` : Marche à l'exécution
constexpr int b = squareCE(n); // `squareCE` est `constexpr` : Marche à la compilation

int c = squareCE(n); // `squareCE` est bien `constexpr` mais pas `c` : Marche à l'exécution
```

Évaluer les variables à l'exécution a 2 avantages majeurs :

- Temps d'évaluation moins long à la compilation qu'à l'exécution
- Expression évaluée _seulement_ à la compilation, et non pas à _chaque_ redémarrage de l'exécutable

Évidemment, c'est rarement plus de quelques milli ou nano secondes de gagnées, mais pour de gros projets avec des centaines de variables `constexpr`, ça peut faire une différence

**_CEPENDANT_** !!!!!

Pour être évaluées à la compilation, les fonctions `constexpr` doivent respecter quelques règles [[2]](#constexpr) :
1. Ne doit pas être une _coroutine_ (pas encore vu)
2. Si la fonction est un constructeur ou un destructeur, la classe ne doit pas hériter d'une classe `virtual`
3. Pour les fonctions `template` ou les méthodes membres de classes `template` (pas encore vu) : Au moins _une_ des spécialisations de la template doit satisfaire les 2 premières règles

C'est très flou pour le moment, mais ça sera utile plus tard dans l'année

### Le modificateur `consteval`

Celui-ci ne s'applique qu'aux fonctions/méthodes.

Vous voyez comment `constexpr` donne aux fonctions la ***possibilité*** d'être évaluées à la compilation ? \
Eh bien `consteval` les ***force*** à le faire. Si une fonction `consteval` ne _peut_ pas être évaluée à la compilation, une erreur est renvoyée.

Outre cela, `consteval` a exactement les mêmes caractéristiques que `constexpr`, et peut être considéré comme une _extension_ de cela

Un petit exemple pour la route :

```cpp
int square(n){ return n * n; } // Fonction classique
consteval int squareCE(n){ return n * n; } // Fonction consteval

constexpr int n = 10; // Marche à la compilation

constexpr int a = square(n); // `square` n'est pas `constexpr` : Marche à l'exécution
constexpr int b = squareCE(n); // `squareCE` est `consteval` et `b` est `constexpr` : Marche à la compilation

int c = squareCE(n); // `squareCE` est bien `consteval` mais `c` n'est pas `constexpr` :
                     // Erreur car impossibilité d'évaluer à la compilation
```

## Sources & Documentation

1. <a id="cours">[Cours de Mosbah - n°1](https://myjunia.sharepoint.com/teams/JUNIA_2024_2025_ISEN_CIR2_S1/Shared%20Documents/General/Supports%20de%20cours/01%20Introduction%20C++.pdf)</a>
2. <a id="constexpr">[Docu `constexpr` - CPPreference](https://en.cppreference.com/w/cpp/language/constexpr)</a>
# Bases du C++

<span style="color: gray">_Écrit par Léo Lewandowski_</span>

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

> [!WARNING]
> Je vais utiliser beaucoup les termes "constante" et "variable" dans ce document, donc pour mettre au clair :
> 
> - Une _variable_ peut changer
> - Une _constante_ ne peut pas changer
>
> Outre cette différence, elles sont exactement pareilles

Ce document est déjà beaucoup trop long, alors rentrons dans le vif du sujet !

## Modificateurs



## Expressions constantes

Il y a 3 types d'expressions constantes. Ces expressions peuvent être des variables (appellées _constantes_ à la place de _variables_ du coup), ou des méthodes (fonctions)

> [!IMPORTANT]
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
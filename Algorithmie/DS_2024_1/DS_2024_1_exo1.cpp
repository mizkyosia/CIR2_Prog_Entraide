#include <iostream>
#include <algorithm>
#include <vector>

// -------------------- PARTIE 1 ----------------------

class A {
public:
    A() {
        std::cout << "A";
    }
    virtual void f() const = 0;
};

class B : public A {
    int n;

public:
    B(int p = 1) : n(p) {
        std::cout << "B";
    }
    void f() const {
        std::cout << "B" << n;
    }
};

class C : public A {
    int n;

public:
    C(int p = 2) : n(p) {
        std::cout << "C";
    }
    void f() const {
        std::cout << "C" << n;
    }
};

class D : public C {
    int n;

public:
    D(int p = 4) : C(p) {
        std::cout << "D";
    }
};

void print(const A* a) {
    a->f();
}
void print(const B& a) {
    a.f();
}
void print(const C& a) {
    a.f();
}
void print(const D& a) {
    a.f();
}

// -------------------- PARTIE 2 ----------------------

void tab_test(unsigned size, int max_rand_val = 100){
    // Création et allocation du tableau de façon dynamique (en utilisant new)
    int* tab = new int[size];

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Remplissage du tableau avec des valeurs aléatoires
    for(int i = 0; i < size; i++) {
        // Valeurs comprises dans l'intervalle [0, max_rand_val]
        tab[i] = (rand() * (float)max_rand_val) / RAND_MAX;
    }

    std::cout << "\nTableau non trié : ";
    for(int i = 0; i < size; i++) std::cout << tab[i] << ", ";

    // Tri des valeurs
    std::sort(tab, tab + size);

    std::cout << "\nTableau trié : ";
    for(int i = 0; i < size; i++) std::cout << tab[i] << ", ";

    // Suppression du tableau
    // Obligation d'utiliser delete car on a créé le tableau avec new
    delete [] tab;
}

// -------------------- PARTIE 3 ----------------------

template<typename T>
T vector_sum(std::vector<T> vec){
    // On initialise un objet de type T, qui servira de point de départ pour la somme
    // On ne peut pas mettre `= 0` car ce n'est pas forcément un type numérique
    T sum(0);

    // On itère dans vec, depuis le début jusqu'à la fin
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        // On ajoute chacun des éléments du vecteur à la somme
        sum += *iter;
    }

    // Enfin, on retourne la somme
    return sum;
};

int main(){
    B b(3);
    C c;
    D d;
    A* ab = &b;
    A* ac = &c;
    A* ad = &d;

    print(ab);
    print(ac);
    print(ad);
    print(b);
    print(c);
    print(d);

    std::cout << "Tableau test : \n";

    tab_test(20);

    std::cout << "\nSomme vecteur (1, 2, 3, 4, 5) :";

    std::vector<int> vec = {1, 2, 3, 4, 5};

    int val = vector_sum(vec);

    std::cout << val << std::endl;

    return 0;
}
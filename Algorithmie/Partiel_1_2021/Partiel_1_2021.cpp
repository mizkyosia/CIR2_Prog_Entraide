#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <complex>

using std::complex;
using std::cout;
using std::endl;
using std::ostream;

// -------------------- EXERCICE 1 ------------------
// ---- Partie A

// Functor
struct Comp
{
public:
    bool operator()(int x, int y)
    {
        return x < y;
    }
};

// Function
bool comp(int x, int y)
{
    return x < y;
}

// ---- Partie B
template <typename T>
T vector_sum(std::vector<T> vec)
{
    T total(0); // Initialisation à 0

    // Itération à travers les éléments du vecteur (peut aussi se faire avec vec.begin() et v.end())
    for (T item : vec)
    {
        total += item;
    }

    return total;
}

// -------------------- EXERCICE 2 ------------------
// ---- Partie A

template <typename _T, size_t _SIZE>
class My_vector
{
private:
    _T *vec_;

public:
    // Taille du vecteur
    size_t get_size() const
    {
        return _SIZE;
    }

    My_vector() : vec_(new _T[_SIZE]{0}) {}; // Crée le tableau interne et l'initialise à 0
    ~My_vector()
    {
        delete[] vec_; // Suppression du tableau (NE PAS OUBLIER LES CROCHETS)
    }
    _T &operator[](const size_t &ind) // Accès classique à un élément du vecteur
    {
        return vec_[ind];
    }
    _T operator[](const size_t &ind) const // Accès pour un vecteur const (copie l'élément plutôt que de renvoyer une référence)
    {
        return vec_[ind];
    }

    template <typename _T1>
    _T1 operator*(const My_vector<_T1, _SIZE> &v) // Produit scalaire
    {
        _T1 res(0);                        // Initialisation à 0 du résultat
        for (size_t i = 0; i < _SIZE; i++) // Itération à travers les éléments des 2 vecteurs
        {
            res = res + static_cast<_T1>(vec_[i]) * v[i]; // Cast l'élément de ce vecteur dans le bon type, puis multiplie par le deuxième élément
        }
        return res;
    }

    template <typename _T1>
    My_vector<_T1, _SIZE> operator*(const _T1 &val)
    {
        My_vector<_T1, _SIZE> out; // Initialisation de l'output

        for (size_t i = 0; i < _SIZE; i++)
        {
            out[i] = static_cast<_T1>(vec_[i]) * val; // Cast l'élément de ce vecteur dans le bon type, puis multiplie par le nombre donné
        }

        return out;
    }

    template <typename T, size_t SIZE>
    friend std::ostream &operator<<(std::ostream &os, const My_vector<T, SIZE> &v); // Surcharge de l'opérateur <<
};

template <typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &os, const My_vector<T, SIZE> &v)
{
    for (auto i = 0; i < SIZE; i++)
        os << v[i] << " "; // Affiche chacun des nombres séparés par un espace
    return os;
}

// ----- Partie B -----

template <typename _T, size_t _SIZE>
class My_square_matrix
{
    My_vector<_T, _SIZE> *mat_;

public:
    size_t get_size() const
    {
        return _SIZE;
    }
    My_square_matrix() : mat_(new My_vector<_T, _SIZE>[_SIZE]) // Initialise le tableau de vecteurs
    {
    }
    ~My_square_matrix()
    {
        delete[] mat_; // Suppression du tableau (NE PAS OUBLIER LES CROCHETS)
    }
    My_vector<_T, _SIZE> &operator[](const size_t &ind) // Accès au vecteur via référence
    {
        return mat_[ind];
    }
    My_vector<_T, _SIZE> operator[](const size_t &ind) const // Copie du vecteur donné
    {
        return mat_[ind];
    }

    template <typename _T1>
    My_vector<_T1, _SIZE> operator*(My_vector<_T1, _SIZE> &v) // Produit matrice * vecteur, renvoyant un vecteur
    {
        My_vector<_T1, _SIZE> out;

        for (auto i = 0; i < _SIZE; i++)
            out[i] = mat_[i] * v; // On ajoute le produit scalaire des 2 vecteurs

        return out;
    }

    template <typename _T1>
    My_square_matrix<_T1, _SIZE> operator*(My_square_matrix<_T1, _SIZE> &m)
    {
        My_square_matrix<_T1, _SIZE> out;

        for (auto i = 0; i < _SIZE; i++)
        {
            for (auto j = 0; j < _SIZE; j++)
            {
                // Formule de multiplication de matrice carrée : c_ij = Sum(a_ik * b_kj) avec 0 <= k < taille de la matrice
                for (auto k = 0; k < _SIZE; k++)
                {
                    out[i][j] += static_cast<_T1>(mat_[i][k]) * m[k][j];
                }
            }
        }

        return out;
    }

    template <typename T, size_t SIZE>
    friend std::ostream &operator<<(std::ostream &os, const My_square_matrix<T, SIZE> &v); // Surcharge de l'opérateur <<
};

template <typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &os, const My_square_matrix<T, SIZE> &v)
{
    for (auto i = 0; i < SIZE; i++)
        os << v.mat_[i] << " "; // Affiche chacun des vecteurs, séparés par un espace

    return os;
}

int main()
{
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-100, 100); //(min, max)
    std::vector<int> v;
    v.reserve(100);
    for (int i = 0; i < 100; ++i)
    {
        v.push_back(dist(rng)); // génération aléatoire de valeurs
    }

    std::sort(v.begin(), v.end(), Comp()); // Trie avec functor (on doit créer une instance de la structure pour pouvoir l'utiliser)
    std::sort(v.begin(), v.end(), comp);   // Trie avec une fonction
    std::sort(v.begin(), v.end(), [](int x, int y)
              { return x < y; }); // Trie avec une fonction lambda

    // Effectue la somme du vecteur
    int sum = vector_sum(v);
    cout << "Sum of vector : " << sum << endl;

    // -------------------------------- EXERCICE 2 ------------------------------

    constexpr size_t size = 3;
    My_vector<float, size> v1;
    My_vector<float, size> v2;
    My_vector<complex<float>, size> v3;

    My_square_matrix<float, size> m1;
    My_square_matrix<float, size> m2;

    for (size_t i = 0; i < size; ++i)
    {
        v1[i] = i;
        v2[i] = i + 1;
        v3[i] = complex<float>(i + 1, i);
        for (size_t j = 0; j < size; ++j)
        {
            m1[i][j] = 1;
            m2[i][j] = i * m1.get_size() + j;
        }
    }

    cout << "get_size :" << v1.get_size() << endl;
    cout << "V1 : " << v1 << endl;
    cout << "get_size :" << v1.get_size() << endl;
    cout << "V2 : " << v2 << endl;
    cout << "get_size :" << v3.get_size() << endl;
    cout << "V3 : " << v3 << endl;
    cout << "V1*V2 : " << v1 * v2 << endl;
    cout << "V1*V3 : " << v1 * v3 << endl;
    cout << "V1*(2,1) : " << v1 * complex<float>(2, 1) << endl;

    cout << "M1 : " << m1 << endl;
    cout << "M2 : " << m2 << endl;
    cout << "M2*V1 : " << m2 * v1 << endl;
    cout << "M2*V3 : " << m2 * v3 << endl;
    cout << "M1*M2 : " << m1 * m2 << endl;

    return EXIT_SUCCESS;
}
#include <iostream>
#include <vector>
#include <cmath>

class Big_N_N
{
private:
    std::vector<unsigned short> tab_;

public:
    Big_N_N operator+(const Big_N_N &other) const;
    Big_N_N operator*(const unsigned short &nb) const;
    Big_N_N operator*(const Big_N_N &other) const;

    friend Big_N_N &operator>>(Big_N_N &other, const int &nb);
    friend std::ostream &operator<<(std::ostream &os, const Big_N_N &other);
};

// -------------------- PARTIE 1 ----------------------

Big_N_N &operator>>(Big_N_N &other, const int &nb)
{
    if (nb <= 0)
        return other;

    int carry = nb;

    // On calcule le nombre de chiffres à insérer
    int nb_digits = std::log10(nb) + 1;

    // On insère le bon nombre de chiffres directement, puis on remplira avec les chiffres plus tard
    other.tab_.insert(other.tab_.end(), nb_digits, 0);

    // Tant qu'il reste des chiffres à placer
    for (auto i = other.tab_.rbegin(); i != other.tab_.rend() && carry > 0; i++)
    {
        // On insère le reste par 10 de `carry`, soit son dernier chiffre
        *i = carry % 10;

        // On fait une division d'un `int`, ainsi on arrondit le résultat à la partie entière
        // Exemple : 12 / 10 = 1
        carry /= 10;
    }

    return other;
}

// -------------------- PARTIE 2 ----------------------

std::ostream &operator<<(std::ostream &os, const Big_N_N &other)
{
    // Si le tableau est vide
    if (other.tab_.size() == 0)
    {
        os << 0;
        return os;
    }

    // Doit-on afficher les chiffres ?
    bool display = false;

    // On traverse tous les chiffres du tableau
    for (auto i = other.tab_.begin(); i != other.tab_.end(); i++)
    {
        // Si on trouve un chiffre qui n'est pas un 0, ou qu'on est arrivés au dernier chiffre du tableau
        // on commence à afficher les chiffres
        if (*i != 0 || i == other.tab_.end() - 1)
            display = true;

        // On affiche les chiffres, si on doit
        // if(display)
        os << *i;
    }

    // Enfin, on renvoie l'output
    return os;
}

// -------------------- PARTIE 3 ----------------------

Big_N_N Big_N_N::operator+(const Big_N_N &other) const
{
    // Création du résultat
    Big_N_N output;

    // On copie le nombre `other` dans le nouveau
    output.tab_.insert(output.tab_.begin(), other.tab_.begin(), other.tab_.end());

    // La retenue des additions
    unsigned short carry = 0;

    // On itère à travers les chiffres du nouveau nombre
    // L'itération est à l'envers, car on doit commencer par les derniers chiffres
    auto j = output.tab_.rbegin();

    // Et à travers ceux de l'ancien (à l'envers aussi)
    for (auto i = tab_.rbegin(); i != tab_.rend(); i++)
    {
        // Calcul du chiffre actuel
        auto x = *i + carry;

        // Si on est à la fin de l'output
        if (j == output.tab_.rend())
        {
            // On lui rajoute une case
            output.tab_.insert(output.tab_.begin(), x % 10);
        }
        else
        {
            // Sinon, on rajoute au chiffre actuel
            x += *j;
            // On garde le dernier chiffre
            *j = x % 10;
            // Et on augmente l'itérateur
            j++;
        }

        // On prend la retenue
        carry = x / 10;
    }

    std::cout << "(output = " << output << ", carry = " << carry << ')' ;

    // // Tant qu'on est pas à la fin de l'itérateur
    for (j; j != output.tab_.rend(); j++) {
        std::cout << 'a';
        // Pareil qu'au dessus
        // auto x = *j + carry;
        // *j = x % 10;
        // carry = x / 10;
    }

    if(carry > 0) {
        // La retenue ne peut pas avoir 2 chiffres lors d'une addition
        // ainsi, on l'ajoute telle quelle à la fin de l'output
        output.tab_.insert(output.tab_.begin(), carry);
    }

    // Enfin, on renvoie l'output
    return output;
}

// -------------------- PARTIE 4 ----------------------

Big_N_N Big_N_N::operator*(const unsigned short &nb) const
{
    // Création du résultat
    Big_N_N output;

    // Si on multiplie par 0, on renvoie 0 (OPTIONNEL)
    if (nb == 0)
    {
        output.tab_.insert(output.tab_.begin(), 0);
        return output;
    }

    // On copie ce nombre dans le nouveau
    output.tab_.insert(output.tab_.begin(), tab_.begin(), tab_.end());

    // Définition de la retenue
    int carry = 0;

    // On calcule le nombre de chiffres à insérer en plus
    int nb_digits = std::log10(nb);

    // On insère ensuite ces chiffres dans le vecteur, afin qu'il y
    // ait toujours assez de place pour les nombres à ajouter
    output.tab_.insert(output.tab_.begin(), nb_digits, 0);

    // On itère à travers tous les chiffres (du dernier au premier)
    for (auto i = output.tab_.rbegin(); i != output.tab_.rend(); i++)
    {
        // Calcul
        auto x = (*i) * nb + carry;
        // Dernier chiffre
        *i = x % 10;
        // Retenue
        carry = x / 10;
    }

    // Grâce à l'allocation du nombre de chiffres plus haut, la retenue est forcément vide
    // on n'a donc pas à gérer le cas où elle ne l'est pas

    return output;
}

// -------------------- PARTIE 5 ----------------------

Big_N_N Big_N_N::operator*(const Big_N_N &other) const
{
    // Création du résultat
    Big_N_N output;

    // Définition de la retenue
    int carry = 0;

    // On calcule le nombre de chiffres dont on aura besoin
    int nb_digits = tab_.size() + other.tab_.size();

    // On insère ensuite ces chiffres dans le vecteur, afin qu'il y
    // ait toujours assez de place pour les nombres à ajouter
    output.tab_.insert(output.tab_.begin(), nb_digits, 0);

    // On itère à travers tous les chiffres (du dernier au premier)
    for (int j = 0; j < tab_.size(); j++)
    {
        // On parcourt le nombre
        for (int i = 0; i < other.tab_.size(); i++)
        {
            // Calcul
            auto x = other.tab_[i] * tab_[j] + carry;
            // Garde dernier chiffre
            output.tab_[i + j] = x % 10;
            // Retenue
            carry = x / 10;
        }
    }

    // Grâce à l'allocation du nombre de chiffres plus haut, la retenue est forcément vide
    // on n'a donc pas à gérer le cas où elle ne l'est pas

    return output;
}

int main()
{
    Big_N_N a1;
    a1 >> 123;
    a1 >> 4 >> 5;

    Big_N_N a2;
    a2 >> 5 >> 3;

    std::cout << "a1 = " << a1 << std::endl;
    std::cout << "a2 = " << a2 << std::endl;
    std::cout << "a3 = " << (a1 + a2) << " = " << 12345 + 53 << std::endl;
    std::cout << "a4 = " << a1 * 5 << " = " << 12345 * 5 << std::endl;
    std::cout << "a5 = " << a1 * a2 << " = " << 12345 * 53 << std::endl;

    return 0;
}

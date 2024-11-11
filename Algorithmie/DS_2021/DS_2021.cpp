#include <string>
#include <iostream>

using namespace std;

class A
{
public:
    virtual void f() const = 0;
};
class B : public A
{
    int n;

public:
    B(int p = 1) : n(p) {}
    void f() const { std::cout << "B" << n; }
};
class C : public A
{
    int n;

public:
    C(int p = 2) : n(p) {}
    void f() const { std::cout << "C" << n; }
};
class D : public C
{
    int n;

public:
    D(int p = 4) : C(p) {}
};
void print(const A *a) { a->f(); }
void print(const B &a) { a.f(); }
void print(const C &a) { a.f(); }
void print(const D &a) { a.f(); }

class E
{
private:
    int x;

public:
    E()
    {
        x = 0;
        std::cout << "1";
    }
    E(int px)
    {
        x = px;
        std::cout << "2";
    }
    E(const E &pa)
    {
        x = pa.x;
        std::cout << "3";
    }
};

class F
{
private:
    E a;
    int y;

public:
    F(const E &pa = E()) : a(pa) { std::cout << "4"; }
    F(const E &pa, int py) : y(py)
    {
        a = pa;
        std::cout << "5";
    }
};

int decalage(const int &lettre, const int &nb_decal)
{
    int code = toupper(lettre);
    if (code > 64 && code < 91)
    {
        code = (code + nb_decal - 65) % (90 - 65 + 1) + 65;
        return code;
    }
    return ' ';
}

int decalage_inverse(const int &lettre, const int &nb_decal)
{

    if (lettre > 64 && lettre < 91)
    {
        int decal = lettre - 65 - nb_decal;
        if (decal < 0)
        {
            return 90 + decal + 1;
        }
        return decal + 65;
    }
    return ' ';
}

class Chiffrement
{
private:
public:
    virtual string chiffrement(const string &texte_a_chiffrer) const = 0;
    virtual string dechiffrement(const string &texte_a_dechiffrer) const = 0;
    friend ofstream &operator<<(ofstream &os, const Chiffrement *chf);
    friend ifstream &operator>>(ifstream &os, Chiffrement *chf);
    string texte_;
};

class Chiffrement_Cesar : public Chiffrement
{
private:
    const int nb_decal_;

public:
    Chiffrement_Cesar(const int &nb_decal) : nb_decal_(nb_decal){};
    string chiffrement(const string &texte_a_chiffrer) const;
    string dechiffrement(const string &texte_a_dechiffrer) const;
};

class Chiffrement_Vigenere : public Chiffrement
{
private:
    const string password_;

public:
    Chiffrement_Vigenere(const string &password) : password_(password){};
    string chiffrement(const string &texte_a_chiffrer) const;
    string dechiffrement(const string &texte_a_dechiffrer) const;
};

string Chiffrement_Cesar::chiffrement(const string &texte_a_chiffrer) const
{
    int count = 0;
    string ch(texte_a_chiffrer.size(), ' ');
    for (auto c : texte_a_chiffrer)
    {
        ch[count++] = decalage(c, nb_decal_);
    }
    return ch;
}

string Chiffrement_Cesar::dechiffrement(const string &texte_a_dechiffrer) const
{
    int count = 0;
    string ch(texte_a_dechiffrer.size(), ' ');
    for (auto c : texte_a_dechiffrer)
    {
        ch[count++] = decalage_inverse(c, nb_decal_);
    }
    return ch;
}

string Chiffrement_Vigenere::chiffrement(const string &texte_a_chiffrer) const
{
    // int count_password = 0;
    int count = 0;
    char code;
    const auto lenght = password_.size();
    string ch(texte_a_chiffrer.size(), ' ');
    for (auto c : texte_a_chiffrer)
    {
        ch[count] = decalage(c, password_[count % lenght] - 65);
        ++count;
    }
    return ch;
}

string Chiffrement_Vigenere::dechiffrement(const string &texte_a_dechiffrer) const
{
    int count = 0;
    const auto lenght = password_.size();
    string ch(texte_a_dechiffrer.size(), ' ');
    for (auto c : texte_a_dechiffrer)
    {
        ch[count] = decalage_inverse(c, password_[count % lenght] - 65);
        ++count;
    }
    return ch;
}

ostream &operator<<(ostream &flux, const Chiffrement *chf)
{
    flux << chf->dechiffrement(chf->texte_);
    return flux;
}

istream &operator>>(istream &flux, Chiffrement *chf)
{
    string str;
    std::getline(flux, str);
    chf->texte_ = chf->chiffrement(str);
    return flux;
}

int main()
{
    // A a;
    B b(3);
    C c;
    D d;
    A *ab = &b;
    A *ac = &c;
    A *ad = &d;
    print(ab);
    std::cout << std::endl;
    print(ac);
    std::cout << std::endl;
    print(ad);
    std::cout << std::endl;
    print(b);
    std::cout << std::endl;
    print(c);
    std::cout << std::endl;
    print(d);
    std::cout << std::endl;

    std::cout << "-- A --\n";
    E a0;
    std::cout << std::endl;
    E a1(3);
    std::cout << std::endl;
    E a2(a1);
    std::cout << std::endl;
    E a3 = a2;
    std::cout << std::endl;
    a3 = a1;
    std::cout << std::endl;
    std::cout << "-- B --\n";
    F b0(a0, 3);
    std::cout << std::endl;
    F b1(a1);
    std::cout << std::endl;
    F b2;
    std::cout << std::endl;

    Chiffrement_Cesar Cesar(3);

    Chiffrement *chiff = &Cesar;

    cin >> chiff;
    cout << chiff << endl;

// Par simplicité le mot de passe est toujours en majuscule
    Chiffrement_Vigenere Vigenere("PASSWORD");

    chiff = &Vigenere;

    cin >> chiff;
    cout << chiff << endl;

    return 0;
}

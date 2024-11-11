#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template<typename T, int testing_val>
class Classe1 {
    public:
    T val;
    const int val2 = testing_val;

    template<typename T2>
    void test(T2 v){
        std::cout << v;
    }
    
};

template<typename T>
class Classe2 : public Classe1<T, 3> {

};

template<typename T1, typename T2, int a>
int add(T2 var1, T1 var2) {
    return var1 + var2 + a;
}

int main()
{
    int a = add  <int, int, 1> (1, 2);

    // int b = add(1.5f, 2.5f);
    
    // int c = add(1.5f, 1);

    // int d = add("abc", 5);

    Classe1<int, 3> test;
    test.val;

    Classe1<float, 5> test2;
    test2.val;

    test2.test<int>(4);


    std::array<int, 4> arr = {1, 2, 3, 4};
    
    int* tab = arr.data();

    std::vector<int> vec = {1, 2, 3, 4};

    vec.push_back(5);

    vec.insert(vec.begin() + 2, 4, 5);

    std::vector<int> temp = {100, 101, 102};

    vec.insert(vec.begin() + 1, temp.rbegin() + 1, temp.rend());

    vec.erase(vec.begin() + 1, vec.end() - 1);

    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

#include <cstdlib>

template <class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> &a)
{
    if (out) {
        for (int i = 0; i < a.size(); ++i) {
            out << "a[" << i << "] = " << a[i] << std::endl;
        }
    }
    return out;
}

template <class T> class MyLess
{
  public:
    bool operator()(const T &a, const T &b) { return a > b; }
};

int main(void)
{
    std::vector<double> a;

    for (int i = 0; i < 10; ++i) {
        a.push_back((rand() % 100) / 10.0);
    }
    std::cout << a << std::endl;
    a.push_back(0);
    std::cout << "Add one more element" << std::endl << a;

    std::sort(a.begin(), a.end(), MyLess<double>());
    std::cout << std::endl << "Sorted array" << std::endl << a;

    return 0;
}

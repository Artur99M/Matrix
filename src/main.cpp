#include <iostream>
#include <cassert>
#include "../include/Matrix.hpp"

int main()
{
    size_t n;
    std::cin >> n;
    assert (std::cin.good());

    long double* data = new long double[n * n]{};
    for (size_t i = 0; i < n * n; i++)
    {
        // std::cerr << i << std::endl;
        std::cin >> data[i];
        assert (std::cin.good());
    }
    matrix::Matrix<long double> M {n, data};
    // std::cerr << "Matrix was made\n";
    delete[] data;
    std::cout << static_cast<long long>(M.det());
}

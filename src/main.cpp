#include <iostream>
#include <cassert>
#include "../include/Matrix.hpp"

int main()
{
    size_t n;
    std::cin >> n;
    assert (std::cin.good());

    double* data = new double[n * n]{};
    for (size_t i = 0; i < n * n; i++)
    {
        std::cin >> data[i];
        assert (std::cin.good());
    }
    matrix::Matrix<double> M {n, data};
    std::cerr << "Matrix was made\n";
    delete[] data;
    std::cout.precision (0);
    std::cout << M.det();
}

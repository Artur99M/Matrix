#include <iostream>
#include <cassert>
#include "Matrix.hpp"

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
    std::cout.precision(12);
    double answer_d = M.det();
    int answer_i = static_cast<int>(answer_d);
    if (answer_d - answer_i < 0.5)
        std::cout << answer_i << std::endl;
    else
        std::cout << (answer_i + 1) << std::endl;
}

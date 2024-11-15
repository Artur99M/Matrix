#include"../include/Matrix.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>


namespace matrix
{

    std::ostream& operator<<(std::ostream& os, Matrix<double> M)
    {
        for (size_t i = 0; i < M.size(); i++)
        {
            for (size_t j = 0; j < M.size(); j++)
                os << M.at(i, j) << ' ';
            os << std::endl;
        }
        return os;
    }

    static const double Eps = 1e-10;
    template <class T>
    Matrix<T>::Matrix(size_t sz) : sz_(sz), data_(new T[sz_ * sz_])
    {}

    // template <class T>
    // Matrix<T>::Matrix (size_t sz, T* data) : sz_(sz), data_(new T[sz_ * sz_])
    // {
    //     if (data != nullptr)
    //         std::copy(data, data + sz_ * sz_, data_);
    // }

    template <class T>
    Matrix<T>::Matrix (size_t sz, T** data) : Matrix<T> (sz, (T*) data)
    {}

    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& M) : Matrix<T> (M.sz_, M.data_)
    {}

    template <class T>
    Matrix<T>::Matrix(Matrix<T>&& M) : sz_(M.sz_), data_(M.data_)
    {
        M.data_ = nullptr;
    }

    template <class T>
    Matrix<T>::Matrix(size_t sz, std::vector<T> data) : Matrix<T> (sz)
    {
        std::copy (data.begin(), data.end(), data_);
    }


    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& M)
    {
        if (this == &M)
            return *this;

        sz_ = M.sz_;
        delete[] data_;
        data_ = new T[sz_ * sz_];
        std::copy(M.data_, M.data_ + sz_ * sz_, data_);
        return *this;
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator=(Matrix<T>&& M)
    {
        if (this == &M)
            return *this;

        std::swap (data_, M.data_);
        return *this;
    }

    template<> Matrix<double> Matrix<double>::to_triangle() const
    {
        Matrix<double> M = *this;
        for (size_t p = 0; p < sz_ - 1; p++)
        {
            double* non_nil_line = nullptr;
            for (size_t l = p; l < sz_; l++)
            {
                if ((-Eps > *(M.data_ + l * sz_ + p)) ||
                (*(M.data_ + l * sz_ + p) > Eps))
                {
                    non_nil_line = M.data_ + M.sz_ * l;
                    break;
                }
            }
            if (non_nil_line == nullptr)
            {
                //code
            }
            else
            {
                if (non_nil_line != M.data_ + sz_ * p)
                {
                    // double* swap_elem = new double[sz_]{};
                    // std::copy (non_nil_line, non_nil_line + M.sz_, swap_elem);
                    // std::copy (M.data_ + sz_ * p, M.data_ + (sz_ + 1) * p, non_nil_line);
                    // std::copy (swap_elem, swap_elem + sz_, M.data_ + sz_ * p);
                    // delete[] swap_elem;
                    // non_nil_line = M.data_ + sz_ * p;

                    for (size_t i = 0; i < sz_; i++)
                        *(M.data_ + sz_ * p + i) += non_nil_line[i];
                }
                double& a_p = non_nil_line[p];
                // std::cerr << __LINE__ << ": non_nil_line =";
                // for (size_t i = 0; i < sz_; i++)
                //     std::cerr << ' ' << non_nil_line[i];
                // std::cerr << std::endl;
                for (size_t q = p + 1; q < sz_; q++)
                {
                    double b_p = *(M.data_ + sz_ * q + p);
                    // std::cerr << __LINE__ << ": b_p = " << b_p << std::endl;
                    if ((-Eps > b_p) || (b_p > Eps))
                    {
                        for (size_t i = p; i < sz_; i++)
                          *(M.data_ + q * sz_ + i) -= (non_nil_line[i] * b_p / a_p);
                    }
                }
            }
            // std::cerr << "p = " << p << std::endl;
        }
        return M;
    }

    template<> double Matrix<double>::det() const
    {
        double answer = 1;
        // std::cerr << "I go to to_triangle\n";
        Matrix<double> M = to_triangle();
        // std::cerr << "I have finished to_triangle\n";
        // std::cerr << "I have matrix\n";
        // std::cerr << M;
        for (size_t i = 0; i < sz_; i++)
            if ((-Eps < (answer *= *(M.data_ + (sz_ + 1)* i)))
            && ((answer * *(M.data_ + (sz_ + 1)* i)) < Eps))
                break;
        return answer;

    }

} //namespace matrix

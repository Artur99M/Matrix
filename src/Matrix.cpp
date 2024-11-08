#include"../include/Matrix.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

namespace matrix
{

    template <class T>
    std::ostream& operator<<(std::ostream& os, Matrix<T> M)
    {
        for (size_t i = 0; i < M.sz_; i++)
        {
            for (size_t j = 0; j < M.sz_; j++)
                os << *(M.data_+ M.sz_ * i + j) << ' ';
            os << std::endl;
        }
        return os;
    }

    static const double Eps = 1e-10;
    template <class T>
    Matrix<T>::Matrix(size_t sz) : sz_(sz), data_(new T[sz_ * sz_])
    {}

    template <class T>
    Matrix<T>::Matrix (size_t sz, T* data) : sz_(sz), data_(new T[sz_ * sz_])
    {
        if (data != nullptr)
            std::copy(data, data + sz_ * sz_, data_);
    }

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
    void Matrix<T>::operator=(Matrix<T>&& M)
    {
        if (this == &M)
            return *this;

        std::swap (data_, M.data_);
        return *this;
    }

    template<> Matrix<double> Matrix<double>::to_triangle() const
    {
        Matrix<double> M = *this;
        for (size_t p = 0; p < sz_; p++)
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
                double& a_p = non_nil_line[0];
                for (size_t q = p + 1; q < sz_; q++)
                {
                    std::cerr << "101: non_nil_line =";
                    for (size_t i = 0; i < sz_; i++)
                        std::cerr << ' ' << non_nil_line[i];
                    std::cerr << std::endl;
                    double b_p = *(M.data_ + sz_ * q);
                    std::cerr << "106: b_p = " << b_p << std::endl;
                    if ((-Eps > b_p) || (b_p > Eps))
                        for (size_t i = 0; i < sz_; i++)
                            *(M.data_ + sz_ * q + i) -= non_nil_line[i] * b_p / a_p;
                    std::cerr << "110:\n";
                }
            }
        }
        std::cerr << "final of to_triangle" << std::endl;
        for (size_t i = 0; i < M.sz_; i++)
        {
            for (size_t j = 0; j < M.sz_; j++)
                std::cerr << *(M.data_+ M.sz_ * i + j) << ' ';
            std::cerr << std::endl;
        }
        return M;
    }

    template<> double Matrix<double>::det() const
    {
        double answer = 1;
        std::cerr << "I go to to_triangle\n";
        Matrix<double> M = to_triangle();
        std::cerr << "I have finished to_triangle\n";
        for (size_t i = 0; i < sz_; i++)
            if ((-Eps < (answer *= *(M.data_ + (sz_ + 1)* i)))
            && ((answer * *(M.data_ + (sz_ + 1)* i)) < Eps))
                break;
        return answer;

    }

} //namespace matrix

#include "Matrix.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <cassert>

#ifdef DEBUG
auto & debug = std::cerr;
#else
class debuging
{
    public:
    template <class T>
    debuging & operator<< (const T & elem)
    {
        return *this;
    }
};

debuging debug;
#endif


namespace matrix
{

    std::ostream& operator<<(std::ostream& os, Matrix<long double> M)
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

    template<> const Matrix<long double> Matrix<long double>::to_triangle()
    {
        debug << "In to_triangle\n";
        for (size_t line = 0; line < sz_; ++line)
        {
            debug << *this;
            long double* non_nil_line = nullptr;
            for (size_t i = line; i < sz_; ++i)
                if (-Eps > data_[sz_ * i + line] || data_[sz_ * i + line] > Eps)
                {
                    non_nil_line = data_ + sz_ * i;
                    assert(reinterpret_cast<size_t>(non_nil_line + sz_ - 1) < reinterpret_cast<size_t>(data_ + sz_ * sz_));
                    break;
                }
            if (non_nil_line == nullptr) continue;
            debug << "non_nil_line = {";
            for (size_t i = 0; i < sz_; ++i)
                debug << data_[i] << ", ";
            debug << "\b\b}\n";

            if (non_nil_line != data_ + sz_ * line)
            {
                for (size_t i = line; i < sz_; ++i)
                {
                    data_[sz_ * line + i] += non_nil_line[i];
                    assert (sz_ * line + i < sz_ * sz_);
                }
                non_nil_line = data_ + sz_ * line;
            }
            double a_p = data_[(sz_ + 1) * line];
            assert ((sz_ + 1) * line < sz_ * sz_);
            debug << "a_p = " << a_p << '\n';
            for (size_t j = line + 1; j < sz_; ++j)
            {
                double b_p = data_[sz_ * j + line];
                assert (sz_ * j + line < sz_ * sz_);
                debug << "b_p = " << b_p << '\n';
                if (-Eps > b_p || b_p > Eps)
                for (size_t i = line; i < sz_; ++i)
                {
                    assert(sz_ * j + i < sz_ * sz_);
                    data_[sz_ * j + i] -= (non_nil_line[i] * b_p / a_p);
                }
            }
        }
        return *this;
    }

    template<> long double Matrix<long double>::det() const
    {
        double answer = 1;
        // std::cerr << "I go to to_triangle\n";
        Matrix<long double> M = *this;
        M.to_triangle();
        // std::cerr << "I have finished to_triangle\n";
        // std::cerr << "I have matrix\n";
        // std::cerr << M;
        debug << "\n\n\n";
        for (size_t i = 0; i < sz_; ++i)
        {
            debug << (M.data_)[(sz_ + 1) * i] << ' ';
            answer *= (M.data_)[(sz_ + 1) * i];
            assert ((sz_ + 1) * i < sz_ * sz_);
        }
        debug << '\n';
        return answer;

    }

} //namespace matrix

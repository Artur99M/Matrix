// Сорян, что на русском, но мой английский вери бэд.
// В данном случае выбран T*, потому что в отличие от массива он
// не требует определенного размера как матрица и не занимает
// стек. К тому же тут не возникнет путаницы с адресами, которая
// появляется в других реализациях. Выбран шаблон, чтобы сделать
// класс гибче. Реализацию можно подстроить под каждый тип по отдельности.

#pragma once
#include <iostream>
#include <vector>

namespace matrix
{
    template <class T>
    class Matrix
    {
        private:
        size_t sz_;
        T* data_ = nullptr;

        public: // Ctors
        explicit Matrix (size_t sz = 1);
        Matrix (size_t sz, T* data) : sz_(sz), data_(new T[sz_ * sz_])
        {
            if (data != nullptr)
                std::copy(data, data + sz_ * sz_, data_);
        }
        Matrix (size_t sz, T** data);
        Matrix (const Matrix& M);
        Matrix (Matrix&& M);
        Matrix (size_t sz, std::vector<T> data);

        //Dtor
        ~Matrix()
        { delete[] data_; }

        //operators
        Matrix& operator=(const Matrix& M);
        Matrix& operator=(Matrix&& M);

        //funcs
        T det() const;
        T& at(size_t x, size_t y)
        { return *(data_ + x * sz_ + y); }
        const T& at(size_t x, size_t y) const
        { return *(data_ + x * sz_ + y); }
        const Matrix<T> to_triangle();
        inline size_t size() const {return sz_;}

    };

} // namespace matrix

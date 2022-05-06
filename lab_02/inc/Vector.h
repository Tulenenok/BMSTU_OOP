/*
 * Примечания
 *
 * Какие операторы хочется перегрузить:
 *   [], -, +, =, -=, +=, ==, !=, *, *=, /, /=
 */

#ifndef MY_LAB_02_VECTOR_H
#define MY_LAB_02_VECTOR_H

#include <iostream>
#include <memory>

#include "../inc/BaseContainer.h"
#include "../inc/Iterator.h"

#define EPS 1e-6

template<typename T>
class Vector: public BaseContainter
{
    friend class Iterator<T>;

public:
    Vector();
    Vector(const size_t size);
    Vector(const size_t size, const T &filler);
    Vector(const size_t size, const T *arr);
    Vector(const std::initializer_list<T> list);

    Vector(const Vector<T> &vector);
    Vector(const Vector<T> &&vector) noexcept;

    ~Vector() override;

    T& operator[](const size_t ind) const;

    Vector<T> operator-() const;
    Vector<T> operator-(const Vector<T> &vector) const;
    Vector<T> operator-(const T &num) const;

    template<typename OtherT>
    decltype(auto) operator-(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) operator-(const OtherT &num) const;

    Vector<T> operator+() const;
    Vector<T> operator+(const Vector<T> &vector) const;
    Vector<T> operator+(const T &num) const;

    template<typename OtherT>
    decltype(auto) operator+(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) operator+(const OtherT &num) const;


    Vector<T> &operator=(const Vector<T> &vector);

    template<typename OtherT>
    bool operator==(const Vector<OtherT> &vector) const;

protected:
    void allocateMemory(const size_t size);

private:
    std::shared_ptr<T[]> data = nullptr;
};

#include "../imp/Vector.hpp"

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T> &vector)
{
    if (vector.isEmpty())
        return os << "()";

    os << "(" << vector[0];
    for(size_t i = 1; i < vector.getSize(); i++)
        os << ", " << vector[i];
    os << ")\n";
    return os;
}

#endif //MY_LAB_02_VECTOR_H

/*
 * Примечания
 *   todo: конкретные-операции с векторами, текстовые названия функций
 *   todo: разобраться с итератором
 *   todo: разобраться с функциями begin и end
 *   done: [], -, +, =, -=, +=, ==, !=, *, /, *=, /=, exceptions
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

    // []
    T& operator[](const size_t ind);
    const T& operator[](const size_t ind) const;
    //

    // -
    Vector<T> operator-() const;
    Vector<T> operator-(const Vector<T> &vector) const;
    Vector<T> operator-(const T &num) const;
    template<typename OtherT>
    decltype(auto) operator-(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) operator-(const OtherT &num) const;
    //

    // +
    Vector<T> operator+() const;
    Vector<T> operator+(const Vector<T> &vector) const;
    Vector<T> operator+(const T &num) const;
    template<typename OtherT>
    decltype(auto) operator+(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) operator+(const OtherT &num) const;
    //

    // *
    Vector<T> operator*(const T &num) const;
    template<typename OtherT>
    decltype(auto) operator*(const OtherT &num) const;
    //

    // /
    Vector<T> operator/(const T &num) const;
    template<typename OtherT>
    decltype(auto) operator/(const OtherT &num) const;
    //

    // =
    Vector<T> &operator=(const Vector<T> &vector);
    Vector<T> &operator=(std::initializer_list<T> list);
    Vector<T> &operator=(Vector<T> &&vector) noexcept;
    //

    // -=
    Vector<T> &operator-=(const Vector<T> &vector);
    Vector<T> &operator-=(const T &num);
    template<typename OtherT>
    Vector<T> &operator-=(const Vector<OtherT> &vector);
    template<typename OtherT>
    Vector<T> &operator-=(const OtherT &num);
    //

    // +=
    Vector<T> &operator+=(const Vector<T> &vector);
    Vector<T> &operator+=(const T &num);
    template<typename OtherT>
    Vector<T> &operator+=(const Vector<OtherT> &vector);
    template<typename OtherT>
    Vector<T> &operator+=(const OtherT &num);
    //

    // *=
    Vector<T> &operator*=(const T &num);
    template<typename OtherT>
    Vector<T> &operator*=(const OtherT &num);
    //

    // /=
    Vector<T> &operator/=(const T &num);
    template<typename OtherT>
    Vector<T> &operator/=(const OtherT &num);
    //

    // == !=
    template<typename OtherT>
    bool operator==(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    bool operator!=(const Vector<OtherT> &vector) const;
    //

    // Скалярное произведение
    T operator&(const Vector<T> &vector) const;
    template<typename OtherT>
    decltype(auto) operator&(const Vector<OtherT> &vector) const;
    //

    // Векторное произведение
    Vector<T> operator^(const Vector<T> &vector) const;
    Vector<T> &operator^=(const Vector<T> &vector);

    template<typename OtherT>
    decltype(auto) operator^(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    Vector<T> &operator^=(const Vector<OtherT> &vector);
    //

    // Длина вектора
    template<typename OtherT>
    OtherT len() const;
    //

    // Скалярное произведение
    T scalarProduct(const Vector<T> &vector) const;
    template<typename OtherT>
    decltype(auto) scalarProduct(const Vector<OtherT> &vector) const;
    //

    // Угол между векторами
    double angle(const Vector<T> &vector) const;

    template<typename OtherT>
    double angle(const Vector<OtherT> &vector) const;
    //

    // Коллинеарность
    bool isCollinear(const Vector<T> &vector) const;
    template<typename OtherT>
    bool isCollinear(const Vector<OtherT> &vector) const;
    //

    // Ортогональность
    bool isOrthogonal(const Vector<T> &vector) const;
    template<typename OtherT>
    bool isOrthogonal(const Vector<OtherT> &vector) const;
    //


    // Текстовые зеркала перегруженных операторов
        // -
    Vector<T> neg() const;
    Vector<T> diff(const Vector<T> &vector) const;
    Vector<T> diff(const T &num) const;
    template<typename OtherT>
    decltype(auto) diff(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) diff(const OtherT &num) const;
       //

       // +
    Vector<T> sum(const Vector<T> &vector) const;
    Vector<T> sum(const T &num) const;
    template<typename OtherT>
    decltype(auto) sum(const Vector<OtherT> &vector) const;
    template<typename OtherT>
    decltype(auto) sum(const OtherT &num) const;
       //

       // *
    Vector<T> mul(const T &num) const;
    template<typename OtherT>
    decltype(auto) mul(const OtherT &num) const;
       //

       // /
    Vector<T> div(const T &num) const;
    template<typename OtherT>
    decltype(auto) div(const OtherT &num) const;
       //

       // =
    Vector<T> &equal(const Vector<T> &vector);
    Vector<T> &equal(std::initializer_list<T> list);
    Vector<T> &equal(Vector<T> &&vector) noexcept;
       //




    //



protected:
    void allocateMemory(const size_t size);

    // check + exceptions
    template<typename OtherT>
    void checkSize(const Vector<OtherT> &vector, const size_t line) const;

    void checkIndex(const size_t index, const size_t line) const;
    void checkEmpty(const size_t line) const;

    template<typename OtherT>
    void checkDivisionByZero(const OtherT &num, const size_t line) const;
    //

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

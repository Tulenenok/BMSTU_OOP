#ifndef MY_LAB_02_VECTOR_HPP
#define MY_LAB_02_VECTOR_HPP

#include "../inc/Vector.h"

template<typename T>
Vector<T>::Vector(): BaseContainter(), data() {}

template<typename T>
Vector<T>::Vector(const size_t size): BaseContainter(size)
{
    allocateMemory(size);
}

template<typename T>
Vector<T>::Vector(const size_t size, const T &filler): BaseContainter(size)
{
    allocateMemory(size);

    for(size_t i = 0; i < size; i++)
        (*this)[i] = filler;
}

template<typename T>
Vector<T>::Vector(const size_t size, const T *arr): BaseContainter(size)
{
    allocateMemory(size);

    for(size_t i = 0; i < size; i++)
        (*this)[i] = arr[i];
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> list): BaseContainter(list.size())
{
    allocateMemory(this->size);

    size_t i = 0;
    for(auto elem : list)
        (*this)[i++] = elem;
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vector): BaseContainter(vector)
{
    allocateMemory(this->size);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] = vector[i];
}

template<typename T>
Vector<T>::Vector(const Vector<T> &&vector) noexcept: BaseContainter(vector.size)
{
    this->data = vector.data;
    // vector.data.reset();
}

template<typename T>
Vector<T>::~Vector() = default;

template<typename T>
T& Vector<T>::operator[](const size_t ind)
{
    // Нужна проверка на то, что индекс корректный
    return this->data[ind];
}

template<typename T>
const T& Vector<T>::operator[](const size_t ind) const
{
    // Нужна проверка на то, что индекс корректный
    return this->data[ind];
}

template<typename T>
Vector<T> Vector<T>::operator-() const
{
    Vector<T> tmp(*this);
    for(size_t i = 0; i < tmp.size; i++)
        tmp[i] = -tmp[i];
    return tmp;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &vector) const
{
    // Проверка на совпадение длины

    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] -= vector[i];

    return res;
}

template<typename T>
Vector<T> Vector<T>::operator-(const T &num) const
{
    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] -= num;

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator-(const Vector<OtherT> &vector) const
{
    // Нужна проверка длин векторов
    // И возможно проверка на то, что длина не 0 (отсебятина)

    Vector<decltype((*this)[0] - vector[0])> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] - vector[i];

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator-(const OtherT &num) const
{
    // Было бы неплохо проверить, что длина вектора хотя бы 1

    Vector<decltype((*this)[0] - num)> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] - num;

    return res;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector)
{
    this->size = vector.size;
    allocateMemory(this->size);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] = vector[i];
    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator=(std::initializer_list<T> list)
{
    this->size = list.size();
    allocateMemory(this->size);

    size_t i = 0;
    for(auto elem : list)
        (*this)[i++] = elem;
    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&vector) noexcept
{
    this->size = vector.getSize();
    this->data = vector.data;
    vector.data.reset();

    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator-=(const Vector<T> &vector)
{
    // Проверка на равенство длин векторов

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] -= vector[i];

    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator-=(const T &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] -= num;
    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator-=(const Vector<OtherT> &vector)
{
    // Нужна проверка на равенство длин векторов
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] -= vector[i];

    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator-=(const OtherT &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] -= num;
    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &vector)
{
    // Нужна проверка на равенcтво длин векторов

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] += vector[i];
    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator+=(const T &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] += num;
    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator+=(const Vector<OtherT> &vector)
{
    // Нужна проверка на равенство длин векторов

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] += vector[i];

    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator+=(const OtherT &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] += num;

    return (*this);
}

template<typename T>
template<typename OtherT>
bool Vector<T>::operator==(const Vector<OtherT> &vector) const
{
    if(this->size != vector.getSize())
        return false;

    for(size_t i = 0; i < this->size; i++)
        if(abs((*this)[i] - vector[i]) > EPS)
            return false;
    return true;
}

template<typename T>
template<typename OtherT>
bool Vector<T>::operator!=(const Vector<OtherT> &vector) const
{
    // Можно будет заменить потом на !Equal, после ввода текстовых функций

    if(this->size != vector.getSize())
        return true;

    for(size_t i = 0; i < this->size; i++)
        if(abs((*this)[i] - vector[i]) > EPS)
            return true;
    return false;
}

template<typename T>
Vector<T> Vector<T>::operator+() const
{
    Vector<T> res(*this);
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &vector) const
{
    // Нужна проверка на совпадение длинны векторов

    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] += vector[i];
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator+(const T &num) const
{
    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] += num;

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator+(const Vector<OtherT> &vector) const
{
    // Нужна проверка на длину

    Vector<decltype((*this)[0] + vector[0])> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] + vector[i];

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator+(const OtherT &num) const
{
    Vector<decltype((*this)[0] + num)> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] + num;

    return res;
}

template<typename T>
Vector<T> Vector<T>::operator*(const Vector<T> &vector) const
{
    // Нужна проверка на совпадение длинны векторов

    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] *= vector[i];
    return res;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T &num) const
{
    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] *= num;

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator*(const Vector<OtherT> &vector) const
{
    // Нужна проверка на длину

    Vector<decltype((*this)[0] * vector[0])> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] * vector[i];

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator*(const OtherT &num) const
{
    Vector<decltype((*this)[0] * num)> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] * num;

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator/(const Vector<OtherT> &vector) const
{
    // Нужна проверка на длину

    Vector<decltype((*this)[0] * vector[0])> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] / vector[i];

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator/(const OtherT &num) const
{
    Vector<decltype((*this)[0] / num)> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] / num;

    return res;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator*=(const Vector<OtherT> &vector)
{
    // Нужна проверка на равенство длин векторов

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] *= vector[i];

    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator*=(const OtherT &num)
{
    // Нужна проверка на равенство длин векторов

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] *= num;

    return (*this);
}


template<typename T>
void Vector<T>::allocateMemory(const size_t size)
{
    // Здесь нужна обработка ошибки выделения памяти
    this->data.reset(new T[size]);
}


#endif
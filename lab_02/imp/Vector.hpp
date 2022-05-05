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
Vector<T>::~Vector() = default;

template<typename T>
T& Vector<T>::operator[](const size_t ind) const
{
    // Нужна проверка на то, что индекс корректный
    return this->data[ind];
}

template<typename T>
void Vector<T>::allocateMemory(const size_t size)
{
    // Здесь нужна обработка ошибки выделения памяти
    this->data.reset(new T[size]);
}

#endif
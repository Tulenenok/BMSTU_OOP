#include "../inc/Iterator.h"

template<typename T>
Iterator<T>::Iterator(const Vector<T> &vector) noexcept: BaseIter()
{
    this->size = vector.size;
    this->ptr = vector.data;
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &iter) noexcept: BaseIter(iter)
{
    // Базовый конструктор копирования вызван, поэтому достаточно указатель перекинуть
    this->ptr = iter.ptr;
}

template<typename T>
Iterator<T>::~Iterator() = default;

template<typename T>
T* Iterator<T>::getPtr() const
{
    // Сделали сохраненный shared указатель и вернули его со смещением
    return this->ptr.lock().get() + this->cur_ind;
}
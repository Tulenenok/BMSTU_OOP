#ifndef MY_LAB_02_CONSTINTERATOR_HPP
#define MY_LAB_02_CONSTINTERATOR_HPP

#include "../inc/ConstIterator.h"
#include "../inc/Exceptions.h"
#include <time.h>

template<typename T>
ConstIterator<T>::ConstIterator(const Vector<T> &vector) noexcept: BaseIter()
{
    this->size = vector.size;
    this->ptr = vector.data;
}

template<typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iter) noexcept: BaseIter(iter)
{
    this->ptr = iter.ptr;
}

template<typename T>
ConstIterator<T>::~ConstIterator() = default;

template<typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &iter) noexcept
{
    this->size = iter.size;
    this->cur_ind = iter.cur_ind;
    this->ptr.reset(iter.ptr);

    return (*this);
}

template<typename T>
const T& ConstIterator<T>::operator*() const
{
    this->checkWildPointer(__LINE__);
    this->checkIndex(__LINE__);

    return *this->getPtr();
}

template<typename T>
const T* ConstIterator<T>::operator->() const
{
    this->checkWildPointer(__LINE__);
    this->checkIndex(__LINE__);

    return this->getPtr();
}

template<typename T>
const T& ConstIterator<T>::operator[](const size_t offset) const
{
    this->checkWildPointer(__LINE__);
    this->checkIndex(__LINE__);

    return *(this->getPtr() + offset);
}

template<typename T>
template<typename OtherT>
ConstIterator<T> ConstIterator<T>::operator+(const OtherT offset) const
{
    this->checkWildPointer(__LINE__);

    ConstIterator<T> res(*this);
    res.cur_ind += offset;
    return res;
}

template<typename T>
template<typename OtherT>
ConstIterator<T> &ConstIterator<T>::operator+=(const OtherT offset)
{
    this->checkWildPointer(__LINE__);

    this->cur_ind += offset;
    return (*this);
}

template<typename T>
ConstIterator<T> &ConstIterator<T>::operator++()
{
    this->checkWildPointer(__LINE__);

    (this->cur_ind)++;
    return (*this);
}

template<typename T>
template<typename OtherT>
ConstIterator<T> ConstIterator<T>::operator-(const OtherT offset) const
{
    this->checkWildPointer(__LINE__);

    ConstIterator<T> res(*this);
    res.cur_ind -= offset;
    return res;
}

template<typename T>
template<typename OtherT>
ConstIterator<T> &ConstIterator<T>::operator-=(const OtherT offset)
{
    this->checkWildPointer(__LINE__);

    this->cur_ind -= offset;
    return (*this);
}

template<typename T>
ConstIterator<T> &ConstIterator<T>::operator--()
{
    this->checkWildPointer(__LINE__);

    (this->cur_ind)--;
    return (*this);
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() == iter.getPtr();
}

template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() != iter.getPtr();
}

template<typename T>
bool ConstIterator<T>::operator<(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() < iter.getPtr();
}

template<typename T>
bool ConstIterator<T>::operator>(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() > iter.getPtr();
}

template<typename T>
bool ConstIterator<T>::operator<=(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() <= iter.getPtr();
}

template<typename T>
bool ConstIterator<T>::operator>=(const ConstIterator<T> &iter) const
{
    this->checkWildPointer(__LINE__);
    iter.checkWildPointer(__LINE__);

    return this->getPtr() >= iter.getPtr();
}

template<typename T>
ConstIterator<T>::operator bool() const
{
    this->checkWildPointer(__LINE__);
    return this->size and this->cur_ind < this->size;
}






template<typename T>
T* ConstIterator<T>::getPtr() const
{
    // Сделали сохраненный shared указатель и вернули его со смещением
    return this->ptr.lock().get() + this->cur_ind;
}

template<typename T>
void ConstIterator<T>::checkIndex(const size_t line, const size_t offset) const
{
    if(this->cur_ind + offset >= this->size)
    {
        time_t curTime = time(NULL);
        throw IndexOutOfRangeException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template<typename T>
void ConstIterator<T>::checkWildPointer(const size_t line) const
{
    if(this->ptr.expired())
    {
        time_t curTime = time(NULL);
        throw WildPointerException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

#endif //MY_LAB_02_CONSTINTERATOR_HPP
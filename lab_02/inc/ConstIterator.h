#ifndef MY_LAB_02_CONSTITERATOR_H
#define MY_LAB_02_CONSTITERATOR_H

#include <memory>
#include "../inc/BaseIter.h"

template<typename T>
class Vector;

template<typename T>
class ConstIterator: public BaseIter
{
    friend class Vector<T>;

public:
    ConstIterator(const Vector<T> &vector) noexcept;
    ConstIterator(const ConstIterator<T> &iter) noexcept;
    ~ConstIterator() override;

    ConstIterator<T> &operator=(const ConstIterator<T> &iter) noexcept;

    const T &operator*() const;
    const T *operator->() const;

    const T &operator[](const size_t offset) const;

    template <typename OtherT>
    ConstIterator<T> operator+(const OtherT offset) const;

    template<typename OtherT>
    ConstIterator<T> &operator+=(const OtherT offset);

    ConstIterator<T> &operator++();


    template <typename OtherT>
    ConstIterator<T> operator-(const OtherT offset) const;

    template<typename OtherT>
    ConstIterator<T> &operator-=(const OtherT offset);

    ConstIterator<T> &operator--();

    bool operator==(const ConstIterator<T> &iter) const;
    bool operator!=(const ConstIterator<T> &iter) const;

    bool operator>(const ConstIterator<T> &iter) const;
    bool operator<(const ConstIterator<T> &iter) const;

    bool operator>=(const ConstIterator<T> &iter) const;
    bool operator<=(const ConstIterator<T> &iter) const;

protected:
    T* getPtr() const;

    void checkIndex(const size_t line, const size_t offset = 0) const;
    void checkWildPointer(const size_t line) const;

private:
    std::weak_ptr<T[]> ptr = nullptr;         // не владеем данными
};

#include "../imp/ConstIterator.hpp"

#endif //MY_LAB_02_CONSTITERATOR_H

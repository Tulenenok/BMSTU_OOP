/*
 * Примечания
 *
 * forward объявление вектора сначала вместо подключения заголовочника для того, чтобы ослабить зависимости
 * между файлами
 * noexcept -- указание компилятору, что функция не будет выбрасывать исключения (=> ускоряем работу программы
 * и уменьшаем размер итогового файла)
 *
 * todo:
 * done: =, *, ->, [], +, -, +=, -=, ++, --, ==, !=, >, >=, <, <=
 */

#ifndef MY_LAB_02_ITERATOR_H
#define MY_LAB_02_ITERATOR_H

#include <memory>
#include "../inc/BaseIter.h"

template<typename T>
class Vector;

template<typename T>
class Iterator: public BaseIter
{
    friend class Vector<T>;

public:
    Iterator(const Vector<T> &vector) noexcept;
    Iterator(const Iterator<T> &iter) noexcept;
    ~Iterator() override;

    Iterator<T> &operator=(const Iterator<T> &iter) noexcept;

    T& operator*();
    const T& operator*() const;

    T* operator->();
    const T* operator->() const;

    T& operator[](const size_t offset);
    const T& operator[](const size_t offset) const;

    // +
    template<typename OtherT>
    Iterator<T> operator+(const OtherT offset) const;

    template<typename OtherT>
    Iterator<T> &operator+=(const OtherT offset);

    Iterator<T> &operator++();
    //

    // -
    template<typename OtherT>
    Iterator<T> operator-(const OtherT offset) const;

    template<typename OtherT>
    Iterator<T> &operator-=(const OtherT offset);

    Iterator<T> &operator--();
    //

    bool operator==(const Iterator<T> &iter) const;
    bool operator!=(const Iterator<T> &iter) const;

    bool operator>(const Iterator<T> &iter) const;
    bool operator<(const Iterator<T> &iter) const;

    bool operator>=(const Iterator<T> &iter) const;
    bool operator<=(const Iterator<T> &iter) const;

    operator bool() const;

protected:
    T* getPtr() const;

    void checkIndex(const size_t line, const size_t offset = 0) const;
    void checkWildPointer(const size_t line) const;

private:
    std::weak_ptr<T[]> ptr = nullptr;         // не владеем данными
};

#include "../imp/Iterator.hpp"

#endif //MY_LAB_02_ITERATOR_H

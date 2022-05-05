/*
 * Примечания
 *
 * forward объявление вектора сначала вместо подключения заголовочника для того, чтобы ослабить зависимости
 * между файлами
 * noexcept -- указание компилятору, что функция не будет выбрасывать исключения (=> ускоряем работу программы
 * и уменьшаем размер итогового файла)
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
    Iterator(const Vector<T> &vector) noexcept;          // Конструктор инициализации
    Iterator(const Iterator<T> &iter) noexcept;          // Конструктор копирования
    ~Iterator() override;                                         // Деструктор

protected:
    T* getPtr() const;

private:
    std::weak_ptr<T[]> ptr = nullptr;         // не владеем данными
};
#endif //MY_LAB_02_ITERATOR_H

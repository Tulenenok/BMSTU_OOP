/*
 *  Примечания
 *
 *  Идея: создаем базовый итератор (абстрактный класс, т.к. есть virtual),
 *  который потом будем использовать для четырех итераторов, бегающих по вектору
 *
 *  В производных классах мы должны будем определить деструкторы, потому что иначе они будут
 *  тоже абстрактными и мы не сможем создавать объекты таких классов.
 *
 */

#ifndef MY_LAB_02_BASEITER_H
#define MY_LAB_02_BASEITER_H

#include <cstdlib>

class BaseIter
{
public:
    BaseIter();                         // Конструктор инициализации
    BaseIter(const BaseIter &iter);     // Конструктор копирования
    virtual ~BaseIter() = 0;            // Деструктор

protected:
    size_t size = 0;
    size_t cur_ind = 0;
};

#endif //MY_LAB_02_BASEITER_H

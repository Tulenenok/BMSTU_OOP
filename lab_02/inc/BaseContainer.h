/*
 * Примечания
 *
 * Идея: создать абстрактный класс, который будет базой для нашего класса Vector
 * const в конце означает, что метод константный, то есть он не изменяет какие-либо данные экземпляра
 *
 */

#ifndef MY_LAB_02_BASECONTAINER_H
#define MY_LAB_02_BASECONTAINER_H

#include <cstdlib>

class BaseContainter
{
public:
    BaseContainter();                                  // Конструктор
    BaseContainter(const size_t size);                 // Конструктор
    BaseContainter(const BaseContainter &baseCont);    // Конструктор копирования
    virtual ~BaseContainter() = 0;                     // Деструктор

    bool isEmpty() const;
    size_t getSize() const;

protected:
    size_t size = 0;
};

#endif //MY_LAB_02_BASECONTAINER_H

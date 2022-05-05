#ifndef MY_LAB_02_VECTOR_H
#define MY_LAB_02_VECTOR_H

#include <memory>

#include "../inc/BaseContainer.h"
#include "../inc/Iterator.h"

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

    T& operator[](const size_t ind) const;

    ~Vector() override;
protected:
    void allocateMemory(const size_t size);

private:
    std::shared_ptr<T[]> data = nullptr;
};

#include "../imp/Vector.hpp"

#endif //MY_LAB_02_VECTOR_H

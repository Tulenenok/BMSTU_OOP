#ifndef MY_LAB_02_VECTOR_HPP
#define MY_LAB_02_VECTOR_HPP

#include <ctime>
#include <cmath>
//#include <math.h>
#include "../inc/Vector.h"
#include "../inc/Exceptions.h"

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
    this->checkIndex(ind, __LINE__);

    return this->data[ind];
}

template<typename T>
const T& Vector<T>::operator[](const size_t ind) const
{
    this->checkIndex(ind, __LINE__);

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
    this->checkSize(vector, __LINE__);

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
    this->checkSize(vector, __LINE__);

    Vector<decltype((*this)[0] - vector[0])> res(this->size);

    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] - vector[i];

    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator-(const OtherT &num) const
{
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
    this->checkSize(vector, __LINE__);

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
    this->checkSize(vector, __LINE__);

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
    this->checkSize(vector, __LINE__);

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
    this->checkSize(vector, __LINE__);

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
    this->checkSize(vector, __LINE__);

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
Vector<T> Vector<T>::operator*(const T &num) const
{
    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] *= num;

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
Vector<T> Vector<T>::operator/(const T &num) const
{
    Vector<T> res(*this);

    for(size_t i = 0; i < this->size; i++)
        res[i] /= num;

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
Vector<T> &Vector<T>::operator*=(const T &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] *= num;

    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator*=(const OtherT &num)
{
    for(size_t i = 0; i < this->size; i++)
        (*this)[i] *= num;

    return (*this);
}

template<typename T>
Vector<T> &Vector<T>::operator/=(const T &num)
{
    checkDivisionByZero(num, __LINE__);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] /= num;

    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator/=(const OtherT &num)
{
    checkDivisionByZero(num, __LINE__);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] /= num;

    return (*this);
}

template<typename T>
T Vector<T>::operator&(const Vector<T> &vector) const
{
    return this->scalarProduct(vector);
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator&(const Vector<OtherT> &vector) const
{
    return this->scalarProduct(vector);
}

template<typename T>
Vector<T> Vector<T>::operator^(const Vector<T> &vector) const
{
    this->checkSize(vector, __LINE__);

    Vector<T> res(this->size);
    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[(i + 1) % this->size] * vector[(i + 2) % this->size] -
                 (*this)[(i + 2) % this->size] * vector[(i + 1) % this->size];
    return res;
}

template<typename T>
Vector<T> &Vector<T>::operator^=(const Vector<T> &vector)
{
    this->checkSize(vector, __LINE__);
    Vector<T> thisCopy(*this);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] = thisCopy[(i + 1) % this->size] * vector[(i + 2) % this->size] -
                     thisCopy[(i + 2) % this->size] * vector[(i + 1) % this->size];
    return (*this);
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::operator^=(const Vector<OtherT> &vector)
{
    this->checkSize(vector, __LINE__);
    Vector<T> thisCopy(*this);

    for(size_t i = 0; i < this->size; i++)
        (*this)[i] = thisCopy[(i + 1) % this->size] * vector[(i + 2) % this->size] -
                     thisCopy[(i + 2) % this->size] * vector[(i + 1) % this->size];
    return (*this);
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::operator^(const Vector<OtherT> &vector) const
{
    this->checkSize(vector, __LINE__);

    Vector<decltype((*this)[0] + vector[0])> res(this->size);
    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[(i + 1) % this->size] * vector[(i + 2) % this->size] -
                (*this)[(i + 2) % this->size] * vector[(i + 1) % this->size];
    return res;
}

template<typename T>
template<typename OtherT>
OtherT Vector<T>::len() const
{
    checkEmpty(__LINE__);

    OtherT sum = 0;
    for(size_t i = 0; i < this->size; i++)
        sum += (*this)[i] * (*this)[i];
    return sqrt(sum);
}

template<typename T>
bool Vector<T>::isUnit() const
{
    return abs(this->len<T>() - 1) < EPS;
}

template<typename T>
template<typename OtherT>
Vector<OtherT> Vector<T>::getUnit()
{
    this->checkEmpty(__LINE__);

    OtherT thisLen = this->len<OtherT>();
    this->template checkDivisionByZero(thisLen, __LINE__);

    Vector<OtherT> res(this->size);
    for(size_t i = 0; i < this->size; i++)
        res[i] = (*this)[i] / thisLen;

    return res;
}

template<typename T>
bool Vector<T>::isZero() const
{
    return abs(this->len<T>()) < EPS;
}

template<typename T>
T Vector<T>::scalarProduct(const Vector<T> &vector) const
{
    this->checkSize(vector, __LINE__);

    T res = 0;
    for(size_t i = 0; i < this->size; i++)
        res += (*this)[i] * vector[i];
    return res;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::scalarProduct(const Vector<OtherT> &vector) const\
{
    this->checkSize(vector, __LINE__);

    decltype((*this)[0] * vector[0]) res = 0;
    for(size_t i = 0; i < this->size; i++)
        res += (*this)[i] * vector[i];
    return res;
}

template<typename T>
Vector<T> Vector<T>::vectorProduct(const Vector<T> &vector) const
{
    return (*this) ^ vector;
}

template<typename T>
Vector<T> &Vector<T>::vectorEqualProduct(const Vector<T> &vector)
{
    return (*this) ^= vector;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::vectorEqualProduct(const Vector<OtherT> &vector)
{
    return (*this) ^= vector;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::vectorProduct(const Vector<OtherT> &vector) const
{
    return (*this) ^ vector;
}

template<typename T>
double Vector<T>::angle(const Vector<T> &vector) const
{
    double thisLen = this->len<double>();
    double vecLen = this->len<double>();

    if (fabs(thisLen) > EPS and fabs(vecLen) > EPS)
        return acos(this->scalarProduct(vector) / (thisLen * vecLen));

    return 0;
}

template<typename T>
template<typename OtherT>
double Vector<T>::angle(const Vector<OtherT> &vector) const
{
    double thisLen = this->len<double>();
    double vecLen = this->len<double>();

    if (fabs(thisLen) > EPS and fabs(vecLen) > EPS)
        return acos(this->scalarProduct(vector) / (thisLen * vecLen));

    return 0;
}

template<typename T>
bool Vector<T>::isCollinear(const Vector<T> &vector) const
{
    this->checkSize(vector, __LINE__);
    return this->vectorProduct(vector).isZero();
}

template<typename T>
template<typename OtherT>
bool Vector<T>::isCollinear(const Vector<OtherT> &vector) const
{
    this->checkSize(vector, __LINE__);
    return this->vectorProduct(vector).isZero();
}

template<typename T>
bool Vector<T>::isOrthogonal(const Vector<T> &vector) const
{
    this->checkSize(vector, __LINE__);
    return abs(this->scalarProduct(vector)) < EPS;
}

template<typename T>
template<typename OtherT>
bool Vector<T>::isOrthogonal(const Vector<OtherT> &vector) const
{
    this->checkSize(vector, __LINE__);
    return abs(this->scalarProduct(vector)) < EPS;
}

template<typename T>
Vector<T> Vector<T>::neg() const
{
    return -(*this);
}

template<typename T>
Vector<T> Vector<T>::diff(const Vector<T> &vector) const
{
    return (*this) - vector;
}

template<typename T>
Vector<T> Vector<T>::diff(const T &num) const
{
    return (*this) - num;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::diff(const Vector<OtherT> &vector) const
{
    return (*this) - vector;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::diff(const OtherT &num) const
{
   return (*this) + num;
}

template<typename T>
Vector<T> Vector<T>::sum(const Vector<T> &vector) const
{
    return (*this) + vector;
}

template<typename T>
Vector<T> Vector<T>::sum(const T &num) const
{
    return (*this) - num;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::sum(const Vector<OtherT> &vector) const
{
    return (*this) + vector;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::sum(const OtherT &num) const
{
    return (*this) + num;
}

template<typename T>
Vector<T> Vector<T>::mul(const T &num) const
{
    return (*this) * num;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::mul(const OtherT &num) const
{
    return (*this) * num;
}

template<typename T>
Vector<T> Vector<T>::div(const T &num) const
{
    return (*this) / num;
}

template<typename T>
template<typename OtherT>
decltype(auto) Vector<T>::div(const OtherT &num) const
{
    return (*this) / num;
}

template<typename T>
Vector<T> &Vector<T>::equal(const Vector<T> &vector)
{
    return (*this) = vector;
}

template<typename T>
Vector<T> &Vector<T>::equal(Vector<T> &&vector) noexcept
{
    return (*this) = vector;
}

template<typename T>
Vector<T> &Vector<T>::equal(std::initializer_list<T> list)
{
    return (*this) = list;
}

template<typename T>
Vector<T> &Vector<T>::diffEqual(const Vector<T> &vector)
{
    return (*this) -= vector;
}

template<typename T>
Vector<T> &Vector<T>::diffEqual(const T &num)
{
    return (*this) -= num;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::diffEqual(const Vector<OtherT> &vector)
{
    return (*this) -= vector;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::diffEqual(const OtherT &num)
{
    return (*this) -= num;
}

template<typename T>
Vector<T> &Vector<T>::sumEqual(const Vector<T> &vector)
{
    return (*this) += vector;
}

template<typename T>
Vector<T> &Vector<T>::sumEqual(const T &num)
{
    return (*this) += num;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::sumEqual(const Vector<OtherT> &vector)
{
    return (*this) += vector;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::sumEqual(const OtherT &num)
{
    return (*this) += num;
}

template<typename T>
Vector<T> &Vector<T>::mulEqual(const T &num)
{
    return (*this) *= num;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::mulEqual(const OtherT &num)
{
    return (*this) *= num;
}

template<typename T>
Vector<T> &Vector<T>::divEqual(const T &num)
{
    return (*this) /= num;
}

template<typename T>
template<typename OtherT>
Vector<T> &Vector<T>::divEqual(const OtherT &num)
{
    return (*this) /= num;
}

template<typename T>
template<typename OtherT>
bool Vector<T>::isEqual(const Vector<OtherT> &vector) const
{
    return (*this) == vector;
}

template<typename T>
template<typename OtherT>
bool Vector<T>::isNotEqual(const Vector<OtherT> &vector) const
{
    return (*this) != vector;
}











template<typename T>
void Vector<T>::allocateMemory(const size_t size)
{
    try
    {
        this->data.reset(new T[size]);
    }
    catch (std::bad_alloc &err)
    {
        time_t curTime = time(NULL);
        throw AllocateMemoryException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);
    }
}

template<typename T>
template<typename OtherT>
void Vector<T>::checkSize(const Vector<OtherT> &vector, const size_t line) const
{
    if(this->size != vector.getSize())
    {
        time_t curTime = time(NULL);
        throw DifferentSizesException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template<typename T>
template<typename OtherT>
void Vector<T>::checkDivisionByZero(const OtherT &num, const size_t line) const
{
    if(abs(num) < EPS)
    {
        time_t curTime = time(NULL);
        throw DivisionByZeroException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template<typename T>
void Vector<T>::checkEmpty(const size_t line) const
{
    if(isEmpty())
    {
        time_t curTime = time(NULL);
        throw EmptyVectorException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template<typename T>
void Vector<T>::checkIndex(const size_t index, const size_t line) const
{
    if(index >= this->getSize())
    {
        time_t curTime = time(NULL);
        throw IndexOutOfRangeException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}


#endif
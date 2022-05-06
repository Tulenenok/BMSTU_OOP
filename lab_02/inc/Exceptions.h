#ifndef MY_LAB_02_EXCEPTIONS_H
#define MY_LAB_02_EXCEPTIONS_H

#include "BaseException.h"

class DifferentSizesException: public BaseException
{
public:
    DifferentSizesException(const std::string &time, const std::string &filename,
                            const size_t &line, const std::string &className,
                            const std::string &methodName, const std::string &info="The vectors don't have the same sizes")
                   : BaseException(time, filename, line, className, methodName, info){};
};

class IndexOutOfRangeException: public BaseException
{
public:
    IndexOutOfRangeException(const std::string &time, const std::string &filename,
                             const size_t &line, const std::string &className,
                             const std::string &methodName, const std::string &info="Index is out of range")
            : BaseException(time, filename, line, className, methodName, info){};
};

class EmptyVectorException: public BaseException
{
public:
    EmptyVectorException(const std::string &time, const std::string &filename,
                         const size_t &line, const std::string &className,
                         const std::string &methodName, const std::string &info="Empty vector")
            : BaseException(time, filename, line, className, methodName, info){};
};

class DivisionByZeroException: public BaseException
{
public:
    DivisionByZeroException(const std::string &time, const std::string &filename,
                         const size_t &line, const std::string &className,
                         const std::string &methodName, const std::string &info="Division by zero")
            : BaseException(time, filename, line, className, methodName, info){};
};

class AllocateMemoryException: public BaseException
{
public:
    AllocateMemoryException(const std::string &time, const std::string &filename,
                            const size_t &line, const std::string &className,
                            const std::string &methodName, const std::string &info="Allocate memory error")
            : BaseException(time, filename, line, className, methodName, info){};
};
#endif //MY_LAB_02_EXCEPTIONS_H

#ifndef MY_LAB_02_BASEEXCEPTION_H
#define MY_LAB_02_BASEEXCEPTION_H

#include <exception>
#include <string>

class BaseException: public std::exception
{
public:
    BaseException(const std::string &time, const std::string &filename,
                  const size_t &line, const std::string &className,
                  const std::string &methodName, const std::string &info);

    virtual const char *what() const noexcept override;

protected:
    std::string outputMessage;
};

#endif //MY_LAB_02_BASEEXCEPTION_H

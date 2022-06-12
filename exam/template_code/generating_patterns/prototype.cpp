#include <iostream>
#include <memory>

// Prototype
class BaseObject
{
public:
    virtual ~BaseObject() = default;

    virtual std::unique_ptr<BaseObject> clone() = 0;
};

// ConPrototype
class Object1: public BaseObject
{
public:
    Object1() {std::cout << "Default constructor\n";}
    Object1(const Object1 &obj) {std::cout << "Copy constructor\n";}
    ~Object1() {std::cout << "Destrcutor\n";}

    virtual std::unique_ptr<BaseObject> clone() override
    {
        return std::unique_ptr<BaseObject>(new Object1(*this));
    }
};


int main()
{
    std::unique_ptr<BaseObject> ptr1(new Object1());

    auto ptr2 = ptr1->clone();
}
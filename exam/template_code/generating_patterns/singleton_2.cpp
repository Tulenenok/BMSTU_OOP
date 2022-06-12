/*
 * Проблема: не накладываем ограничения на объект (может иметь конструкторы),
 * но если мы работаем через эту оболочку, это гарантирует то, что этот объект только 1.
 */

#include <iostream>
#include <memory>

template<typename Type>
class Singleton
{
public:
    static Type& instance()
    {
        static std::unique_ptr<Type> myInstance(new Type());
        return *myInstance;
    }

    Singleton() = delete;
    Singleton(const Singleton<Type>&) = delete;
    Singleton<Type>& operator=(const Singleton<Type>&) = delete;
};


class Product
{
public:
    Product() {std::cout << "Default const\n";}
    ~Product() {std::cout << "Destructor\n";}

    void f() {std::cout << "Method\n";}
};


int main()
{
    Product &d = Singleton<Product>::instance();
    d.f();
}
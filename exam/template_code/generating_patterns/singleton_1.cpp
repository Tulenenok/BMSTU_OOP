#include <iostream>
#include <memory>

class Singleton
{
private:
    Singleton() {std::cout << "Default constructor\n";}

public:
    static std::shared_ptr<Singleton>& instance()
    {
        static std::shared_ptr<Singleton> myInstance(new Singleton());
        return myInstance;
    }

    ~Singleton() {std::cout << "Destructor\n";}

    // Запрещаем конструктор копирования и оператор присваивания
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;


    void f() {std::cout << "Method\n";}
};


int main()
{
    std::shared_ptr<Singleton> p(Singleton::instance());
    p->f();
}

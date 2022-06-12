/*
 * Фабричный метод. Новый объект.
 */

#include <iostream>
#include <memory>

class Product;

class Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
};

template<typename TypeProd>
class ConCreator: public Creator
{
public:
    virtual std::unique_ptr<Product> createProduct() override
    {
        return std::unique_ptr<Product>(new TypeProd());
    }
};


class Product
{
public:
    virtual ~Product() = 0;
    virtual void run() = 0;
};
Product::~Product() = default;


class ConProd: public Product
{
public:
    virtual ~ConProd() override {std::cout << "Destructor\n";}
    virtual void run() override {std::cout << "Method run\n";}
};

int main()
{
    std::shared_ptr<Creator> c = std::make_shared<ConCreator<ConProd>>();
    std::shared_ptr<Product> p = c->createProduct();

    p->run();
}

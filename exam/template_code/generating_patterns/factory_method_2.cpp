/*
 * Фабричный метод. Без повторного создания.
 * (один раз создав продукт, в дальнейшем мы можем его только возвращать)
 */

#include <iostream>
#include <memory>

class Product;

class Creator
{
public:
    std::shared_ptr<Product> getProduct();

protected:
    virtual std::shared_ptr<Product> createProduct() = 0;

private:
    std::shared_ptr<Product> product;
};

template<typename TypeProd>
class ConCreator: public Creator
{
protected:
    virtual std::shared_ptr<Product> createProduct() override
    {
        return std::shared_ptr<Product>(new TypeProd());
    }
};

std::shared_ptr<Product> Creator::getProduct()
{
    if (!product)
        product = createProduct();
    return product;
}


class Product
{
public:
    virtual ~Product() = 0;
    virtual void run() = 0;
};

Product::~Product() = default;

class ConProduct: public Product
{
public:
    virtual ~ConProduct() override {std::cout << "Destructor\n";}
    virtual void run() override {std::cout << "Run\n";}
};

int main()
{
    std::shared_ptr<Creator> c = std::make_shared<ConCreator<ConProduct>>();
    std::shared_ptr<Product> p1 = c->getProduct();
    std::shared_ptr<Product> p2 = c->getProduct();

    // use_count возвращает количество различных shared_ptr, управляющих объектов
    std::cout<< p1.use_count() << std::endl;   // 3
    p1->run();
}

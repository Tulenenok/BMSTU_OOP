/*
 * Это чистый код Тассова
 * Значит типа по определению правильный
 * /поэтому оставлю без комментариев/
 */

#include <iostream>
#include <memory>

// Продукт, который мы хотим построить
class Product
{
public:
    Product() {std::cout << "Default constructor\n";}
    ~Product() {std::cout << "Destructot\n";}

    void run() {std::cout << "Run\n";}
};

// Строитель, который будет заниматься стройкой
class Builder
{
protected:
    // Судя по всему это метод из серии "Мы создали продукт, нужно начать создавать новый?"
    virtual std::shared_ptr<Product> createProduct() = 0;

    std::shared_ptr<Product> product;

public:
    // Почему build-ы открыты, а createProduct в protected??
    virtual bool buildPart1() = 0;
    virtual bool buildPart2() = 0;

    std::shared_ptr<Product> getProduct();
};

std::shared_ptr<Product> Builder::getProduct()
{
    if(!product)
        product = createProduct();
    return product;
}


class ConBuilder: public Builder
{
private:
    size_t part{0};

protected:
    virtual std::shared_ptr<Product> createProduct() override;

public:
    virtual bool buildPart1() override { std::cout << "Completed part: " << ++part << "\n"; return true; }
    virtual bool buildPart2() override { std::cout << "Completed part: " << ++part << "\n"; return true; }
};

std::shared_ptr<Product> ConBuilder::createProduct()
{
    if(part == 2)
    {
        part = 0;  // Мое дополнение, возможно неправильное, но, по-моему, так логичнее

        product = std::shared_ptr<Product>(new Product());
    }

    return product;
}


class Director
{
public:
    std::shared_ptr<Product> create(std::shared_ptr<Builder> builder);
};


std::shared_ptr<Product> Director::create(std::shared_ptr<Builder> builder)
{
    if(builder->buildPart1() && builder->buildPart2())
        return builder->getProduct();

    return std::shared_ptr<Product>();
}


int main()
{
    std::shared_ptr<Builder> builder(new ConBuilder());
    std::shared_ptr<Director> director(new Director());

    std::shared_ptr<Product> prod = director->create(builder);
    std::shared_ptr<Product> prod2 = director->create(builder);  // Лучше не писать

    if(prod)
        prod->run();

    // Интересный факт, что деструктор срабатывает только для одного продукта
}
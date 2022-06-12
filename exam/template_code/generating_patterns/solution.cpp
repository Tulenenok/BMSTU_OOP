/*
 * Фабричный метод. Новый объект.
 */

#include <iostream>
#include <memory>
#include <map>

// Все про продукты и креаторы копипастится
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
// Конец копипаста

// Solution наше все
class Solution
{
    // Объявили указатель на функцию
    typedef std::unique_ptr<Creator> (*CreateCreator)();

private:
    std::map<size_t, CreateCreator> callbackMap;

public:

    bool registration(size_t id, CreateCreator cr)
    {
        return callbackMap.insert(std::map<size_t, CreateCreator>::value_type(id, cr)).second;
    }

    // Абсолютно не понимаю, зачем мы его здесь удаляем из карты
    // Почему не
    // bool check(size_t id) {return  callbackMap.find(id) == callbackMap.end();}
    bool check(size_t id) {return callbackMap.erase(id) == 1;}

    std::unique_ptr<Creator> create(size_t id)
    {
        std::map<size_t, CreateCreator>::const_iterator it = callbackMap.find(id);
        if(it == callbackMap.end()) {
            std::cout << "Error";
            return nullptr;
        }
        // throw IdError();

        return std::unique_ptr<Creator>((it->second)());
    }
};
//

// Функция просто так (для регистрации в карте)
std::unique_ptr<Creator> createConCreator()
{
    return std::unique_ptr<Creator>(new ConCreator<ConProd>());
}

int main()
{
    Solution solution;
    solution.registration(1, createConCreator);

    std::shared_ptr<Creator> c(solution.create(1));
    std::shared_ptr<Product> p = c->createProduct();

    p->run();
}

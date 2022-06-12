#include <iostream>
#include <memory>
#include <iterator>
#include <vector>

using namespace std;

class Product
{
private:
    static size_t count;

public:
    Product() {std::cout << "Constructor(" << ++count << ")\n";}
    ~Product() {std::cout << "Destructor(" << count-- << ")\n";}

    void clear() {std::cout << "Method clear: 0x" << this << "\n";}
};

size_t Product::count = 0;


template<typename Type>
class ObjectPool
{
private:
    std::vector<std::pair<bool, std::shared_ptr<Type>>> pool;

    ObjectPool() {}

    // Необходимо знать, занят объект или нет, используем пару: ключ (bool) и объект.
    std::pair<bool, std::shared_ptr<Type>> create();

    template <typename NType>
    friend std::ostream& operator << (std::ostream& os, const ObjectPool<NType>& pl);

public:
    static std::shared_ptr<ObjectPool<Type>> instance();

    std::shared_ptr<Type> getObject();
    bool releaseObject(std::shared_ptr<Type>& obj);
    size_t count() const { return pool.size(); }

    // Пулл объектов - контейнерный класс, удобно использовать итераторы!
    std::iterator<std::output_iterator_tag, const std::pair<bool, std::shared_ptr<Type>>> begin() const;
    std::iterator<std::output_iterator_tag, const std::pair<bool, std::shared_ptr<Type>>> end() const;

    ObjectPool(const ObjectPool<Type>&) = delete;
    ObjectPool<Type>& operator=(const ObjectPool<Type>&) = delete;
};



template <typename Type>
shared_ptr<ObjectPool<Type>> ObjectPool<Type>::instance()
{
    static shared_ptr<ObjectPool<Type>> myInstance(new ObjectPool<Type>());

    return myInstance;
}

template <typename Type>
shared_ptr<Type> ObjectPool<Type>::getObject()
{
    size_t i;
    for (i = 0; i < pool.size() && pool[i].first; ++i);

    if (i < pool.size())
        pool[i].first = true;
    else
        pool.push_back(create());

    return pool[i].second;
}

template <typename Type>
bool ObjectPool<Type>::releaseObject(shared_ptr<Type>& obj)
{
    size_t i;
    for (i = 0; i < pool.size() && pool[i].second != obj; ++i);

    if (i == pool.size()) return false;

    obj.reset();
    pool[i].first = false;
    pool[i].second->clear();

    return true;
}

template <typename Type>
pair<bool, shared_ptr<Type>> ObjectPool<Type>::create()
{
    return pair<bool, shared_ptr<Type>>(true, shared_ptr<Type>(new Type()));
}

#pragma endregion

template <typename Type>
ostream& operator << (ostream& os, const ObjectPool<Type>& pl)
{
    for (auto elem : pl.pool)
        os << "{" << elem.first << ", 0x" << elem.second << "} ";

    return os;
}

int main()
{
    shared_ptr<ObjectPool<Product>> pool = ObjectPool<Product>::instance();

    vector<shared_ptr<Product>> vec(4);

    for (auto& elem : vec)
        elem = pool->getObject();

    pool->releaseObject(vec[1]);

    cout << *pool << endl;

    shared_ptr<Product> ptr = pool->getObject();
    vec[1] = pool->getObject();

    cout << *pool << endl;
}





#include <iostream>
#include <memory>

// Базовый класс, интерфейс которого мы хотим подменить
class BaseAdaptee
{
public:
    virtual ~BaseAdaptee() = 0;
    virtual void specRequest() = 0;
};

BaseAdaptee::~BaseAdaptee() = default;


// Производный класс, интерфейс которого мы хотим подменить
class ConAdaptee : public BaseAdaptee
{
public:
    virtual void specRequest() override {std::cout << "AAAAA" << std::endl; }
};


// Базовый класс, который будет заниматься подменой
class BaseAdapter
{
public:
    virtual ~BaseAdapter() = 0;
    virtual void request() = 0;
};

BaseAdapter::~BaseAdapter() = default;

// Производный класс, который будет заниматься подменой
class ConAdapter: public BaseAdapter
{
private:
    // Храним ссылку на объект, интерфейс которого хотим подменить
    std::shared_ptr<BaseAdaptee> adaptee;

public:
    ConAdapter(std::shared_ptr<BaseAdaptee> _adaptee) : adaptee(_adaptee) {}

    virtual void request() override;
};

void ConAdapter::request()
{
    std::cout << "Adapter: ";
    if (adaptee)
        adaptee->specRequest();
    else
        std::cout << "No adaptee" << std::endl;
}

int main() {
    std::shared_ptr<BaseAdaptee> adaptee(new ConAdaptee());
    adaptee->specRequest();

    std::shared_ptr<BaseAdapter> adapter(new ConAdapter(adaptee));
    adapter->request();

    return 0;
}



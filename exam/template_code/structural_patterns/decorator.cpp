#include <iostream>
#include <memory>

class Component
{
public:
    virtual ~Component() = 0;
    virtual void operation() = 0;
};
Component::~Component() = default;

class ConComponent: public Component
{
    virtual void operation() override {std::cout << "AAAAA "; }
};


class Decorator: public Component
{
protected:
    std::shared_ptr<Component> component;
public:
    Decorator(std::shared_ptr<Component> _component) : component(_component) {}
};

class ConDecorator: public Decorator
{
public:
    using Decorator::Decorator;
    virtual void operation() override;
};

void ConDecorator::operation()
{
    if (component)
    {
        component->operation();
        std::cout << "BBBBB\n";
    }
}

int main()
{
    std::shared_ptr<Component> c(new ConComponent);
    std::shared_ptr<Component> d(new ConDecorator(c));

    d->operation(); // AAAAA BBBBB

    // Выпендриваемся и создаем декоратор для декоратора
    std::shared_ptr<Component> dd(new ConDecorator(d));

    dd->operation(); // AAAAA BBBBB BBBBB
}

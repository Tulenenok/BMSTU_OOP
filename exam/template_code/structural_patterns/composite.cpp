#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

class Component;

using VectorComponent = vector<shared_ptr<Component>>;
using IteratorComponent = VectorComponent::const_iterator;


class Component
{
public:
    virtual ~Component() = 0;

    virtual void operation() = 0;

    virtual bool isComposite() const {return false;}
    virtual bool add(shared_ptr<Component> _component) {return false;}
    virtual bool remove(const IteratorComponent& it) {return false;}
    virtual IteratorComponent begin() const {return IteratorComponent();}
    virtual IteratorComponent end() const {return IteratorComponent();}
};
Component::~Component() = default;         // или {} ?

class Figure: public Component
{
public:
    virtual void operation() override { cout  << "Figure method\n";}
};

class Camera: public Component
{
public:
    virtual void operation() override { cout  << "Camera method\n";}
};

class Composite: public Component
{
private:
    VectorComponent vec;

public:
    Composite() = default;
    Composite(shared_ptr<Component> first, ...);

    virtual void operation() override;

    virtual bool isComposite() const override {return true;}
    virtual bool add(shared_ptr<Component> _component) override {vec.push_back(_component); return true;}
    virtual bool remove(const IteratorComponent& it) override {vec.erase(it); return true;}
    virtual IteratorComponent begin() const override {return vec.begin();}
    virtual IteratorComponent end() const override {return vec.end();}
};

Composite::Composite(shared_ptr<Component> first, ...)
{
    for (shared_ptr<Component>*ptr = &first; *ptr; ++ptr)
        vec.push_back(*ptr);
}

void Composite::operation()
{
    cout << "Composite method: \n";
    for(auto elem: vec)
        elem->operation();
}


int main()
{
    shared_ptr<Component> fig1 = make_shared<Figure>();
    shared_ptr<Component> fig2 = make_shared<Figure>();

    shared_ptr<Component> cam1 = make_shared<Camera>();
    shared_ptr<Component> cam2 = make_shared<Camera>();

    auto composite1 = make_shared<Composite>(fig1, cam1, fig2, cam2, shared_ptr<Component>());

    composite1->operation();
    cout << "\n";

    composite1->add(make_shared<Camera>());
    composite1->remove(composite1->begin());

    composite1->operation();
    cout << "\n";
}


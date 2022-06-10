#include <iostream>
#include <memory>
#include <map>
#include <random>

using namespace std;

class Subject
{
public:
    virtual ~Subject() = 0;

    virtual pair<bool, double> request(size_t index) = 0;
    virtual bool changed() {return true;}
};

Subject::~Subject() = default;


class ConSubject: public Subject
{
private:
    bool flag{false};
    size_t counter{0};

public:
    virtual pair<bool, double> request(size_t index) override;
    virtual bool changed() override;
};

class Proxy: public Subject
{
protected:
    shared_ptr<ConSubject> conSub;

public:
    Proxy(shared_ptr<ConSubject> _con) : conSub(_con) {}
};

class ConProxy: public Proxy
{
private:
    map<size_t, double> cache;

public:
    using Proxy::Proxy;

    virtual pair<bool, double> request(size_t index) override;
};

bool ConSubject::changed()
{
    if (counter == 0)
        flag = true;

    if(++counter == 7)
    {
        counter = 0;
        flag = false;
    }

    return flag;
}

// ЫЫЫЫ, ладно
pair<bool, double> ConSubject::request(size_t index)
{
    random_device rd;

    mt19937 gen(rd());
    return pair<bool, double>(true, generate_canonical<double, 10>(gen));
}

pair<bool, double> ConProxy::request(size_t index)
{
    pair<bool, double> result;

    // Основного объекта у нас вообще нет
    if(!conSub)
    {
        cache.clear();
        result = pair<bool, double>(false, 0);
    }

    // Основной объект есть, но у него поменялось состояние
    if(!conSub->changed())
    {
        cache.clear();
        result = conSub->request(index);
        cache.insert(map<size_t, double>::value_type(index, result.second));
    }
        // Основной объект есть, состояние не менялось
    else
    {
        map<size_t, double>::const_iterator it = cache.find(index);

        // Пытаемся вытащить из кеша
        if(it != cache.end())
            result = pair<bool, double>(true, it->second);
        else
            // Не получается, все-таки делаем запрос
        {
            result = conSub->request(index);
            cache.insert(map<size_t, double>::value_type(index, result.second));
        }
    }

    return result;
}

int main()
{
    shared_ptr<ConSubject> subject = make_shared<ConSubject>();
    shared_ptr<Subject> proxy = make_shared<ConProxy>(subject);

    for(size_t i = 0; i < 21; i++)
    {
        // 1, 2, 3 -- делает запрос
        // 4, 5, 6 -- использует кеш
        // 7 -- состояние обновилось, опять делаем три раза запрос, три раза кеш
        cout << "( " << i + 1 << ", " << proxy->request(i % 3).second << " )" << endl;
        if ((i + 1) % 3 == 0)
            cout << endl;
    }
}


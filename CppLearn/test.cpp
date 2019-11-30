#include <iostream>

class Observable
{
public:
    void Register_(weak_ptr<Observer> x);
    void NotifyObservers();

private:
    mutable MutexLock mutex_;
    std::vector<weak_ptr<Observer> observers_;
    typedef std::vector<weak_ptr<Observer> >::iterator Iterator;
};

void Observable::NotifyObservers()
{
    MutexLockGuard lock(mutex_);
    Iterator it = observers_.begin();

    while (it != observers_.end())
    {
        shared_ptr<Observer> obj(it->lock());

        if (obj)
        {
            obj->Update();
            ++it;
        }
        else
        {
            it = observers_.erase(it);
        }
    }
}

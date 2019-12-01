#include <iostream>

class Request
{
public:
    void process() // __attribute__((noinline))
    {
        muduo::MutexLockGuard lock(mutex_);
        g_inventory.add(this);
        // ...
        
        print();
    }

    ~Request() __attribute__ ((noinline))
    {
        muduo::MutexLockGuard lock(mutex_);
        sleep(1);
        g_inventory.remove(this);
    }

    void print() const // __attribute__((noinline))
    {
        muduo::MutexLockGuard lock(mutex_);
        // ...
    }

private:
    mutable mmuduo::MutexLockGuard mutex_;
};

int main()
{
    Request req;
    req.process();
}

class Inventory
{
public:
    void add(Request *req)
    {
        muduo::MutexLockGuard lock(mutex_);
        requests_.insert(req);
    }

    void remove(Request *req) // __attribute__ ((noinline))
    {
        muduo::MutexLockGuard lock(mutex_);
        requests_.erase(req);
    }

    void printAll() const;

private:
    mutable muduo::MutexLock mutex_;
    std::set<request*> requests_;
};

Inventory g_inventory;

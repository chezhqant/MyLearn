#include <iostream>

MutexLock mutex;
std::vector<Foo> foos;

void post(const Foo &f)
{
    MutexLockGuard lock(mutex);
    postWitchLockHold(f);
}

void postWithLockHold(const Foo &f)
{
    foos.push_back(f);
}

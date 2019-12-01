class CountDownLatch : boost::noncopyable
{
public:
    explicit CountDownLatch(int count); //倒数几次
    void wait(); //等待计数值变为0
    void countDown(); //计数值减一

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};

CountDownLatch的实现同样简单
void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);

    while (count_ > 0)
    {
        condition_.wait();
    }
}

void CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    --count_;

    if (count_ == 0)
    {
        condition_.notifyAll();
    }
}

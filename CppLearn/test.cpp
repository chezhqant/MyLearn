#include <iostream>

class StoryFactory : public boost::enable_shared_from_this<StoryFactory>, boost::noncopyable
{
public:
    shared_ptr<Stock> get(const string &key)
    {
        shared_ptr<Stock> p_Stock;
        MutexLockGuard lock(mutex_);
        weak_ptr<Stock> &wk_Stock = stocks_[key];
        p_Stock = wk_Stock.lock();

        if (!p_Stock)
        {
            p_Stock.reset(new Stock(key),
                          boost::bind(&StoryFactory::weakDeleteCallback,
                                      boost::weak_ptr<StoryFactory>(shared_from_this)), _1);

            //上面必须强制将shared_from_this() 转型为weak_ptr，才不会延长生命期，因为boost::bind拷贝的是实参类型，不是形参类型
            wk_Stock = p_Stock;
        }

        return p_Stock;
    }

private:
    static void weakDeleteCallback(const boost::weak_ptr<StoryFactory> &wk_wk_Factory, Stock *stock)
    {
        shared_ptr<StockFactory> factory(wk_Factory.lock());

        if (factory)
        {
            factory->removeStock(stock);
        }
        delete stock;
    }

    void removeStock(Stock *stock)
    {
        if (stock)
        {
            MutexLockGuard lock(mutex_);
            stocks_.erase(stock->key());
        }
    }

private:
    mutable MutexLock mutex_;
    std::map<string, weak_ptr<Stock> > stock_;
};

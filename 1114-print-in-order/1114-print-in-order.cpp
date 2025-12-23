class Foo {
private:
    int counter;
    mutable std::mutex mut;
    mutable std::condition_variable cond;

public:
    Foo()
    : counter{1}
    , mut{}
    , cond{}
    {
    }

    void first(function<void()> printFirst) {
        std::unique_lock lock{mut};
        cond.wait(lock, [this](){
            return counter == 1;
        });
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        ++counter;
        lock.unlock();
        cond.notify_all();
    }

    void second(function<void()> printSecond) {
        std::unique_lock lock{mut};
        cond.wait(lock, [this](){
            return counter == 2;
        });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        ++counter;
        lock.unlock();
        cond.notify_all();
    }

    void third(function<void()> printThird) {
        std::unique_lock lock{mut};
        cond.wait(lock, [this](){
            return counter == 3;
        });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        counter = 1;
        lock.unlock();
        cond.notify_all();
    }
};
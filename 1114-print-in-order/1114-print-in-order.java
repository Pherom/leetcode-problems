class Foo {

    private final ReentrantLock lock;
    private final Condition cond;
    private int counter;

    public Foo() {
        lock = new ReentrantLock();
        cond = lock.newCondition();
        counter = 1;
    }

    public void first(Runnable printFirst) throws InterruptedException {
        lock.lock();
        try {
            // printFirst.run() outputs "first". Do not change or remove this line.
            printFirst.run();
            ++counter;
            cond.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public void second(Runnable printSecond) throws InterruptedException {
        lock.lock();
        try {
            while (counter < 2) {
                cond.await();
            }
            // printSecond.run() outputs "second". Do not change or remove this line.
            printSecond.run();
            ++counter;
            cond.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public void third(Runnable printThird) throws InterruptedException {
        lock.lock();
        try {
            while (counter < 3) {
                cond.await();
            }
            // printThird.run() outputs "third". Do not change or remove this line.
            printThird.run();
        } finally {
            lock.unlock();
        }
    }
}
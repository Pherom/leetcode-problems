using System.Threading;

public class Foo {

    private AutoResetEvent firstEvent;
    private AutoResetEvent secondEvent;

    public Foo() {
        firstEvent = new AutoResetEvent(false);
        secondEvent = new AutoResetEvent(false);
    }

    public void First(Action printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        firstEvent.Set();
    }

    public void Second(Action printSecond) {
        firstEvent.WaitOne();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        secondEvent.Set();
    }

    public void Third(Action printThird) {
        secondEvent.WaitOne();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
}
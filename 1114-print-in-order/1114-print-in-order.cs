using System.Threading;

public class Foo {

    private readonly object lck;
    private int counter = 1;

    public Foo() {
        lck = new object();
    }

    public void First(Action printFirst) {
        lock (lck) {
            // printFirst() outputs "first". Do not change or remove this line.
            printFirst();
            ++counter;

            Monitor.PulseAll(lck);
        }
    }

    public void Second(Action printSecond) {
        lock (lck) {
            while (counter != 2) {
                Monitor.Wait(lck);
            }

            // printSecond() outputs "second". Do not change or remove this line.
            printSecond();
            ++counter;

            Monitor.PulseAll(lck);
        }
    }

    public void Third(Action printThird) {
        lock (lck) {
            while (counter != 3) {
                Monitor.Wait(lck);
            }

            // printThird() outputs "third". Do not change or remove this line.
            printThird();
        }
    }
}
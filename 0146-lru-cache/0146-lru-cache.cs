public class LRUCache {

    private Dictionary<int, LinkedListNode<(int Key, int Value)>> dict;
    private LinkedList<(int Key, int Value)> list;
    private int capacity;

    public LRUCache(int capacity) {
        dict = new Dictionary<int, LinkedListNode<(int Key, int Value)>>();
        list = new LinkedList<(int Key, int Value)>();
        this.capacity = capacity;
    }
    
    public int Get(int key) {
        LinkedListNode<(int Key, int Value)> node;

        if (dict.TryGetValue(key, out node)) {
            list.Remove(node);
            list.AddFirst(node);
            return node.ValueRef.Value;
        }

        return -1;
    }
    
    public void Put(int key, int value) {
        if (dict.ContainsKey(key)) {
            LinkedListNode<(int Key, int Value)> node = dict[key];

            list.Remove(node);
            list.AddFirst(node);
            node.ValueRef = (key, value);
            return;
        }

        if (list.Count == capacity) {
            LinkedListNode<(int Key, int Value)> last = list.Last;

            dict.Remove(last.ValueRef.Key);
            list.RemoveLast();
        }

        list.AddFirst((key, value));
        dict.Add(key, list.First);
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.Get(key);
 * obj.Put(key,value);
 */
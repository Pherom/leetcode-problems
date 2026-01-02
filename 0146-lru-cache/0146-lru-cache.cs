public class LRUCache {

    private class Node {
        public int Key { get; set; }
        public int Value { get; set; }
        public Node Prev { get; set; }
        public Node Next { get; set; }

        public Node(int key, int value) {
            Key = key;
            Value = value;
            Prev = null;
            Next = null;
        }
    }

    private Dictionary<int, Node> dict;
    private Node head;
    private Node tail;
    private int count;
    private int capacity;

    public LRUCache(int capacity) {
        dict = new Dictionary<int, Node>();
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head.Prev = null;
        head.Next = tail;
        tail.Prev = head;
        tail.Next = null;
        count = 0;
        this.capacity = capacity;
    }
    
    private void MoveToFirst(Node node) {
        node.Prev.Next = node.Next;
        node.Next.Prev = node.Prev;
        node.Next = head.Next;
        node.Prev = head;
        head.Next.Prev = node;
        head.Next = node;
    }

    public int Get(int key) {
        Node node;

        if (!dict.TryGetValue(key, out node)) {
            return -1;
        }

        MoveToFirst(node);
        return node.Value;
    }
    
    public void Put(int key, int value) {
        Node node;
        
        if (dict.TryGetValue(key, out node)) {
            MoveToFirst(node);
            node.Value = value;
            return;
        }

        if (count == capacity) {
            Node last = tail.Prev;

            dict.Remove(last.Key);
            last.Key = key;
            last.Value = value;
            MoveToFirst(last);
            dict.Add(key, last);
            return;
        }

        Node created = new Node(key, value);
        created.Prev = head;
        created.Next = head.Next;
        head.Next.Prev = created;
        head.Next = created;
        dict.Add(key, created);
        ++count;
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.Get(key);
 * obj.Put(key,value);
 */
#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// Circular queue: push, pop, peek, size and is_empty take O(1) time.
// Storage takes O(capacity) space. A full queue rejects new elements.
class Queue
{
private:
    vector<int> collection;
    size_t head = 0;
    size_t count = 0;

public:
    explicit Queue(size_t capacity = 1000) : collection(capacity)
    {
        if(capacity == 0)
            throw invalid_argument("Queue capacity must be positive");
    }

    bool is_empty() const
    {
        return count == 0;
    }

    size_t size() const
    {
        return count;
    }

    bool push(int element)
    {
        if(count == collection.size())
            return false;

        collection[(head + count) % collection.size()] = element;
        ++count;
        return true;
    }

    int peek() const
    {
        if(is_empty())
            throw underflow_error("Queue is empty");

        return collection[head];
    }

    int pop()
    {
        int element = peek();
        head = (head + 1) % collection.size();
        --count;
        return element;
    }
};

int main()
{
    Queue queue(3);
    assert(queue.is_empty());
    assert(queue.size() == 0);

    // Fill the queue, then wrap around into the released storage.
    bool inserted = queue.push(10);
    assert(inserted);
    inserted = queue.push(20);
    assert(inserted);
    inserted = queue.push(30);
    assert(inserted);
    inserted = queue.push(40);
    assert(!inserted);
    assert(queue.size() == 3);
    assert(queue.peek() == 10);
    int removed = queue.pop();
    assert(removed == 10);
    inserted = queue.push(40);
    assert(inserted);

    for(int expected : {20, 30, 40})
    {
        removed = queue.pop();
        assert(removed == expected);
        cout << removed << '\n';
    }
    assert(queue.is_empty());

    for(bool pop_element : {false, true})
    {
        bool rejected = false;
        try
        {
            if(pop_element)
                queue.pop();
            else
                queue.peek();
        }
        catch(const underflow_error&)
        {
            rejected = true;
        }
        assert(rejected);
    }

    Queue single(1);
    for(int value : {0, -1, 42})
    {
        inserted = single.push(value);
        assert(inserted);
        removed = single.pop();
        assert(removed == value);
    }

    bool rejected = false;
    try
    {
        Queue invalid(0);
    }
    catch(const invalid_argument&)
    {
        rejected = true;
    }
    assert(rejected);
    return 0;
}

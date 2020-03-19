#include <bits/stdc++.h>

using namespace std;

#define MAX 1000

class Stack
{    
public:
    int top;
    int collection[MAX];
    Stack(/* args */);
    bool push(int element);
    int pop();
    int peek();
    bool is_empty();
};

Stack::Stack(/* args */)
{
    top = -1;
}

bool Stack::is_empty()
{
    return (top < 0);
}

bool Stack::push(int element)
{
    if(top >= (MAX-1))
    {
        cout << "Stack overflow\n";
        return false;
    }
    else 
    {
        collection[++top] = element;
        return true;
    }
}

int Stack::pop()
{
    if(is_empty())
    {
        cout << "Stack underflow";
        return 0;
    }
    else
    {
        top--;
        return collection[top];
    }
    
}


int Stack::peek()
{
    if(is_empty())
    {
        cout << "Stack is empty\n";
        return 0;
    }
    else
    {
        return collection[top];
    }
}


int main(int argc, char const *argv[])
{

    // Tests
    Stack my_stack;
    my_stack.push(10);
    cout << my_stack.peek() << endl;
    my_stack.push(20);
    cout << my_stack.peek() << endl;
    my_stack.pop();
    cout << my_stack.peek() << endl;
    
    return 0;
}

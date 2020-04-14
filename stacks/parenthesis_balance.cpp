// Fast solution to solve the problem: 
// https://www.urionlinejudge.com.br/judge/en/problems/view/1068


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
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string expression;

    while(getline(cin, expression))
    {
        Stack parenthesis_stack;
        bool starts_ok = true;
        for(size_t i = 0; i < expression.length(); i++)
        {
            if(expression[i] == '(')
                parenthesis_stack.push(1);
            
            else if(expression[i] == ')')
            {
                if(!parenthesis_stack.is_empty())
                    parenthesis_stack.pop();
                else
                {
                    cout << "incorrect" << endl;
                    starts_ok = false;
                    break;
                }
            }
        }
        if(starts_ok)
        {    
            if(parenthesis_stack.is_empty())
                cout << "correct" << endl;
            else
                cout << "incorrect" << endl;
        }
        
    }

    return 0;
}

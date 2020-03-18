#include <bits/stdc++.h>

using namespace std;

void singly_left_rotate(int array[], int size)
{
    int temp = array[0];
    for(size_t i = 1; i < size; i++)
    {
        array[i-1] = array[i];
    }
    array[size-1] = temp;
}

void print_array(int array[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    
}

int main(int argc, char const *argv[])
{

    int array[] = {1, 2, 3, 4, 5, 6, 7};
    const int size =  sizeof(array)/sizeof(array[0]);
    int d = 2;

    for (size_t i = 0; i < d; i++)
    {
        singly_left_rotate(array, size);
    }
    
    print_array(array, size);

    return 0;
}

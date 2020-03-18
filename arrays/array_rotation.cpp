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

int main(int argc, char const *argv[])
{

    int array[] = {1, 2, 3, 4, 5, 6, 7};
    const int size =  sizeof(array)/sizeof(array[0]);
    int d = 2;

    for (size_t i = 0; i < d; i++)
    {
        singly_left_rotate(array, size);
    }
    
    for (size_t i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << "\n";

    return 0;
}

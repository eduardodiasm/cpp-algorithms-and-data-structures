#include <bits/stdc++.h>

using namespace std;

int binary_search(int *array, int begin, int end, int key)
{

    if(begin <= end)
    {
        int mid = (begin + end)/2;
        if(key == array[mid])
            return mid;
        else if(key > array[mid])
            return binary_search(array, mid+1, end, key);
        else
            return binary_search(array, begin, mid-1, key);
    }
    
    return -1;
}

int main(int argc, char const *argv[])
{
    // Test
    int array[] = {1, 2, 3};
    cout << binary_search(array, 0, 2, 3) << endl;
    
    return 0;
}

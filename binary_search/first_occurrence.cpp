#include <bits/stdc++.h>

using namespace std;

int first_occurrence_binary_search(int *array, int begin, int end, int key)
{
    if(begin <= end)
    {
        int mid = (begin + end)/2;
        if((key == 0 ||key != array[mid-1]) && array[mid] == key)
            return mid;
        else if(key > array[mid])
            return first_occurrence_binary_search(array, mid+1, end, key);
        else
            return first_occurrence_binary_search(array, begin, mid-1, key);
    }
    
    return -1;
}

int main(int argc, char const *argv[])
{
    
    int array[] = {1, 2, 3, 3};
    cout << first_occurrence_binary_search(array, 0, 3, 3) << endl;    

    return 0;
}

#include <bits/stdc++.h>

using namespace std;

void find_the_largest_three(int array[], int n)
{

    int largests_found = 1;
    int last_found = array[n-1];
    cout << array[n-1] << "\n";
    // The first one found is the largest of the whole collection.

    for (int i = n - 2; i >= 0 && largests_found < 3; i--)
    {
        // To handle with duplicate values.
        if(array[i] != last_found)
        {
            last_found = array[i];
            largests_found++;
            cout << array[i] << "\n";
        }
    }
    
}

int main(int argc, char const *argv[])
{
    
    int array[] = {1, 2, 3, 8, 4, 5, 6, 7};
    int const SIZE = sizeof(array)/sizeof(array[0]);
    sort(array, array+SIZE);
    find_the_largest_three(array, SIZE);

    return 0;
}

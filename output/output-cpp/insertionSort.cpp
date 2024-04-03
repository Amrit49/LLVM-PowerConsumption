#include <iostream>

class InsertionSort {
public:
    // Function to sort array using insertion sort
    void sort(int arr[], int n) {
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    // A utility function to print array of size n
    static void printArray(int arr[], int n) {
        for (int i = 0; i < n; ++i)
            std::cout << arr[i] << " ";

        std::cout << std::endl;
    }
};

// Driver method
int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    InsertionSort ob;
    ob.sort(arr, n);

    InsertionSort::printArray(arr, n);

    return 0;
}

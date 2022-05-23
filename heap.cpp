/*
Read the marks obtained by students of second year in an online examination of particular subject.
Find out maximum and minimum marks obtained in that subject. Use heap data structure.
Analyze the algorithm.

Insert - O(logN)
Delete - O(logN)
Creation of Heap - O(N*logN)
Space - O(N) array of N elements
*/

#include <bits/stdc++.h>
using namespace std;


class min_heap
{
    int *harr;     // pointer to array of elements in heap
    int capacity;  // maximum possible size of min heap
    int heap_size; // current number of elements in min heap
public:
    // constructor: builds a heap from a given array a[] of given size
    min_heap(int capacity)
    {
        this->heap_size = 0;
        this->capacity = capacity;
        this->harr = new int[capacity];
    }

    // a utility function to swap two elements
    void swap(int *x, int *y)
    {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    // to get parent of node at index i
    int parent(int i) { return (i - 1) / 2; }

    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }

    // to extract the root which is the minimum element
    int delete_key()
    {
        if (heap_size <= 0)
            return INT_MAX;
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }
        // store the minimum value, and remove it from heap
        int root = harr[0];
        harr[0] = harr[heap_size - 1];
        // store the root elemet at the end of the array in the free space
        harr[heap_size - 1] = root;
        heap_size--;
        int i = 0;
        while (i < heap_size)
        {
            int l = left(i);
            int r = right(i);
            int smallest = i;
            if (l < heap_size && harr[l] < harr[i])
                smallest = l;
            if (r < heap_size && harr[r] < harr[smallest])
                smallest = r;
            if (smallest != i)
                swap(&harr[i], &harr[smallest]);
            else
                break;
            i = smallest;
        }
        return root;
    }

    // inserts a new key 'k'
    void insert_key(int k)
    {
        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // first insert the new key at the end
        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        // fix the min heap property if it is violated
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    void display_heap()
    {
        for (int i = 0; i < heap_size; i++)
        {
            cout << harr[i] << "\n";
        }
    }
};

int main()
{
    min_heap h(10);
    h.insert_key(10);
    h.insert_key(20);
    h.insert_key(15);
    h.insert_key(12);
    // h.delete_key();
    h.display_heap();
    return 0;
}

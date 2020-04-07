#include <iostream>

using namespace std;


template <class h_data>
class PriorityQueue
{
    h_data *arr;
    int size;
    int leafPtr;
    int rootPtr;

  public :
    PriorityQueue(int maxSize)
    {
        size = maxSize;
        arr = new h_data[size];
        for(int i = 0; i < size; i++)
        {
            arr[i] = -1;
        }
        leafPtr = 0;
        rootPtr = 1;
    }

    ~PriorityQueue()
    {
        delete [] arr;
    }

    void enQueue(h_data data)
    {
        arr[++leafPtr] = data;
        heapify(arr, rootPtr);
    }

    h_data deQueue()
    {
        h_data data = arr[rootPtr];

        arr[rootPtr] = -1;
        swap(arr[rootPtr], arr[leafPtr]);
        heapify(arr, rootPtr);

        return data;
    }

  private :
    void swap(int &x, int &y)
    {
        int tmp;
        tmp = x;
        x = y;
        y = tmp;
    }

    //This function heapifies data
    int heapify(h_data arr[], int rootPtr)
    {
        if(arr[2 * rootPtr] == -1 || 2 * rootPtr > 9)
        {
            return rootPtr;
        }

        int leftChildPtr, rightChildPtr, leftPtr, rightPtr;

        leftChildPtr = 2 * rootPtr;
        rightChildPtr = (2 * rootPtr) + 1;

        leftPtr = heapify(arr, leftChildPtr);
        rightPtr = heapify(arr, rightChildPtr);

        if(arr[rootPtr] < arr[leftPtr])
        {
            swap(arr[rootPtr], arr[leftPtr]);
        }
        if(arr[rootPtr] < arr[rightPtr])
        {
            swap(arr[rootPtr], arr[rightPtr]);
        }

        return rootPtr;
    }

  public :
    void printer()
    {
        for(int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

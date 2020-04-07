#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdarg>
#include <typeinfo>

#define DEBUG
#define DEBUG_LIST


using namespace std;

class experimental_IO
{
  public :
      void randGen(char *fileName, int size)
      {
            ofstream fout;
            fout.open(fileName);

            srand(time(NULL));
            for(int i = 0; i < size; i++)
            {
                fout << rand() - ((RAND_MAX)/2) << endl;
            }

            fout.close();
      }

      void getFromFile(int arr[], int size, char *fileName)
      {
            ifstream fin;
            fin.open(fileName);

            for(int i = 0; i < size; i++)
            {
                fin >> arr[i];
            }
            fin.close();
      }

      template <class inputArrayType, class functionType>
      double elapsedPracticalTime(functionType (*functionPtr)(inputArrayType *, int), inputArrayType *arr, int size)
      {
          clock_t initTime, finalTime;

          initTime = clock();
          functionPtr(arr, size);
          finalTime = clock();

          return (finalTime - initTime)/1000.00;
      }

      template <class inputArrayType>
      int arrayCopier(inputArrayType arrayFrom[], int sizeArrayFrom, inputArrayType arrayTo[], int sizeArrayTo)
      {
        if(sizeArrayTo < sizeArrayFrom)
            return -1;

        for(int i = 0; i < sizeArrayFrom; i++)
            arrayTo[i] = arrayFrom[i];

        return 0;
      }

      template <class inputArrayType>
      int arrayCopier(inputArrayType arrayFrom[], int startIndex, int endIndex, inputArrayType arrayTo[], int sizeArrayTo)
      {
        if(sizeArrayTo != (endIndex - startIndex + 1))
        {
            cout << "Got Err" << endl;
            return sizeArrayTo - (endIndex - startIndex + 1);
        }

        for(int i = 0, j = startIndex; j <= endIndex; i++, j++)
            arrayTo[i] = arrayFrom[j];

        return 0;
      }

      template <class inputArrayType>
      void arrayPrinter(inputArrayType array[], int size, char deliminator)
      {
        for(int i = 0; i < size; i++)
        {
            if(i != size - 1)
                cout << array[i] << deliminator;
            else
                cout << array[i];
        }
      }

      template <class inputArrayType>
      void arrayPrinter(inputArrayType array[], int initialIndex, int finalIndex, char deliminator)
      {
        for(int i = initialIndex; i <= finalIndex; i++)
        {
            if(i != finalIndex)
                cout << array[i] << deliminator;
            else
                cout << array[i];
        }
      }

      template <class inputArrayType>
      void arrayMerger(inputArrayType array1[], int size1, inputArrayType array2[], int size2, inputArrayType mergedArray[])
      {
          int i = 0, j = 0, k = 0;

          while(i != size1 && j != size2)
          {
              if(array1[i] <= array2[j])
              {
                  mergedArray[k] = array1[i];
                  ++i;
                  ++k;
              }
              else if(array1[i] > array2[j])
              {
                  mergedArray[k] = array2[j];
                  ++j;
                  ++k;
              }
          }

          while(i != size1)
          {
              mergedArray[k] = array1[i];
              ++i;
              ++k;
          }
          while(j != size2)
          {
              mergedArray[k] = array2[j];
              ++j;
              ++k;
          }
      }

};

template <class X> class STACK
{
    X *ptr;
    int top;
    int size;

  public :
    STACK(int size)
    {
        this -> size = size;
        ptr = new X[size];
        top = -1;
    }

    int push(X data)
    {
        if(top == size - 1)
        {
            return -1;
        }
        ptr[++top] = data;
    }

    X pop()
    {
        if(top != -1)
        {
            return ptr[top--];
        }

    }
};

template <class inputArrayType>
class SORT
{
  public :
    void merge_Sort(inputArrayType arr[], int size, float *time = NULL)
    {
        clock_t initTime, finalTime;
        int low = 0, high = size - 1;

        initTime = clock();
        mergeSort(arr, low, high);
        finalTime = clock();

        if(time != NULL)
            *time = (finalTime - initTime);
    }

  private :
    void mergeSort(inputArrayType arr[], int l, int h)
    {
        int m;
        m = l + (h - l) / 2;

        if(l == h)
            return;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, h);

        merge(arr, l, m, h);
    }

    void merge(inputArrayType arr[], int l, int m, int h)
    {
        inputArrayType arrL[m - l + 1];
        inputArrayType arrR[h - m];
        inputArrayType arrMerged[h - l + 1];
        experimental_IO ob;

        ob.arrayCopier(arr, l, m, arrL, m - l + 1);
        ob.arrayCopier(arr, m + 1, h, arrR, h - m);
        ob.arrayMerger(arrL, m - l + 1, arrR, h - m, arrMerged);

        for(int i = l, j = 0; i <= h; i++, j++)
        {
            arr[i] = arrMerged[j];
        }
    }
};

template <class dataType>
class LIST
{
    dataType *headPtr;
    dataType *endPtr;
    int element_countert;

  public :
      LIST()
      {
          headPtr = NULL;
          endPtr = NULL;
          element_countert = -1;
      }

      ~LIST()
      {
          delete [] headPtr;
      }

      int endSeeker()
      {
          return element_countert + 1;
      }

      void operator()(int argc,...)
      {
          int startIndex;
          int argCounter = argc;
          if(!headPtr)
          {
            headPtr = (dataType*) malloc(sizeof(dataType) * 1);
            argCounter -= 1;
          }
          realloc(headPtr, argCounter);

          startIndex = element_countert + 1;
          element_countert += argc;

          va_list args;
          va_start(args, argc);
          for(int i = startIndex; i < startIndex + argc; i++)
          {
              headPtr[i] = va_arg(args, dataType);
          }
          va_end(args);
      }

      void push(dataType value)
      {
          if(!headPtr)
          {
            headPtr = (dataType*) malloc(sizeof(dataType) * 1);
            headPtr[++element_countert] = value;
            return;
          }
          realloc(headPtr, 1);
          headPtr[++element_countert] = value;
      }

      dataType pop()
      {
          dataType tmp = headPtr[element_countert];
          delete &headPtr[element_countert--];
          return tmp;
      }

      dataType &operator[](int index)
      {
          if(index <= element_countert)
          {
              return headPtr[index];
          }
          else
          {
              cout << "...Exception : IndexOutOfBoundException!!! Process aborted." << endl;
              exit(-1);
          }
      }

      friend ostream &operator<<(ostream &outStream, LIST ob)
      {
          outStream << "Start__" << endl;
          for(int i = 0; i <= ob.element_countert ; i++)
          {
              outStream << "@ " << &ob.headPtr[i] << " Index[" << i << "] : " << ob.headPtr[i] << endl;
          }
          outStream << "__End\n" << endl;
          return outStream;
      }
};

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

#ifdef DEBUG
int main()
{
#ifdef DEBUG_LIST
    LIST <int> ob;
    ob.push(0);
    cout << ob;
    ob(5,1,2,3,4,5);
    cout << ob;
    ob.push(6);
    cout << ob;
    ob(3,7,8,9);
    cout << ob;
    ob.push(10);
    cout << ob;
    ob.pop();
    cout << ob;
    ob[3] = 30;
    cout << ob;

    for(int i = 0; i < ob.endSeeker(); i++)
    {
        cout << ob[i] << endl;
    }
#endif // DEBUG_LIST
}
#endif // DEBUG

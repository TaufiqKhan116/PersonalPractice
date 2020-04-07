#include <iostream>

using namespace std;

/*
Backtracking is an approach to find multiple solution tuples of a problem.
It is considered to be faster than brute force approach.
There are two types of constraints in problems solved by backtracking :
1. Explicit constraint :
    Suppose we have 8x8 checkerboard where * queens are to be fit. So all
    the solutions must be 8-tuples containing column position for 8 queens.
    So, solutions will be all permutations of position 1 to 8 (Counting from 1).
2. Implicit constraint :
    Any two of the queens must not share same row, column or diagonal. These
    constraints are used to filter the 8-tuples for actual solution.

Sample input :
4

Sample output :
Solution tuples are :
( 1 3 0 2 )
( 2 0 3 1 )
*/

class NQueen
{
    int x[8];

  public :
    NQueen()
    {
        for(int i = 0; i < 8; i++)
        {
            x[i] = -1;
        }
    }

    void arrayPrinter(int arr[], int size)
    {
        cout << "( ";
        for(int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << ")" << endl;
    }

    //x[j] holds columns that carries queens
    //k denotes row
    //i denotes column where we want to place the new queen
    //this functions check if any previous queen's column match with the new one
    //by x[j] == i
    //and if the new place is at any diagonal of any old queen by |x[j] - i| == |j - k|
    bool place(int k, int i)
    {
        for(int j = 0; j < k; j++)
        {
            if(x[j] == i || abs(x[j] - i) == abs(j - k))
            {
                return false;
            }
        }
        return true;
    }


    void NQueens(int k, int n)
    {
        for(int i = 0; i < n; i++)//For placing the first queen at 0, 1, 2, ..., n - 1 place respectively
        {
            if(place(k, i))
            {
                x[k] = i; //Placing the queen at k row x[k] column i.e i column

                if(k == n - 1)
                    arrayPrinter(x, n); //For queens other than first one
                else
                    NQueens(k + 1, n);
            }
        }
    }
};

int main()
{
    NQueen ob;
    int queenNo;

    cout << "Enter number of queens :" << endl;
    cin >> queenNo;

    cout << "Solution tuples are :" << endl;
    ob.NQueens(0, queenNo);
    return 0;
}

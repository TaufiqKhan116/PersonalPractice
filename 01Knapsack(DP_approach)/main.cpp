#include <iostream>

using namespace std;

/*
A problem should satisfy two properties to be solved efficiently using DP
approach. These properties are :

1. Optimal substructure :
    The optimal solution of the problem can be constructed from
    the optimal solutions of its subproblems. In other words
    problem can be break apart on basis of Bellman's optimality
    principal.

2. Overlapping subproblems :
    Solution of one problem is used multiple times to solve
    multiple subproblems. In other words the problem is not
    inductively proven to be optimal at each state.

0/1 knapsack problem satisfies these properties as follows :
        Filling a knapsack with objects of optimal profit satisfying
    the constraint may require optimal solutions to previous levels
    of constraint.
        Suppose optimal solution to a 8kg knapsack is 5kg and 3kg.
    The optimal solution to the problem of filling a 3kg knapsack
    is needed here. So, subproblems are over lapping.

There are two ways to implement DP :
1. Top to bottom memoization methd( Not memorization)
2. Bottom to up method
Here Bottom to top method is used.

Sample input :
8
4
1 2
2 3
5 4
6 5

Sample output :
Printing table :
0 0 0 0 0 0 0 0 0
0 0 1 1 1 1 1 1 1
0 0 1 2 2 3 3 3 3
0 0 1 2 5 5 6 7 7
0 0 1 2 5 6 6 7 8

Maximum profit :8

*/

class Object
{
  public :
    int profit;
    int weight;
    bool flag;
};

class knapSack0_1
{
    int arr[30][30];
    int objectNo;
    int constraint;

  public :

    knapSack0_1()
    {
        for(int i = 0; i < 30; i++)
            for(int j = 0; j < 30; j++)
                arr[i][j] = 0;
    }

    //Sorting objects in increasing order on basis of weight
    void SORT_Objects(Object objArr[], int size)
    {
        for(int i = 1; i < size; i++)
            for(int j = i + 1; j <= size; j++)
                if(objArr[j].weight < objArr[i].weight)
                {
                    Object tmp = objArr[j];
                    objArr[j] = objArr[i];
                    objArr[i] = tmp;
                }
    }

    //At each step we momoize optimal solution to each constraint level of knapsack
    //( 0, 1, 2, ..., constraint) with particular number of object ( 0, 1, 2, ...,objectNo)
    //Thus we get our optimal solution to the problem ( 'constraint' filled with 'objectNO')
    //at the (objectNo, constraint) index.
    void generateTable(Object objArr[], int objectNo, int constraint)
    {
        this -> objectNo = objectNo;
        this -> constraint = constraint;

        for(int i = 1; i <= objectNo; i++)
        {
            for(int j = 0; j <= constraint; j++)
            {
                if(j - objArr[i].weight < 0)
                    arr[i][j] = arr[i - 1][j];
                else
                    arr[i][j] = max(arr[i - 1][j], arr[i-1][j - objArr[i].weight] + objArr[i].profit);
            }
            cout << endl;
        }
    }

    void printer()
    {
        for(int i = 0; i <= objectNo; i++)
        {
            for(int j = 0; j <= constraint; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << "\nMaximum profit :" << arr[objectNo][constraint] << endl;
    }

};

int main()
{
    int noOfObject, constraint;
    Object arr[21];
    knapSack0_1 ob;

    cout << "Enter constraint, number of object, profit and weight :" << endl;

    cin >> constraint >> noOfObject;


    arr[0].profit = 0;
    arr[0].weight = 0;
    for(int i = 1; i <= noOfObject; i++)
    {
        cin >> arr[i].profit >> arr[i].weight;
        arr[i].flag = false;
    }

    ob.SORT_Objects(arr, noOfObject);
    ob.generateTable(arr, noOfObject, constraint);

    cout << "Printing table :" << endl;
    ob.printer();

    return 0;
}

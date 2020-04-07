#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
The greedy approach to solve knapsack problem gives optimal solution only to
the fractional knapsack problem if greedy is being on the basis of profit-weight
ratio. For 0/1 knapsack this approach only gives feasible solution and doesn't
guarantee the solution being optimal.

Sample input :
20
3
18 25
15 24
10 15

Sample output :
15      24

N.B. The solution is not guaranteed to be optimal.
*/

class Object
{
  public :
    int weight;
    int profit;
    bool flag;
};

void loading_01_Knapsack(Object arr[], int size, int constraint);

int main()
{
    int noOfObject, constraint;
    Object arr[10];

    //Input segment
    cout << "Enter constraint, number of object, weight and profit :" << endl;
    cin >> constraint >> noOfObject;
    for(int i = 0; i < noOfObject; i++)
    {
        Object ob;
        cin >> ob.weight >> ob.profit;
        ob.flag = false;

        arr[i] = ob;
    }

    //Sorting the array on basis of profit-weight ratio
    for(int i = 0; i < noOfObject - 1; i++)
    {
        for(int j = i + 1; j < noOfObject; j++)
        {
            if( ((float)arr[i].profit/ (float)arr[i].weight) < ((float)arr[j].profit/ (float)arr[j].weight) )
            {
                Object tmp;
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    //Being greedy on basis of profit-weight ratio
    loading_01_Knapsack(arr, noOfObject, constraint);

    //Output
    cout << "\nIncluded objects :\nWeight\tProfit" << endl;
    for(int i = 0; i < noOfObject; i++)
    {
        if(arr[i].flag)
            cout << arr[i].weight << "\t" << arr[i].profit << endl;
    }

    return 0;
}

void loading_01_Knapsack(Object arr[], int size, int constraint)
{
    int w = constraint;
    for(int i = 0; i < size; i++)
    {
        if(arr[i].weight > w)
            break;
        w -= arr[i].weight;
        arr[i].flag = true;
    }
    //For fractional knapsack
    //w -= w / arr[i].weight;
}

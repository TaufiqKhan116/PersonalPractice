#include <iostream>

using namespace std;

/*
Solving 01Knapsack problem using top down approach
*/

int wt[5] = {0, 2, 3, 4, 5};
int p[5] = {0, 1, 2, 5, 6};
int memo[5][9] = {0};

//Using usual divide and conquer approach
int KNAP(int n, int w)
{
    if(n == 0 || w == 0)
        return 0;
    if(w - wt[n] < 0)
        return KNAP(n - 1, w);
    else
        return max(KNAP(n - 1, w), KNAP(n - 1, w - wt[n]) + p[n]);
}

//Using memoization with divide and conquer
int KNAP_MEMO(int n, int w)
{
    if(n == 0 || w == 0)
    {
        memo[n][w] = 0;
        return memo[n][w];
    }

    if(w - wt[n] < 0)
    {
        if(memo[n][w] == 0)
            memo[n][w] = KNAP_MEMO(n - 1, w);

        return memo[n][w];
    }
    else
    {
        if(memo[n][w] == 0)
            memo[n][w] = max(KNAP_MEMO(n - 1, w), KNAP_MEMO(n - 1, w - wt[n]) + p[n]);

        return memo[n][w];
    }
}

int main()
{
    cout << "Maximum profit :" << KNAP_MEMO(4, 8) << endl;

    cout << "\nMemoization table :" << endl;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

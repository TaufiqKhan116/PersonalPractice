#include <iostream>
#include <ctime>

using namespace std;

class Fib
{
    int mem[100];

  public :
    Fib()
    {
        for(int i = 0;i <100; i++)
            mem[i] = 0;
    }

    int fibDp(int n)
    {
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;

        if(mem[n] != 0)
            return mem[n];

        int tmp = fib(n - 1) + fib(n - 2);

        if(mem[n] == 0)
            mem[n] = tmp;

        return tmp;

    }

    int fib(int n)
    {
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;

        return fib(n - 1) + fib(n - 2);
    }
};

int main()
{
    Fib ob;
    float t1, t2, tdiff;

    t1 = clock();
    ob.fibDp(46);
    t2 = clock();
    cout << t2 - t1 << endl;

    t1 = clock();
    ob.fib(46);
    t2 = clock();
    cout << t2 - t1 << endl;
    return 0;
}

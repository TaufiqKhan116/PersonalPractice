#include <iostream>
#include <vector>

using namespace std;

int wt[10][10] = {-1};

/*
In electrical distribution system, oil distribution system or any other systems
where several terminals are needed system loss may occur traversing terminals.
To boost up the system repeater is needed to be placed at terminals where system
loss is higher than a certain tolerance level. Tree vertex splitting(TVS) algorithm
gives the minimum number of nodes where repeaters should be placed.

N.B.Our this form of TVS algorithm is specified for binary trees and won't work for
other types of trees.
*/
class treeVertexSplitter
{
    //tree definition starts
    int prnt[10] = {-1, 0, 0, 1,  2, 2,  3,  3,  5,  5};
    int lft[10]  = {1, -1, 4, 6, -1, 8, -1, -1, -1, -1};
    int node[10] = {1,  2, 3, 4,  5, 6,  7,  8,  9, 10};
    int rght[10] = {2,  3, 5, 7, -1, 9, -1, -1, -1, -1};
    //tree definition ends
    //Initial weights of vertices
    int d[10]    = {0,  0, 0, 0,  0, 0,  0,  0,  0,  0};
    //Weights of paths among vertices
    int w[10][10];
    //Actual root
    int start;
    //Output vector
    vector <int> vctr;

  public :
    treeVertexSplitter()
    {
        start = 0;
        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                w[i][j] = -1;
        //Assigning paths' weights
        w[1][2] = 4;
        w[1][3] = 2;
        w[2][4] = 2;
        w[4][7] = 1;
        w[4][8] = 4;
        w[3][5] = 1;
        w[3][6] = 3;
        w[6][9] = 2;
        w[6][10] = 3;
    }
    void splitTreeVertices()
    {
        //Calling TVS
        TVS(0, 5);
    }
    void output()
    {
        //Printing output vector
        for(int i = 0; i < vctr.size(); i++)
        {
            cout << node[vctr[i]] << endl;
        }
    }

  private :
    int TVS(int root, int tol)
    {
        int ld = 0;
        int rd = 0;
        //Basis : Returns if leaf is encountered
        if(lft[root] == -1 && rght[root] == -1)
        {
            d[root] = 0;
            return d[root];
        }

        //Recursive call : Only if child node exists
        if(lft[root] != -1)
            ld = TVS(lft[root], tol);
        if(rght[root] != -1)
            rd = TVS(rght[root], tol);

        //Getting current root weight
        cout << node[lft[root]] << ":" << w[node[root]][node[lft[root]]] << endl;
        d[root] = max(
                      ( ld + w[node[root]][node[lft[root]]] ),
                      ( rd + w[node[root]][node[rght[root]]] )
                      );

        //Checking if current root's weight along with its parent node's path weight is crossing the tolerance level or not
        if(root != start && d[root] + w[node[prnt[root]]][node[root]] > tol)
        {
            vctr.push_back(root);
            d[root] = 0;
            return d[root];
        }
        return d[root];
    }
};

int main()
{
    treeVertexSplitter ob;
    ob.splitTreeVertices();

    cout << "Vertices need to be splitted :" << endl;
    ob.output();

    cout << "\n" << wt[2][-2];

    return 0;
}

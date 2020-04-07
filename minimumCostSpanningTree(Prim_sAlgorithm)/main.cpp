#include <iostream>
#define infinity 1000
#define size 7

using namespace std;

/*
A spanning tree of a graph is a connected path including all vertices of the
graph and excluding any cycle. So, for a graph of |e| edges its spanning trees
will be of |e| - 1 edges. A minimum spanning tree of a weighted graph is the
tree including edges that minimize total weight traversed along the edges.

Prim's Algorithm :
1. Select the edge of minimum cost.
2. Select the edge of minimum cost that
   has a common vertex with the last edge(or tree).
3. Repeat 2 till |e| - 1 edges are obtained.
*/
class minimumCostSpanningTree
{
    int adjMat[size][size];
    int near[size];
    int edges[size - 1][2];
    int cost;

  public :
    //initializing adjacency matrix and other variables
    minimumCostSpanningTree()
    {
        cost = 0;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                adjMat[i][j] = infinity;
            }
        }

        adjMat[0][1] = 28;
        adjMat[1][0] = 28;
        adjMat[0][5] = 10;
        adjMat[5][0] = 10;
        adjMat[1][2] = 16;
        adjMat[2][1] = 16;
        adjMat[1][6] = 14;
        adjMat[6][1] = 14;
        adjMat[2][3] = 12;
        adjMat[3][2] = 12;
        adjMat[3][4] = 22;
        adjMat[4][3] = 22;
        adjMat[3][6] = 18;
        adjMat[6][3] = 18;
        adjMat[4][5] = 25;
        adjMat[5][4] = 25;
        adjMat[4][6] = 24;
        adjMat[6][4] = 24;
    }

    void printer()
    {
        for(int i = 0; i < size - 1; i++)
        {
            for(int j = 0; j < 2; j++)
            {
                cout << edges[i][j] << " ";
            }
            cout << endl;
        }
    }

    int generateMinimumCostSpanningTree()
    {
        return primsMinimumCostSpanningTree();
    }

  private :
    //Prim's algorithm
    int primsMinimumCostSpanningTree()
    {
        //Obtaining the edge of minimum weight from adjacency matrix
        int min = adjMat[0][0];
        int k, l;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(adjMat[i][j] < min)
                {
                    min = adjMat[i][j];
                    k = i;
                    l = j;
                }
            }
        }
        cost += min;
        edges[0][0] = k; //Inserting first vertex of first edge into output
        edges[0][1] = l; //Inserting second vertex of first edge into output

        //Initializing near : near is the array such that (indexOfNear, Near) is an edge connected to the vertex denoted by indexOfNear and near
        for(int i = 0; i < size; i++)
        {
            if(adjMat[i][l] < adjMat[i][k])
                near[i] = l;
            else
                near[i] = k;
        }
        near[k] = near[l] = -1;

        //Loop for generating tree
        for(int i = 1; i < size - 1; i++)
        {
            int m, newNode;

            //finding minimum weighted edge that is connected with indexOfNear and Near
            m = infinity;
            for(int j = 0; j < size; j++)
            {
                if(near[j] != -1 && adjMat[j][near[j]] < m)
                {
                    m = adjMat[j][near[j]];
                    newNode = j;
                }
            }
            //Inserting new edge to output
            edges[i][0] = near[newNode];
            edges[i][1] = newNode;
            cost += adjMat[newNode][near[newNode]];
            near[newNode] = -1;

            //Updating near
            for(int c = 0; c < size; c++)
            {
                if(near[c] != -1 && adjMat[c][near[c]] > adjMat[c][newNode])
                {
                    near[c] = newNode;
                }
            }
        }
        return cost;
    }
};

int main()
{
    minimumCostSpanningTree ob;
    int cost = ob.generateMinimumCostSpanningTree();
    cout << "Edges for minimum cost spanning tree :" << endl;
    ob.printer();
    cout << "\nMinimum Cost : " << cost << endl;
    return 0;
}

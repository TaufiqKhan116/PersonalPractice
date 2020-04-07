#include <iostream>
#define infinity 1000
#include <vector>
#include <set>
#define size 7

using namespace std;

/*
Kruskal's algorithm :
1. Sort the edges according to weight in increasing order.
2. Always take the minimum weighted edge.
3. Include the edge in Output if the edge doesn't produce a cycle.
*/

//Class for storing edges
class Edge
{
  public :
    int from;
    int to;
    int weight;
};

class minimumCostSpanningTree
{
    Edge edgArr[9];
    vector<set <int>> setArr;
    vector <Edge> vctr;
    bool flag[size];
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

        for(int i = 0; i < size; i++)
        {
            flag[i] = false;
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
        vector <Edge> :: iterator itr;

        for(itr = vctr.begin(); itr != vctr.end(); itr++)
        {
            cout << itr -> from << " " << itr -> to << endl;
        }
    }

    int generateMinimumCostSpanningTree()
    {
        edgeMaker();
        return krusKulMinimumCostSpanningTree();
    }

  private :
    //Transforming edges from adjacency matrix form to object form
    void edgeMaker()
    {
        int k = 0;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                if(adjMat[i][j] != infinity)
                {
                    edgArr[k].from = i;
                    edgArr[k].to = j;
                    edgArr[k].weight = adjMat[i][j];
                    adjMat[i][j] = infinity;
                    adjMat[j][i] = infinity;
                    k++;
                }
            }
        }
    }

    int krusKulMinimumCostSpanningTree()
    {
        //Every vertex is assumed to be a distinct disjoint tree
        for(int i = 0; i < 7; i++)
        {
            set<int> tmp;
            tmp.insert(i);
            setArr.push_back(tmp); //Every element of the setArr vector is set representing a tree of one vertex
        }

        //Sorting edge objects on basis of their weights
        for(int i = 0; i < 8; i++)
        {
            for(int j = i + 1; j < 9; j++)
            {
                if(edgArr[i].weight > edgArr[j].weight)
                {
                    Edge tmp;
                    tmp = edgArr[j];
                    edgArr[j] = edgArr[i];
                    edgArr[i] = tmp;
                }
            }
        }

        //Checking for the edge not forming a cycle
        //the find function returns true if the two vertices of the edge are in the same disjoint tree and the edge is not included into output
        //the find function returns false if the two vertices of the edge are not in the same disjoint tree and the edge are included into output
        //if the find function returns false then the two vertices of the edge must be in different trees
        //uPos and vPos variables are assigned the root pointer of those different trees(position in the setArr vector)
        //As the two vertices are included into output they are now should be of same tree
        //So we do union operation on trees at uPos position and vPos position of setArr and assigns the union tree to the uPos position
        //and clear the tree pointed by vPos
        for(int i = 0; i < 9; i++)
        {
            int uPos, vPos;
            if(!find(edgArr[i].from, edgArr[i].to, uPos, vPos))
            {
                vctr.push_back(edgArr[i]);
                cost += edgArr[i].weight;
                setArr[uPos].insert(setArr[vPos].begin(), setArr[vPos].end()); //Union of trees pointed by uPos and vPos and assigning the new tree into uPos
                setArr[vPos].clear(); //clearing the old vPos tree
            }
        }
        return cost;
    }

    bool find(int vertex1, int vertex2, int &pos, int &pos1)
    {
        set <int> :: iterator itr1, itr2;
        for(int i = 0; i < 7; i++)
        {
            itr1 = setArr[i].find(vertex1);
            itr2 = setArr[i].find(vertex2);
            if(itr1 != setArr[i].end() && itr2 != setArr[i].end())
            {
                pos = pos1 = i;
                return true;
            }
        }
        for(int i = 0; i < 7; i++)
        {
            itr1 = setArr[i].find(vertex1);
            if(itr1 != setArr[i].end())
            {
                pos = i;
            }
        }
        for(int i = 0; i < 7; i++)
        {
            itr1 = setArr[i].find(vertex2);
            if(itr1 != setArr[i].end())
            {
                pos1 = i;
            }
        }
        return false;
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

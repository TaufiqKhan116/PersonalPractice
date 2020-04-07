#include <iostream>
#include <vector>
#define infinity 1000
#define size 6

using namespace std;
/*
Dijkstra's shortest path algorithm for single source is used to determine the minimum
path length needed to be traversed to get to each vertex from the source vertex.
A slightly updated version of this algorithm can also provide the exact path need
to be traversed along with the path length.
Modification : As it is a greedy approach, for the path to reach a vertex we only need to
remember the exact previous vertex for each state.
*/
class Dijkstra
{
    int cost[size][size];
    bool store[size]; //Flag for vertices included
    int dist[size]; //Array of distance from source vertex (distance from source to last vertex + last vertex to particular vertex)

    vector <int> path[6];
    int tempVrtx;
  public :
    //Initializing cost table
    Dijkstra()
    {
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                cost[i][j] = infinity;
            }
        }
        cost[0][1] = 2;
        cost[0][2] = 4;
        cost[1][2] = 1;
        cost[1][3] = 7;
        cost[2][4] = 3;
        cost[3][5] = 1;
        cost[4][3] = 2;
        cost[4][5] = 5;

        for(int i = 0; i < size; i++)
        {
            dist[i] = infinity;
        }
    }

    void findingShortestPaths(int source)
    {
        shortestPaths(source);
    }

    void printer()
    {
        for(int c = 0; c < size; c++)
        {
            if(dist[c] == infinity)
            {
                cout << "[" << c << "] : " << "x" << endl;
                continue;
            }
            cout << "[" << c << "] : " << dist[c] << " ";

            cout << "Path :";
            vector <int> :: iterator itr;
            for(itr = path[c].begin(); itr != path[c].end(); itr++)
            {
                cout << *itr << " ";
            }
            cout << endl;
        }
    }
  private :
    void shortestPaths(int source)
    {
        tempVrtx = source; //[Modification] : For remembering the exact previous vertex(Initially the source as the first vertex except source can only be reached from source)

        //Initializing distances from source to all vertices (If any vertex is unreachable the distance is infinity)
        for(int i = 0; i < size; i++)
        {
            store[i] = false; //Initializing with false : It will be true for vertices we are done with
            dist[i] = cost[source][i];
        }
        store[source] = true; //As we are done with source vertex its flag is true
        dist[source] = 0; //Distance from source to source is 0

        for(int i = 1; i < size; i++)
        {
            //Selecting vertex that is of minimum distance(path weight) from source vertex
            int min = infinity;
            int minVrtx;
            for(int j = 0; j < size; j++)
            {
                if(!store[j] && dist[j] < min)
                {
                    min = dist[j];
                    minVrtx = j;
                }
            }
            store[minVrtx] = true; //Now this vertex of minimum distance from last already traversed vertex is included into the already done with list

            path[minVrtx] = path[tempVrtx];
            path[minVrtx].push_back(tempVrtx);

            //Relaxation(Updating distance list) : if last weight of particular vertex > (weight of new vertex + distance of particular vertex from new vertex)
            //then (update the weight of particular vertex) : last weight of particular vertex = (weight of new vertex + distance of particular vertex from new vertex)
            //- - - -> u ---> v
            //         4  2   infinity
            //infinity > 4 + 2
            //So, - - - -> u ---> v
            //             4  2   4 + 2 = size
            for(int k = 0; k < size; k++)
            {
                if(!store[k])
                {
                    if(dist[k] > dist[minVrtx] + cost[minVrtx][k])
                        dist[k] = dist[minVrtx] + cost[minVrtx][k];
                }
            }
            tempVrtx = minVrtx;
        }
    }
};

int main()
{
    Dijkstra ob;
    int source;
    cout << "Enter source vertex : ";
    cin >> source;
    ob.findingShortestPaths(source);
    cout << "\nShortest paths from sources :" << endl;
    ob.printer();
}

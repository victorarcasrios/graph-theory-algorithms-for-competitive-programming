#include<bits/stdc++.h>
using namespace std;

class Graph {
    list<int> *adjacentList;
    int NumberOfNodes;
    
    public:
        Graph(int numberOfNodes){
            NumberOfNodes = numberOfNodes;
            adjacentList = new list<int>[NumberOfNodes]; 
        }
        
        void addEdge(int a, int b){
            adjacentList[a].push_back(b);
            adjacentList[b].push_back(a);        
        }
        
        int getCenter(){
            int numberOfNodes = static_cast<int>(adjacentList->size());
            
            for(int i=0; i<numberOfNodes; i++){
                int numberOfEdges = static_cast<int>(adjacentList[i].size());
                if(numberOfEdges == NumberOfNodes - 1){
                    return i;
                }
            }
            
            return -1;
        }
};

int findCenter(vector<vector<int>>edges)
{
    int size = static_cast<int>(edges.size());
    Graph graph(size);
    
    for(vector<int> edge : edges){
        graph.addEdge(edge[0], edge[1]);
    }
    
    int center = graph.getCenter();
    
    return center;
}

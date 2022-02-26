#include "find-center-of-star-graph.h"
#include<bits/stdc++.h>
using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjacentList;

    public:
        
        void addEdge(int a, int b){
            if (!containsNode(a)) {
                vector<int> adjacentNodes;
                adjacentList.insert({a, adjacentNodes});
            }

            adjacentList[a].push_back(b);

            if (!containsNode(b)) {
                vector<int> adjacentNodes;
                adjacentList.insert({b, adjacentNodes});
            }

            adjacentList[b].push_back(a);        
        }

        bool containsNode(int node) {
            try {
                adjacentList.at(node);
                return true;
            } catch (out_of_range oor) {
                return false;
            }
        }
        
        int getCenter(){
            int numberOfNodes = static_cast<int>(adjacentList.size());
            
            for(pair<int, vector<int>> p : adjacentList){
                int numberOfEdges = static_cast<int>(p.second.size());
                if(numberOfEdges == numberOfNodes - 1){
                    return p.first;
                }
            }
            
            return -1;
        }
};

int findCenter(vector<vector<int>>edges)
{
    Graph graph;
    
    for(vector<int> edge : edges){
        graph.addEdge(edge[0], edge[1]);
    }
    
    int center = graph.getCenter();
    
    return center;
}

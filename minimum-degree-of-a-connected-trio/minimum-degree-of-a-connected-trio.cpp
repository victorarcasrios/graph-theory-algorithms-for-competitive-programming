#include "minimum-degree-of-a-connected-trio.h"
#include<bits/stdc++.h>
using namespace std;

class Graph {
    unordered_map<int, vector<int>> adjacentList;

    public:
    void addNode(int nodeId) {
        vector<int> adjacentNodes;
        adjacentList.insert({nodeId, adjacentNodes});
    }

    void addEdge(int a, int b){
        adjacentList[a].push_back(b);
        adjacentList[b].push_back(a);        
    }

    vector<vector<int>> getTrios() {
        vector<vector<int>> trios;
        vector<int> discarded;

        for(auto nodeAndNeighbours : adjacentList) {
            auto node = nodeAndNeighbours.first;
            auto neighbours = nodeAndNeighbours.second;

            if (neighbours.size() < 2) {
                discarded.push_back(node);
                continue;
            }

            for (auto neighbourA : neighbours) {
                if (contains(discarded, neighbourA))
                    continue;

                for (auto neighbourB : neighbours) {
                    if (neighbourA == neighbourB
                            || contains(discarded, neighbourB))
                            continue;

                    if (areNeighbours(neighbourA, neighbourB)) {
                        vector<int> trio {node, neighbourA, neighbourB};
                            
                        if (!containsEquivalentTrio(trios, trio))
                            trios.push_back(trio);
                    }
                }
            }
        }

        return trios;
    }

    int calculateMinimumDegree(vector<int> trio) {
        int degree = 0;

        for (auto node : trio) {
            for (auto neighbour : adjacentList[node]) {
                if (!contains(trio, neighbour)) {
                    degree = degree + 1;
                }
            }
        }

        return degree;
    }

    private:

    bool containsEquivalentTrio(vector<vector<int>> trios, vector<int> trio) {
        for (auto aTrio : trios) {
            vector<int> matches;

            for (auto a : trio) {
               if (contains(aTrio, a))
                   matches.push_back(a);
            }

            if (matches.size() == trio.size())
                return true;
        }

        return false;
    }

    bool contains(vector<int> haystack, int needle) {
        return find(haystack.begin(), haystack.end(), needle) != haystack.end();
    }

    bool areNeighbours(int nodeA, int nodeB) {
        for (auto node : adjacentList[nodeA]) {
            if (node == nodeB)
                return true;
        }

        return false;
    }
};

int minTrioDegree(int n, vector<vector<int>> edges) {
    Graph graph;

    for (int i = 1; i <= n; i++)
        graph.addNode(i);

    for (auto edge : edges)
        graph.addEdge(edge[0], edge[1]);

    vector<vector<int>> trios = graph.getTrios();

    if (trios.size() == 0)
        return -1;

    for (auto trio : trios) {
        cout << "|->(" << trio[0] << ")<--->(" << trio[1] << ")<--->(" << trio[2] << ")<-|\n";
    }

    auto trio = trios[0];

    auto minDegree = graph.calculateMinimumDegree(trio);

    return minDegree;
}


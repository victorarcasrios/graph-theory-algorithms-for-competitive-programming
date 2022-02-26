#include "maximal-network-rank.h"
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

        int calculateMaximalNetworkRank() {
            vector<pair<int, int>> edges;

            for (auto nodeAndNeighbours : adjacentList) {
                auto node = nodeAndNeighbours.first;
                auto neighbours = nodeAndNeighbours.second;

                for (auto neighbour : neighbours) {
                    pair<int, int> edge(node, neighbour);
                    if (containsPair(edges, edge))
                            continue;

                    edges.push_back(edge);
                }
            }

            return edges.size();
        }

    private:

        bool containsPair(vector<pair<int, int>> pairs, pair<int, int> pair) {
            for (auto p : pairs) {
                if ((pair.first == p.first && pair.second == p.second) 
                        || (pair.first == p.second && pair.second == p.first))
                    return true;
            }

            return false;
        }
};

int maximalNetworkRank(int n, vector<vector<int>> roads) {
    Graph graph;

    for (auto road : roads) {
        graph.addEdge(road[0], road[1]);
    }

    return graph.calculateMaximalNetworkRank();
}

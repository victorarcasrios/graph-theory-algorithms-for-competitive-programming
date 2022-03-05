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

    void print() {
        for(auto nodeAndNeighbours : adjacentList) {
            auto node = nodeAndNeighbours.first;
            auto neighbours = nodeAndNeighbours.second;

            cout << "(" << node << ") has " << neighbours.size() << " neighbours\n";

            for(auto neighbour : neighbours)
                cout << " \\--->(" << neighbour << ")\n";
        }
    }

    vector<Graph> getChildGraphs() {
        vector<vector<int>> graphsNodes;
        vector<int> nodes = getKeys(adjacentList);
        vector<int> checkedNodes;
        
        vector<int> nodesToCheck { nodes[0] };

        vector<int> graphNodes;

        while (nodesToCheck.size() > 0 
                && checkedNodes.size() < nodes.size()) {
            auto node = nodesToCheck.back();

            nodesToCheck.pop_back();

            checkedNodes.push_back(node);

            for (auto neighbour : adjacentList[node]) {
                if (!contains(graphNodes, neighbour))
                    graphNodes.push_back(neighbour);

                if (!contains(nodesToCheck, neighbour)
                        && !contains(checkedNodes, neighbour)) {
                    nodesToCheck.push_back(neighbour);
                }
            }

            if (nodesToCheck.size() == 0) {
                graphsNodes.push_back(graphNodes);

                graphNodes = {};

                if (checkedNodes.size() < nodes.size()) {
                    bool found = false;
                    for (auto anotherNode : nodes) {
                        if (!found 
                                && !contains(checkedNodes, anotherNode)) {
                            nodesToCheck.push_back(anotherNode);

                            found = true;
                        }

                    }
                }
            }
        }

        vector<Graph> graphs;

        for (auto graphNodes : graphsNodes) {
            graphs.push_back(mapNodesToGraph(graphNodes));
        }

        return graphs;
    }

    vector<vector<int>> getGroups() {
        vector<vector<int>> groups;
        vector<int> nodes = getKeys(adjacentList);
        vector<int> checkedNodes = {};

        vector<int> nodesToCheck = {nodes[0]};

        while(nodesToCheck.size() > 0
                && checkedNodes.size() < nodes.size()) {
            auto node = nodesToCheck.back();

            nodesToCheck.pop_back();

            checkedNodes.push_back(node);

            auto neighbours = adjacentList[node];

            if (neighbours.size() < 2) {
                checkedNodes.push_back(node);
                continue;
            }

            vector<int> nodeGroup = {node};

            for(auto neighbourA : neighbours) {
                for(auto neighbourB : neighbours) {
                    if(!areNeighbours(neighbourA, neighbourB))
                        continue;

                    if(!contains(nodeGroup, neighbourA)) {
                        nodeGroup.push_back(neighbourA);
                        nodesToCheck.push_back(neighbourA);
                    }

                    if(!contains(nodeGroup, neighbourB)){
                        nodeGroup.push_back(neighbourB);
                        nodesToCheck.push_back(neighbourB);
                    }
                }
            }

            if (nodeGroup.size() > 1)
                groups.push_back(nodeGroup);
        }
        
        groups = uniquify(groups);

        return groups;
    }

    vector<vector<int>> getTrios() {
        vector<vector<int>> groups = getGroups();
        vector<vector<int>> trios = {};

        for(auto group : groups) {
            if (group.size() == 3) {
                trios.push_back(group);
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

    vector<vector<int>> uniquify(vector<vector<int>> lists) {
        vector<vector<int>> outLists;

        for (auto inList : lists) {
            bool duplicated = false;
            for (auto outList : outLists) {
                if (inList.size() == outList.size()
                        && isEquivalent(inList, outList)) {
                    duplicated = true;

                    break;
                }
            }

            if (!duplicated)
                outLists.push_back(inList);
        }

        return outLists;
    }

    Graph mapNodesToGraph(vector<int> nodes) {
        Graph graph;

        for (auto node : nodes)
            graph.addNode(node);

        for (auto node : nodes) {
            for (auto neighbour : adjacentList[node])
                graph.addEdge(node, neighbour);
        }

        return graph;
    }

    vector<int> getKeys(unordered_map<int, vector<int>> uMap) {
        vector<int> keys;
        for (auto aPair : uMap) {
            keys.push_back(aPair.first);
        }
        return keys;
    }

    bool isEquivalent(vector<int> aList, vector<int> bList) {
        vector<int> matches;

        for (auto aItem : aList) {
            if (contains(bList, aItem))
                matches.push_back(aItem);
        }

        return matches.size() == aList.size();
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
    for (int from = 0; from < edges.size(); from++) {
        auto tos = edges[from];
        cout << "[" << tos[0];
        for(int i = 1; i < tos.size(); i++) {
            auto to = tos[i];
            cout << ", " << to;
        }
        cout << "]\n";
    }

    Graph mainGraph;

    for (int i = 1; i <= n; i++)
        mainGraph.addNode(i);

    for (auto edge : edges)
        mainGraph.addEdge(edge[0], edge[1]);

    vector<Graph> graphs = mainGraph.getChildGraphs();

    cout << "The number of child graphs is " << graphs.size() << "\n";

    int graphNumber = 1;
    for (auto graph : graphs) {
        cout << "Graph #" << graphNumber++ << ":\n";
        graph.print();

        auto groups = graph.getGroups();

        cout << "The number of groups is " << groups.size() << "\n";

        for (auto group : groups) {
            cout << "\t|--";
            for (auto node : group)
                cout << "--(" << node << ")--";
            cout << "--|\n";
        }
    }

    int minDegree = -1;

    /*
    for (auto graph : graphs) {
        vector<vector<int>> trios = graph.getTrios();

        for (auto trio : trios) {
            auto trioMinDegree = graph.calculateMinimumDegree(trio);

            cout << "|->(" << trio[0] << ")<--->(" << trio[1] << ")<--->(" << trio[2] << ")<-| MIN: " << trioMinDegree << "\n";

            if (trioMinDegree != 0 
                    && (minDegree == -1 || trioMinDegree < minDegree)) {
                minDegree = trioMinDegree;
            }
        }
    }
    */

    return minDegree;
}


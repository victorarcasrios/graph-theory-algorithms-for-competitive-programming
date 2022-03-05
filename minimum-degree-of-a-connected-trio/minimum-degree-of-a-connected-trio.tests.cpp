#include "minimum-degree-of-a-connected-trio.h"
#include<bits/stdc++.h>
using namespace std;

int test(int nodes, vector<vector<int>> edges, int expectedResult) {
    int result = minTrioDegree(nodes, edges);

    if (result != expectedResult) {
        cout << "Test KO. Expected " << expectedResult << ". Got " << result << "\n";

        return 1;
    }

    cout << "Test OK.\n";

    return 0;
}

int main() {
    vector<vector<int>> edges {
        {1, 2},
        {1, 3},
        {3, 2},
        {4, 1},
        {5, 2},
        {3, 6}
    };
    
    int exitCode = test(6, edges, 3);

    vector<vector<int>> edges2 {
        {1, 3},
        {4, 1},
        {4, 3},
        {2, 5},
        {5, 6},
        {6, 7},
        {7, 5},
        {2, 6}
    };

    exitCode = test(7, edges2, 0);

    if (exitCode == 0) {
        cout << "Test OK. Exercise solved.";
    }

    return exitCode;
}

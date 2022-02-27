#include "maximal-network-rank.h"
#include<bits/stdc++.h>
using namespace std;

int test(int cities, vector<vector<int>> roads, int expectedResult) {
    int result = maximalNetworkRank(cities, roads);

    if (result != expectedResult) {
        cout << "Test KO. Expected " << expectedResult << ". Got " << result << ".\n";

        return 1;
    }

    cout << "Test OK.\n";
    
    return 0;
}


int main() {
    vector<vector<int>> roads {
        {0, 1},
        {0, 3},
        {1, 2},
        {1, 3}
    };

    int exitCode = test(4, roads, 4);

    vector<vector<int>> roads2 {
        {0, 1},
        {0, 3},
        {1, 2},
        {1, 3},
        {2, 3},
        {2, 4}
    };

    exitCode += test(5, roads2, 5);

    if (exitCode == 0)
        cout << "Exercise solved. \n";
    
    return exitCode;
}

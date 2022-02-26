#include "maximal-network-rank.h"
#include<bits/stdc++.h>
using namespace std;

int main() {
    int cities = 4;
    vector<vector<int>> roads {
        {0, 1},
        {0, 3},
        {1, 2},
        {1, 3}
    };

    int result = maximalNetworkRank(cities, roads);

    if (result != 4) {
        cout << "Test KO. Expected 4. Got " << result << ".\n";

        return 1;
    }

    cout << "Test OK. Exercise solved.\n";
    
    return 0;
}

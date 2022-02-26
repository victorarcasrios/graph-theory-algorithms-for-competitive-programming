#include "find-center-of-star-graph.h"
#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> edges {
        {1, 2},
        {2, 3},
        {4, 2}
    };

    int center = findCenter(edges);

    if (center != 2) {
        cout << "Test KO. Expected 2. Got " << center << "\n";

        return 1;
    }

    cout << "Test OK. Exercise solved \n";

    return 0;
}

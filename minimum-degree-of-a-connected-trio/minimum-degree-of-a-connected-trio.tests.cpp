#include "minimum-degree-of-a-connected-trio.h"
#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> edges {
        {1, 2},
        {1, 3},
        {3, 2},
        {4, 1},
        {5, 2},
        {3, 6}
    };
    
    int result = minTrioDegree(6, edges);

    if (result != 3) {
        cout << "Test KO. Expected 3. Got " << result;

        return 1;
    }

    cout << "Test OK. Exercise solved.";

    return 0;
}

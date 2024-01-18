#include <bits/stdc++.h>
using namespace std;

int main () {
    int n, i, j;
    cout <<"n:";
    cin >> n;
    unordered_map<int, unordered_set<int>> graph;

    for (int k = 0; k < n - 1; k++) {
        cin >> i >> j;
        graph[i].insert(j);
        graph[j].insert(i);
    }

    queue<int> leaves;
    int numOfLeaves = 0;

    int leaf, adjNode;

    while (n > 2) {
        numOfLeaves = 0;

        for (const auto& entry : graph) {
            if (entry.second.size() == 1) {
                leaves.push(entry.first);
                numOfLeaves++;
            }
        }

        for (int i = 0; i < numOfLeaves; i++) {
            leaf = leaves.front();
            leaves.pop();
            // cout<<leaf<<endl;
            adjNode = *(graph[leaf].begin());
            graph[adjNode].erase(leaf);
            graph.erase(leaf);
        }

        n -= numOfLeaves;
    }

    cout<<endl;
     for (const auto& entry : graph) {
        cout << entry.first << " ";
    }

    return 0;
}

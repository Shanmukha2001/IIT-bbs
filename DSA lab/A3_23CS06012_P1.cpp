#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int val;
    int ew;
    int vis;
};
void transpose(vector<vector<node *>> &graph, vector<vector<node *>> &tgraph, int k)
{
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            vector<node *> Node;
            Node = graph[i];
            int first = Node[j]->val;
            node *newNode = new node();
            newNode->val = i;
            tgraph[first].push_back(newNode);
        }
    }
}
void dfs(vector<vector<node *>> &tgraph, vector<bool> &visited, int curNode, vector<pair<int, int>> &markedEdges)
{
    vector<node *> temp;
    temp = tgraph[curNode];
    for (int i = 0; i < tgraph[curNode].size(); i++)
    {
        node *tempNode = temp[i];
        if (visited[tempNode->val] == 0)
        {
            markedEdges.push_back({tempNode->val, curNode});
            visited[tempNode->val] = 1;
            dfs(tgraph, visited, tempNode->val, markedEdges);
        }
    }
}
void edgeDfs(vector<vector<node *>> &graph, vector<pair<int, int>> &markedEdges, int curNode, vector<int> &finalRes)
{
    vector<node *> temp;
    temp = graph[curNode];
    for (int i = 0; i < graph[curNode].size(); i++)
    {
        node *tempNode = temp[i];
        pair<int, int> markedEdge = {curNode, tempNode->val};
        if (find(markedEdges.begin(), markedEdges.end(), markedEdge) == markedEdges.end())
        {
            if (tempNode->vis == 0)
            {
                tempNode->vis = 1;
                finalRes.push_back(tempNode->ew);
                edgeDfs(graph, markedEdges, tempNode->val, finalRes);
            }
        }
    }

    for (int i = 0; i < graph[curNode].size(); i++)
    {

        node *tempNode = temp[i];
        auto edge = {curNode, tempNode->val};

        if (tempNode->vis == 0)
        {
            tempNode->vis = 1;
            finalRes.push_back(tempNode->ew);
            edgeDfs(graph, markedEdges, tempNode->val, finalRes);
        }
    }
}
int main()
{
    int n, k;
    cout << "enter n" << endl;
    cin >> n;
    cout << "enter k" << endl;
    cin >> k;
    int nodes = pow(k, n - 1);
    int c = -1;
    vector<vector<node *>> graph(nodes);
    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < k; j++)
        {
            c++;
            c = (c % nodes);
            node *temp = new node();
            temp->ew = j;
            temp->val = c;
            graph[i].push_back(temp);
        }
    }
    vector<vector<node *>> tgraph(nodes);
    transpose(graph, tgraph, k);
    vector<bool> visited(nodes, 0);
    vector<pair<int, int>> markedEdges;
    dfs(tgraph, visited, 0, markedEdges);
    vector<int> finalRes;
    edgeDfs(graph, markedEdges, 0, finalRes);
    for (int i = 0; i < finalRes.size(); i++)
    {
        cout << finalRes[i];
    }
    return 0;
}
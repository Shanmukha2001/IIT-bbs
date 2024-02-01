#include <iostream>
#include <bits/stdc++.h>
// completely done code
using namespace std;
class node
{
public:
    int val;
    int id;
    int vis;
    node()
    {
        this->vis = 0;
    }
};
void transpose(vector<vector<node *>> &graph, vector<vector<node *>> &tgraph, int k)
{
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < k; j++)
        {
            vector<node *> temp;
            temp = graph[i];
            int val1 = temp[j]->val;
            node *tempNode = new node();
            tempNode->val = i;
            tgraph[val1].push_back(tempNode);
        }
    }
}

void dfs(vector<vector<node *>> &tgraph, vector<bool> &visited, int curNode, vector<pair<int, int>> &markedEdges, int k)
{
    vector<node *> temp;
    temp = tgraph[curNode];
    for (int i = 0; i < k; i++)
    {
        node *tempNode = temp[i];
        if (visited[tempNode->val] == 0)
        {
            markedEdges.push_back({tempNode->val, curNode});
            visited[tempNode->val] = 1;
            // cout << tempNode->val;
            dfs(tgraph, visited, tempNode->val, markedEdges, k);
        }
    }

    return;
}

void dfs2(vector<vector<node *>> &graph, vector<pair<int, int>> &markedEdges, int curNode, vector<pair<int, int>> &ans, vector<int> &finalRes, int k)
{
    vector<node *> temp;
    temp = graph[curNode];
    int flag = 0;

    for (int i = 0; i < k; i++)
    {

        node *tempNode = temp[i];
        pair<int, int> edge = {curNode, tempNode->val};
        if (find(markedEdges.begin(), markedEdges.end(), edge) == markedEdges.end())
        {
            if (tempNode->vis == 0)
            {
                tempNode->vis = 1;
                ans.push_back({curNode, tempNode->val});
                finalRes.push_back(tempNode->id);
                flag = 1;
                dfs2(graph, markedEdges, tempNode->val, ans, finalRes, k);
            }
        }
    }

    for (int i = 0; i < k; i++)
    {

        node *tempNode = temp[i];
        auto edge = {curNode, tempNode->val};

        if (tempNode->vis == 0)
        {
            tempNode->vis = 1;
            ans.push_back({curNode, tempNode->val});
            finalRes.push_back(tempNode->id);
            flag = 1;
            dfs2(graph, markedEdges, tempNode->val, ans, finalRes, k);
        }
    }
}



int main()
{
    int k = 3;
    int n = 2; // that means n = n+1
    int nodes = pow(k, n);
    int count = -1;
    vector<vector<node *>> graph(nodes);

    for (int i = 0; i < nodes; i++)
    {
        for (int j = 0; j < k; j++)
        {

            count++;
            count = (count % nodes);
            node *temp = new node();
            temp->id = j;
            temp->val = count;
            graph[i].push_back(temp);
        }
    }
    vector<vector<node *>> tgraph(nodes);

    // transpose of graph ids dosent matter in this transpose graph

    transpose(graph, tgraph, k);

    // find dfs for transpose graph and mark the edges
    vector<bool> visited(nodes, 0);

    vector<pair<int, int>> markedEdges;
    dfs(tgraph, visited, 0, markedEdges, k);

    // dfs on original graph
    // may be you have to write different dfs because, have to take care
    // unmarked first

    visited.assign(nodes, 0);

    vector<pair<int, int>> ans;
    vector<int> finalRes;

    // visited array should be edges as
    //  we are finding the path so

    dfs2(graph, markedEdges, 0, ans, finalRes, k);
    for (auto i : finalRes)
    {
        cout << i;
    }

    return 0;
}
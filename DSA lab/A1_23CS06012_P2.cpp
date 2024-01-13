#include <bits/stdc++.h>

using namespace std;

struct Rectangle
{
    int x, h, pos;

    bool operator<(const Rectangle &otherPoint) const
    {
        if (x != otherPoint.x)
            return x > otherPoint.x;

        if (pos == 1 && otherPoint.pos == 1)
            return h > otherPoint.h;
        else if (pos == -1 && otherPoint.pos == -1)
            return h < otherPoint.h;
        return pos > otherPoint.pos;
    }
};

int main()
{
    int n, y;
    cout << "enter n:";
    cin >> n;
    cin.ignore();
    Rectangle r;
    vector<Rectangle> points;
    priority_queue<Rectangle, vector<Rectangle>, less<Rectangle>> priorityQ;

    for (int i = 0; i < n; i++)
    {
        cout << "enter x y h:";
        cin >> r.x >> y >> r.h;
        cin.ignore();

        r.pos = -1;
        points.push_back(r);
        // priorityQ.push(r);

        r.x = y;
        r.pos = 1;
        points.push_back(r);
        // priorityQ.push(r);
    }

    vector<pair<int, int>> out;
    multiset<int> maxHeap;
    int prevMaxHeight = 0;
    maxHeap.insert(0);
    int top;

    for (auto p : points)
    {
        priorityQ.push(p);
    }

    while (!priorityQ.empty())
    {
        Rectangle currentRectangle = priorityQ.top();
        priorityQ.pop();

        if (currentRectangle.pos == -1)
            maxHeap.insert(currentRectangle.h);
        else
            maxHeap.erase(maxHeap.find(currentRectangle.h));

        int currentMaxHeight = *maxHeap.rbegin();
        if (currentMaxHeight != prevMaxHeight)
        {
            out.push_back(make_pair(currentRectangle.x, currentMaxHeight));
            prevMaxHeight = currentMaxHeight;
        }
    }

    for (auto &point : out)
    {
        cout << point.first << " " << point.second << endl;
    }

    return 0;
}
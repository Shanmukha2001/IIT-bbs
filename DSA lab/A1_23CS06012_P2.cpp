#include <bits/stdc++.h>

using namespace std;

struct Rectangle
{
    int x, h, pos;

    bool operator<(const Rectangle &otherPoint) const
    {
        if (x > otherPoint.x)
            return true;
        else if (x == otherPoint.x && pos > otherPoint.pos)
            return true;
        else if (x == otherPoint.x && pos == otherPoint.pos && h > otherPoint.h)
            return true;
        return false;
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
        priorityQ.push(r);

        r.x = y;
        r.pos = 1;
        points.push_back(r);
        priorityQ.push(r);
    }

    vector<pair<int, int>> out;
    multiset<int> maxHeap;
    maxHeap.insert(0);
    int top;
    while (!priorityQ.empty())
    {
        top = *maxHeap.rbegin();
        Rectangle topRectangle = priorityQ.top();
        std::cout << "x: " << topRectangle.x << ", height: " << topRectangle.h << ", pos: " << topRectangle.pos << std::endl;
        if (topRectangle.pos == -1)
            maxHeap.insert(topRectangle.h);
        else
            maxHeap.erase(maxHeap.find(topRectangle.h));

        if (!maxHeap.empty() && top != *maxHeap.rbegin())
            out.push_back(make_pair(topRectangle.x, *maxHeap.rbegin()));
            
        priorityQ.pop();
    }

    for (auto &point : out)
    {
        cout << point.first << " " << point.second << endl;
    }

    return 0;
}
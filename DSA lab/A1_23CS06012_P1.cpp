#include <bits/stdc++.h>

using namespace std;
const double PI = 3.141592653589793;

double collinear(pair<double, double> p1,pair<double, double> p2,pair<double, double> p3){
   double area = p1.first*(p2.second - p3.second) +
                  p2.first*(p3.second - p1.second) +
                  p3.first*(p1.second - p2.second);
    return area == 0;
}

double calDistance(pair<double, double> p, pair<double, double> q)
{
    return sqrt(pow((q.first - p.first), 2) + pow((q.second - p.second), 2));
}

void intersectionOfLines(double a1, double b1, double c1, double a2, double b2, double c2, double &centerX, double &centerY)
{
    double denominator = a1 * b2 - a2 * b1;
    if (denominator == 0)
    {
        centerX = DBL_MAX;
        centerY = DBL_MAX;
    }
    else
    {
        centerX = (b2 * c1 - c2 * b1) / denominator;
        centerY = (a1 * c2 - a2 * c1) / denominator;
    }
}

void perpendicularBisectorLine(pair<double, double> p, pair<double, double> q, double &a, double &b, double &c)
{
    a = q.first - p.first;
    b = q.second - p.second;
    double midpoint_pq_x = (p.first + q.first) / 2;
    double midpoint_pq_y = (p.second + q.second) / 2;
    c = -b * midpoint_pq_x + a * midpoint_pq_y;
}

void findCenterAndRadius(pair<double, double> p, pair<double, double> q, pair<double, double> r, double &centerX, double &centerY, double &radius)
{
    double a1, b1, c1;
    perpendicularBisectorLine(p, q, a1, b1, c1);
    double a2, b2, c2;
    perpendicularBisectorLine(q, r, a2, b2, c2);
    intersectionOfLines(a1, b1, c1, a2, b2, c2, centerX, centerY);
    if (centerX != DBL_MAX)
        radius = calDistance(p, make_pair(centerX, centerY));
    else
        radius = DBL_MAX;
}

bool covers(pair<double, double> point, pair<double, double> circumCircleCenter, double radius)
{
    return pow(circumCircleCenter.first - point.first, 2) + pow(circumCircleCenter.second - point.second, 2) <= pow(radius, 2);
}

double minAreaUsingThreePoints(vector<pair<double, double>> points, int n,double &x,double &y)
{
    double circleX = DBL_MAX, circleY = DBL_MAX, circleRadius = DBL_MAX;
    double minCircleX = DBL_MAX, minCircleY = DBL_MAX, minRadius = DBL_MAX;
    bool coversAllPoints = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                // cout<<collinear(points[i], points[j], points[k]);
                if(collinear(points[i], points[j], points[k])) continue;
                findCenterAndRadius(points[i], points[j], points[k], circleX, circleY, circleRadius);
                coversAllPoints = all_of(points.begin(), points.end(), [&](pair<double, double> x) { return covers(x, make_pair(circleX, circleY), circleRadius); });
                if (circleRadius != DBL_MAX && circleRadius < minRadius && coversAllPoints)
                {
                    minRadius = circleRadius;
                    x = circleX;
                    y = circleY;
                }
                circleX = DBL_MAX, circleY = DBL_MAX, circleRadius = DBL_MAX;
            }
        }
    }
    // cout<< " 3poin "<<x<<" "<<y<<" "<<minRadius<<endl;
    return PI * minRadius * minRadius;
}

double minAreaUsingTwoPoints(vector<pair<double, double>> points, int n,double &x,double &y)
{
    double radius = 0, minRadius = DBL_MAX;
    bool coversAllPoints = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            radius = (calDistance(points[i], points[j]) / 2);
            double midPointX = (points[i].first + points[j].first) / 2;
            double midPointY = (points[i].second + points[j].second) / 2;
            coversAllPoints = all_of(points.begin(), points.end(), [&](pair<double, double> x) { return covers(x, make_pair(midPointX, midPointY), radius); });
            if (coversAllPoints && minRadius > radius){
                x = midPointX;
                y = midPointY;
                minRadius = radius;
                }
        }
    }
    // cout<< " 2poin "<<x<<" "<<y<<" "<<minRadius<<endl;
    return PI * minRadius * minRadius;
}

int main()
{
    int n;
    double x, y,x2,y2;
   do{
    cout << "Enter n:";
    cin >> n;
    }while(n<2);

    vector<pair<double, double>> points;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter x y:";
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    double min1 = minAreaUsingThreePoints(points, n,x,y);
    double min2 = minAreaUsingTwoPoints(points, n,x2,y2);
    // cout<<min1<<" "<<min2<<endl;
    if(min1>min2){
        cout<<x2<<" "<<y2<<" "<<min2;
    }else{
        cout<<x<<" "<<y<<" "<<min1;
    }
    return 0;
}
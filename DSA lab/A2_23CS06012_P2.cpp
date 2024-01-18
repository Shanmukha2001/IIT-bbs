#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout <<"n:";
    cin >> n;
    vector<int> dp(5, 1);
 
    for (int i = 2; i <= n; i++) {
        for (int j = 3; j >= 0; j--)
            dp[j] += dp[j + 1];
    }
 
    cout << accumulate(dp.begin(),dp.end(),0);
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    #endif
    int n, s;
    scanf("%d%d", &n, &s);
    vector<int> c(n), y(n);
    for (int i=0; i<n; ++i) {
        int x, yy;
        scanf("%d%d", &x, &yy);
        c[i] = x;
        y[i] = yy;
    }
    long long cost = c[0], sum = cost * y[0];
    for (int i=1; i<n; ++i) {
        cost = min(cost + s, static_cast<long long>(c[i]));
        sum += cost * y[i];
    }
    cout << sum << endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <utility>

using namespace std;
int n,t;
vector<pair<int, int> > cows;


int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d%d",&n, &t);
    while(n--){
        int l,r;
        scanf("%d%d",&l, &r);
        cows.push_back(make_pair(l, r));
    }
    sort(cows.begin(), cows.end());
    int start = 1, ans=0, cow=0, i=0, maxlen=-1;
    while(start <= t){
        for(; i<(int)cows.size(); ++i){
            if(cows[i].first > start) break;
            maxlen = max(maxlen, cows[i].second);
        }
        if(i == cow){
            ans = -1;
            break;
        }
        cow = i;
        ++ans;
        start = maxlen + 1;
    }
    printf("%d\n", ans);
    return 0;
}

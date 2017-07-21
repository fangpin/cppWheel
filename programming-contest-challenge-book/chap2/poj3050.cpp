#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;
int a[5][5];
map<int, int> m;
int dx[]={0, 0, -1, 1}, dy[]={-1, 1, 0, 0};

void dfs(int ii, int jj, int deep, int num){
    if(deep == 6){
        m[num]++;
    }
    else{
        for(int i=0; i<4; ++i){
            int ni = ii + dx[i], nj = jj + dy[i];
            if(0<=ni && ni<5 && 0<=nj && nj<5){
                dfs(ni, nj, deep+1, num*10+a[ni][nj]);
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            dfs(i, j, 0, 0);
        }
    }
    printf("%d\n", (int)m.size());
    return 0;
}

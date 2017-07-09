#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
char place[22][22];
int cnt = 0;
int dx[]={0, 0, -1, 1}, dy[]={-1, 1, 0, 0};
int w, h, sx, sy;

void dfs(int x, int y){
    ++cnt;
    place[y][x] = '#';
    for(int i=0; i<4; ++i){
        int nx = x + dx[i], ny = y + dy[i];
        // printf("%d %d %d %d\n", nx, ny, w, h);
        if(0<=nx && nx<w && 0<=ny && ny<h && place[ny][nx]!='#'){
            dfs(nx, ny);
        }
    }
}

int main(){
    // freopen("in.txt", "r", stdin);
    while(scanf("%d%d",&w, &h), w+h){
        for(int i=0; i<h; ++i){
            scanf("%s", place[i]);
            for(int j=0, len=strlen(place[i]); j<len; ++j){
                if(place[i][j] == '@'){
                    sx = j;
                    sy = i;
                }
            }
        }
        cnt = 0;
        dfs(sx, sy);
        printf("%d\n", cnt);
    }
    return 0;
}

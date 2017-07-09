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

int w,h;
int sx, sy, ex, ey;
int place[22][22];
int dx[]={0, 0, -1, 1}, dy[]={-1, 1, 0, 0};
bool ok;

#define is_out(x, y) (x)<0 || (x)>=w || (y)<0 || (y)>=h
#define is_end(x, y) (x)==ex && (y)==ey
#define can_move(x, y) !(( is_out(x+dx[0], y+dy[0]) || is_block(x+dx[0], y+dy[0]) ) && \
                         ( is_out(x+dx[1], y+dy[1]) || is_block(x+dx[1], y+dy[1]) ) && \
                         ( is_out(x+dx[2], y+dy[2]) || is_block(x+dx[2], y+dy[2]) ) && \
                         ( is_out(x+dx[3], y+dy[3]) || is_block(x+dx[3], y+dy[3]) ) )
#define is_block(x, y) place[(y)][(x)]==1

void dfs(int limit, int deep, int x, int y){
    if(deep > limit || !can_move(x, y)) return;
    for(int i=0; i<4; ++i){
        int nx = x, ny = y;
        bool first_step = true;
        do{
            nx += dx[i];
            ny += dy[i];
            if(is_out(nx, ny)) break;
            if(is_end(nx, ny)){
                ok = true;
                return;
            }
            if(first_step){
                first_step = false;
                if(place[ny][nx]!=0 && place[ny][nx]!=2 && place[ny][nx]!=3) break;
            }
            if(is_block(nx, ny)){
                place[ny][nx] = 0;
                dfs(limit, deep+1, nx-dx[i], ny-dy[i]);
                place[ny][nx] = 1;
                break;
            }
        }while(true);
    }
}

int main(){
    // freopen("in.txt", "r", stdin);
    while(scanf("%d%d",&w, &h), w+h){
        memset(place, 0, sizeof(int)*22*22);
        for(int i=0; i<h; ++i){
            for(int j=0; j<w; ++j){
                scanf("%d", &place[i][j]);
                if(place[i][j] == 2){
                    sx = j;
                    sy = i;
                }
                else if(place[i][j] == 3){
                    ex = j;
                    ey = i;
                }
            }
        }
        ok = false;
        int limit;
        for(limit=1; limit<=10; ++limit){
            dfs(limit, 1, sx, sy);
            if(ok) break;
        }
        printf("%d\n", limit == 11 ? -1: limit);
    }
    return 0;
}

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

bool place[305][305];
bool safe[305][305];
bool vis[305][305];
int dx[]={0, 0, -1, 1}, dy[]={-1, 1, 0, 0};

void destroy(const int x, const int y, bool arr[305][305]){
    arr[x][y] = false;
    for(int i=0; i<4; ++i) arr[x+dx[i]][y+dy[i]] = false;
}

struct Node{
    int x, y, t;
    Node(int xx=0, int yy=0, int tt=0):x(xx),y(yy),t(tt){}
    bool operator <(const Node& r) const {
        return t < r.t;
    }
};

vector<Node> vec;

int bfs(){
    queue<Node> q;
    q.push(Node(1, 1, 0));
    vector<Node>::iterator last = vec.begin();
    vis[1][1] = true;
    while(!q.empty()){
        Node s = q.front();
        q.pop();
        if(safe[s.x][s.y]) return s.t;
        ++s.t;
        vector<Node>::iterator ub = upper_bound(vec.begin(), vec.end(), s);
        for(vector<Node>::iterator it=last; it!=ub; ++it){
            destroy(it->x, it->y, place);
        }
        last = ub;
        for(int i=0; i<4; ++i){
            Node t = s;
            t.x += dx[i];
            t.y += dy[i];
            if(0<t.x && 1<=t.y && place[t.x][t.y] && !vis[t.x][t.y]){
                q.push(t);
                vis[t.x][t.y] = true;
            }
        }
    }
    return -1;
}


int main(){
    // freopen("in.txt", "r", stdin);
    memset(safe, true, sizeof(bool)*305*305);
    memset(place, true, sizeof(bool)*305*305);
    memset(vis, false, sizeof(bool)*305*305);
    int m;
    scanf("%d",&m);
    while(m--){
        int x,y,t;
        scanf("%d%d%d",&x, &y, &t);
        destroy(x+1, y+1, safe);
        vec.push_back(Node(x+1, y+1, t));
    }
    sort(vec.begin(), vec.end());
    printf("%d\n", bfs());
    return 0;
}

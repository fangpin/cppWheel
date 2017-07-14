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

int n, sum;
int b[10];
bool ok;

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d%d",&n, &sum);
    ok = false;
    int a[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    do{
        memcpy(b, a, sizeof(a[0])*n);
        for(int i=n-2; i>=0; --i){
            for(int j=0; j<=i; ++j){
                b[j] += b[j+1];
            }
        }
        if(b[0] == sum){
            ok = true;
            for(int i=0; i<n; ++i){
                printf("%d%c", a[i], i==n-1?'\n':' ');
            }
        }
    } while(next_permutation(a, a+n) && !ok);
    return 0;
}

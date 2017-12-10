#include <string.h>

#define MAX_LEN 1000000

char string[MAX_LEN], part[MAX_LEN];

void fail(char *part, int *failure){
    int len = strlen(part), i;
    if(len) failure[0] = -1;
    for(i=1; i<len; ++i){
        int j = failure[i-1];
        while(part[j+1] != part[i] && (j>=0)) j=failure[j];
        if(part[j+1] == part[i]) failure[i] = j + 1;
        else failure[i] = -1;
    }
}

int KMPmatch(char *str, char *part, int *failure){
    int lens = strlen(str), lenp = strlen(part);
    int ss = 0, ps = 0;
    while(ss < lens && ps < lenp){
        if(str[ss] == part[ps]){
            ++ss;
            ++ps;
        }
        else if(ps == 0){
            ++ss;
        }
        else{
            ps = failure[ps-1] + 1;
        }
    }
    return ps == lenp ? ss - lenp : -1;
}

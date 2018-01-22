#include <stdlib.h>
#include <stdio.h>

typedef int Element;

void
merge(Element data[], Element tmp[], int left, int mid, int right)
{
    int i=0, j=mid+1, pos=0;
    while(i<=mid && j<=right)
    {
        if(data[i] < data[j])
            tmp[pos++] = data[i++];
        else
            tmp[pos++] = data[j++];
    }
    while(i<=mid)
        tmp[pos++] = data[i++];
    while(j<=right)
        tmp[pos++] = data[j++];
    for(i=0; i<pos; ++i)
        data[left + i] = tmp[i];
}


void
_merge_sort(Element data[], Element tmp[], int left, int right)
{
    int mid;
    if(left < right)
    {
        mid = (left + right) / 2;
        _merge_sort(data, tmp, left, mid);
        _merge_sort(data, tmp, mid+1, right);
        merge(data, tmp, left, mid, right);
    }
}

void
merge_sort(Element data[], int n)
{
    Element * tmp = (Element*)malloc(n * sizeof(Element));
    if(!tmp)
    {
        fprintf(stderr, "malloc error.\n");
        exit(1);
    }
    _merge_sort(data, tmp, 0, n-1);
}

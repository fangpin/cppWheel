/* find the  kth smallest element. */
/* after call _quick_select, the kth samllest element will at position k. */
typedef int Element;

#define cutoff (3)


static inline void
swap(Element *a, Element *b)
{
    Element *tmp = a;
    *a = *b;
    *b = *tmp;
}


int
median3(Element a[], int left, int right)
{
    int mid = (left + right) / 2;
    if(a[left] > a[mid])
        swap(&a[left], &a[right]);
    if(a[left] > a[right])
        swap(&a[left], &a[right]);
    if(a[mid] > a[right])
        swap(&a[mid], &a[right]);
    swap(&a[mid], &a[right-1]);
    return a[right-1];
}


void
insertion_sort(Element a[], int left, int right)
{
    int i, j;
    Element tmp;
    for(i=left+1; i<=right; ++i)
    {
        tmp = a[i];
        for(j=i; j>=left && a[j]<a[j-1]; --j)
            a[j] = a[j-1];
        a[j] = tmp;
    }
}


void
_quick_select(Element a[], int k, int left, int right)
{
    if(left + cutoff <= right)
    {
        int pivot = median3(a, left, right);
        int i = left, j = right - 1;
        Element tmp = a[j];
        while(i<j)
        {
            while(a[++i] < pivot);
            while(a[--j] < pivot);
            if(i < j)
                swap(a+i, a+j);
        }
        swap(a + i, &tmp);
        if(k <= i)
            _quick_select(a, k, left, i);
        else if(k > i+1)
            _quick_select(a, k, i+1, right);
    }
    else
        insertion_sort(a, left, right);
}


void
quick_select(Element a[], int n, int k)
{
    _quick_select(a, k, 0, n-1);
}

typedef int Element;
void
insertion_sort(Element *data, int n)
{
    Element tmp;
    int i, j;
    for(i=1; i<n; ++i)
    {
        tmp = data[i];
        for(j=i; j>=0 && data[j]>tmp; --j)
            data[j] = data[j-1];
        data[j] = tmp;
    }
}

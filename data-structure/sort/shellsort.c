typedef int Element;

void
shell_sort(Element data[], int n)
{
    Element i, j, increment, tmp;
    for(increment=n/2; increment>0; --i)
    {
        for(i=increment; i<n; ++i)
        {
            tmp = data[i];
            for(j=i; j>=increment && data[j]<data[j-increment]; j-=increment)
                data[j] = data[j-increment];
            data[j] = tmp;
        }
    }
}

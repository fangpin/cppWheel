typedef int Element;

#define Lson(i) (2*(i)+1)

void
swap(Element *x, Element *y)
{
    Element *tmp = x;
    x = y;
    y = tmp;
}

void
down(Element data[], int root, int n)
{
    int child;
    Element tmp = data[root];
    for(child = Lson(root); child < n; root=child, child=Lson(root))
    {
        if(child!=n-1 && data[child]<data[child+1])
            ++child;
        if(tmp < data[child])
            data[root] = data[child];
        else
            break;
    }
    data[root] = tmp;
}


void
heap_sort(Element data[], int n)
{
    int i;
    for(i=(n-2)/2; i>0; --i)
        down(data, i, n);
    for(i=n-1; i>0; --i)
    {
        swap(data, data+i);
        down(data, 0, n);
    }
}

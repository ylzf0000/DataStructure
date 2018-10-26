int partition(int a[], int low, int high)
{
    if (low > high)
        return -1;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp <= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] <= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    return i;
}

void qsort(int a[], int low, int high)
{
    if (low > high)
        return;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp <= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] <= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    qsort(a, low, i - 1);
    qsort(a, i + 1, high);
}

int kBigNo(int a[], int low, int high, int k)
{
    if (low > high || k < low || k > high)
        return -1;
    int i = low, j = high;
    int tmp = a[i];
    while (i < j)
    {
        while (i < j && tmp >= a[j])
            --j;
        a[i] = a[j];
        while (i < j && a[i] >= tmp)
            ++i;
        a[j] = a[i];
    }
    a[i] = tmp;
    if (i < k)
        return kBigNo(a, i + 1, high, k);
    if (k < i)
        return kBigNo(a, low, i - 1, k);
    return a[i];
}

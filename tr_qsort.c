int tr_cmp_int(int a, int b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int tr_cmp_float(float a, float b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int tr_cmp(int index1, int index2, char *tr_attribute)
{
    if(strcmp(tr_attribute, "transaction_date") == 0)
        return strcmp(tr_s2[index1].transaction_date, tr_s2[index2].transaction_date);

    else if(strcmp(tr_attribute, "item_code") == 0)
        return(tr_cmp_int(tr_s2[index1].item_code, tr_s2[index2].item_code));

    else if(strcmp(tr_attribute, "transaction_id") == 0)
        return(tr_cmp_int(tr_s2[index1].transaction_id, tr_s2[index2].transaction_id));

    else if(strcmp(tr_attribute, "transaction_quantity") == 0)
        return(tr_cmp_int(tr_s2[index1].transaction_quantity, tr_s2[index2].transaction_quantity));

    else if(strcmp(tr_attribute, "total_price") == 0)
        return(tr_cmp_float(tr_s2[index1].total_price, tr_s2[index2].total_price));

}

void tr_swap(int *a, int *b)
{
    int temp;//Error was here.. *temp
    temp = *a;
    *a = *b;
    *b = temp;
}

int tr_part(int *index, int low, int high, char *tr_attribute)
{
    int x;
    int j, i;
    x = index[high];
    i = low - 1;

    for(j = low; j < high; j++)//j = low and not 1
    {
        if(tr_cmp(index[j], x, tr_attribute) <= 0)
        {
            i++;
            tr_swap(&index[i], &index[j]);
        } 
    }
    tr_swap(&index[i + 1], &index[high]);
    return (i + 1);
}


void tr_quicksort(int *index, int low, int high, char *tr_attribute, int depth)
{
    int pivot;
    depth++;
    if(low < high)
    {
        pivot = tr_part(index, low, high, tr_attribute);

        if(depth == 1)
        {
            #pragma omp task firstprivate(high, low, pivot, depth) 
            {
                quicksort(index, low, pivot - 1, tr_attribute, depth);
            }   
            #pragma omp task firstprivate(high, low, pivot)
            {   
                quicksort(index, pivot + 1, high, tr_attribute, depth);
            }
        }

        else
        {
            tr_quicksort(index, low, pivot - 1, tr_attribute, depth);
            tr_quicksort(index, pivot + 1, high, tr_attribute, depth);
        }
    }
}
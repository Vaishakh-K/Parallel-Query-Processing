int cmp_int(int a, int b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int cmp_float(float a, float b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int cmp(int index1, int index2, char *attribute)
{
    if(strcmp(attribute, "item_name") == 0)
        return strcmp(s2[index1].item_name, s2[index2].item_name);

    else if(strcmp(attribute, "item_code") == 0)
        return(cmp_int(s2[index1].item_code, s2[index2].item_code));

    else if(strcmp(attribute, "item_type") == 0)
        return(cmp_int(s2[index1].item_type, s2[index2].item_type));

    else if(strcmp(attribute, "item_quantity") == 0)
        return(cmp_int(s2[index1].item_quantity, s2[index2].item_quantity));

    else if(strcmp(attribute, "item_reorder_level") == 0)
        return(cmp_int(s2[index1].item_reorder_level, s2[index2].item_reorder_level));

    else if(strcmp(attribute, "item_price") == 0)
        return(cmp_float(s2[index1].item_price, s2[index2].item_price));

}

void swap(int *a, int *b)
{
    int temp;//Error was here.. *temp
    temp = *a;
    *a = *b;
    *b = temp;
}

int part(int *index, int low, int high, char *attribute)
{
    int x;
    int j, i;
    x = index[high];
    i = low - 1;

    for(j = low; j < high; j++)//j = low and not 1
    {
        if(cmp(index[j], x, attribute) <= 0)
        {
            i++;
            swap(&index[i], &index[j]);
        } 
    }
    swap(&index[i + 1], &index[high]);
    return (i + 1);
}


void quicksort(int *index, int low, int high, char *attribute, int depth)
{
    int pivot;
    depth++;
    
    if(low < high)
    {
        pivot = part(index, low, high, attribute);
        

        if(depth == 1)
        {
            #pragma omp task firstprivate(high, low, pivot, depth) 
            {
                quicksort(index, low, pivot - 1, attribute, depth);
            }   
            #pragma omp task firstprivate(high, low, pivot)
            {   
                quicksort(index, pivot + 1, high, attribute, depth);
            }
        }

        else
        {
            quicksort(index, low, pivot - 1, attribute, depth);
            quicksort(index, pivot + 1, high, attribute, depth);
        }

    }
}
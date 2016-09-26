int join_cmp_int(int a, int b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int join_cmp_float(float a, float b)
{
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    else
        return 0;
}


int join_cmp(int index1, int index2, char *join_attribute)
{
    if(strcmp(join_attribute, "item_name") == 0)
        return strcmp(join_tb[index1].item_name, join_tb[index2].item_name);

    else if(strcmp(join_attribute, "item_code") == 0)
        return(join_cmp_int(join_tb[index1].item_code, join_tb[index2].item_code));

    else if(strcmp(join_attribute, "item_type") == 0)
        return(join_cmp_int(join_tb[index1].item_type, join_tb[index2].item_type));

    else if(strcmp(join_attribute, "item_quantity") == 0)
        return(join_cmp_int(join_tb[index1].item_quantity, join_tb[index2].item_quantity));

    else if(strcmp(join_attribute, "item_reorder_level") == 0)
        return(join_cmp_int(join_tb[index1].item_reorder_level, join_tb[index2].item_reorder_level));

    else if(strcmp(join_attribute, "item_price") == 0)
        return(join_cmp_float(join_tb[index1].item_price, join_tb[index2].item_price));

    else if(strcmp(join_attribute, "transaction_date") == 0)
        return strcmp(join_tb[index1].transaction_date, join_tb[index2].transaction_date);

    else if(strcmp(join_attribute, "transaction_id") == 0)
        return(join_cmp_int(join_tb[index1].transaction_id, join_tb[index2].transaction_id));

    else if(strcmp(join_attribute, "transaction_quantity") == 0)
        return(join_cmp_int(join_tb[index1].transaction_quantity, join_tb[index2].transaction_quantity));

    else if(strcmp(join_attribute, "total_price") == 0)
        return(join_cmp_float(join_tb[index1].total_price, join_tb[index2].total_price)); 

}

void join_swap(struct combine *a, struct combine *b)
{
    struct combine temp;//Error was here.. *temp
    temp = *a;
    *a = *b;
    *b = temp;
}

int join_part(struct combine *index, int low, int high, char *join_attribute)
{
   	int x;
    int j, i;
    x = high;
    i = low - 1;

    for(j = low; j < high; j++)//j = low and not 1
    {
        if(join_cmp(j, x, join_attribute) <= 0)
        {
            i++;
            join_swap(&index[i], &index[j]);
        } 
    }
    join_swap(&index[i + 1], &index[high]);
    return (i + 1);
}


void join_quicksort(struct combine *index, int low, int high, char *join_attribute, int depth)
{
    int pivot;
    depth++;
    if(low < high)
    {
        pivot = join_part(index, low, high, join_attribute);

        if(depth == 1)
        {
            #pragma omp task firstprivate(high, low, pivot, depth) 
            {
                join_quicksort(index, low, pivot - 1, join_attribute, depth);
            }   
            #pragma omp task firstprivate(high, low, pivot)
            {   
                join_quicksort(index, pivot + 1, high, join_attribute, depth);
            }
        }

        else
        {
            join_quicksort(index, low, pivot - 1, join_attribute, depth);
            join_quicksort(index, pivot + 1, high, join_attribute, depth);
        }

    }
}



void join_giveSum(int low, int high, char join_agg_attribute[20])
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(join_agg_attribute, "transaction_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)
			for (i = low; i < high; i++)
			{
				sum += join_tb[i].transaction_quantity;
			}

		printf("Sum of %s is %d\n", join_agg_attribute, sum);
	}

	else if (strcmp(join_agg_attribute, "total_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)
			for (i = low; i < high; i++)
			{
				sum1 += join_tb[i].total_price;
			}

		printf("Sum of %s is %f\n",join_agg_attribute, sum1);
	}

	else if (strcmp(join_agg_attribute, "item_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)	
			for (i = low; i < high; i++)
			{
				sum += join_tb[i].item_quantity;
			}

		printf("Sum of %s is %d\n", join_agg_attribute, sum);
	}

	else if (strcmp(join_agg_attribute, "item_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)	
			for (i = low; i < high; i++)
			{
				sum1 += join_tb[i].item_price;
			}

		printf("Sum of %s is %f\n", join_agg_attribute, sum1);
	}
}

void join_giveMax(int low, int high, char join_agg_attribute[20])
{
	int i, max_val;
	float max_val1;



	if (strcmp(join_agg_attribute, "transaction_quantity") == 0)
	{
		max_val = join_tb[0].transaction_quantity;
		#pragma omp parallel for reduction(max:max_val)
			for (i = low; i < high; i++)
			{
				if (max_val < join_tb[i].transaction_quantity)
					max_val = join_tb[i].transaction_quantity;
			}

		printf("Maximum of %s is %d\n", join_agg_attribute, max_val);
	}

	else if (strcmp(join_agg_attribute, "total_price") == 0)
	{
		max_val1 = join_tb[tr_relevant_records[0]].total_price;
		#pragma omp parallel for reduction(max:max_val1)
			for (i = low; i < high; i++)
			{
				if (max_val1 < join_tb[i].total_price)
					max_val1 = join_tb[i].total_price;
			}

		printf("Maximum of %s is %f\n", join_agg_attribute, max_val1);
	}

	else if (strcmp(join_agg_attribute, "item_quantity") == 0)
	{
		max_val = join_tb[relevant_records[0]].item_quantity;
		#pragma omp parallel for reduction(max:max_val)	
			for (i = low; i < high; i++)
			{
				if (max_val < join_tb[i].item_quantity)
					max_val = join_tb[i].item_quantity;
			}

		printf("Maximum of %s is %d\n", join_agg_attribute, max_val);	
	}

	else if (strcmp(join_agg_attribute, "item_price") == 0)
	{
		max_val1 = join_tb[relevant_records[0]].item_price;
		#pragma omp parallel for reduction(max:max_val1)	
			for (i = low; i < high; i++)
			{
				if (max_val1 < join_tb[i].item_price)
					max_val1 = join_tb[i].item_price;
			}

		printf("Maximum of %s is %f\n", join_agg_attribute, max_val1);
	}

}

void join_giveMin(int low, int high, char join_agg_attribute[20])
{
	int i, min_val;
	float min_val1;


	if (strcmp(join_agg_attribute, "transaction_quantity") == 0)
	{
		min_val = join_tb[0].transaction_quantity;
		#pragma omp parallel for reduction(min:min_val)
			for (i = low; i < high; i++)
			{
				if (min_val > join_tb[i].transaction_quantity)
					min_val = join_tb[i].transaction_quantity;
			}

		printf("Minimum of %s is %d\n", join_agg_attribute, min_val);
	}

	else if (strcmp(join_agg_attribute, "total_price") == 0)
	{
		min_val1 = join_tb[0].total_price;
		#pragma omp parallel for reduction(min:min_val1)
			for (i = low; i < high; i++)
			{
				if (min_val1 > join_tb[i].total_price)
					min_val1 = join_tb[i].total_price;
			}

		printf("Minimum of %s is %f\n", join_agg_attribute, min_val1);
	}

	else if (strcmp(join_agg_attribute, "item_quantity") == 0)
	{
		min_val = join_tb[relevant_records[0]].item_quantity;
		#pragma omp parallel for reduction(min:min_val)	
			for (i = low; i < high; i++)
			{
				if (min_val > join_tb[i].item_quantity)
					min_val = join_tb[i].item_quantity;
			}

		printf("Minimum of %s is %d\n", join_agg_attribute, min_val);	
	}

	else if (strcmp(join_agg_attribute, "item_price") == 0)
	{
		min_val1 = join_tb[relevant_records[0]].item_price;
		#pragma omp parallel for reduction(min:min_val1)	
			for (i = low; i < high; i++)
			{
				if (min_val1 > join_tb[i].item_price)
					min_val1 = join_tb[i].item_price;
			}

		printf("Minimum of %s is %f\n", join_agg_attribute, min_val1);
	}
}

void join_giveAverage(int low, int high, char join_agg_attribute[20])//Average of item_quantity should be integer
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(join_agg_attribute, "transaction_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)
			for (i = low; i < high; i++)
			{
				sum += join_tb[i].transaction_quantity;
			}

		printf("Average of %s is %f\n", join_agg_attribute, (float)sum / no);
	}

	else if (strcmp(join_agg_attribute, "total_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)
			for (i = low; i < high; i++)
			{
				sum1 += join_tb[i].total_price;
			}

		printf("Average of %s is %f\n", join_agg_attribute, (float)sum1 / no);
	}

	else if (strcmp(join_agg_attribute, "item_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)	
			for (i = low; i < high; i++)
			{
				sum += join_tb[i].item_quantity;
			}

		printf("Average of %s is %d\n", join_agg_attribute, sum / no);
	}

	else if (strcmp(join_agg_attribute, "item_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)	
			for (i = low; i < high; i++)
			{
				sum1 += join_tb[i].item_price;
			}

		printf("Average of %s is %f\n", join_agg_attribute, (float)sum1 / no);
	}

}


void join_callAggregate(int i)
{
        if(strcmp(join_aggr[i].agg_func, "sum") == 0 )
        {
            join_giveSum(0, no, join_aggr[i].agg_attribute);
        }
        else if(strcmp(join_aggr[i].agg_func, "avg") == 0)
        {
            join_giveAverage(0, no, join_aggr[i].agg_attribute);
        }
        else if (strcmp(join_aggr[i].agg_func, "min") == 0)
        {
            join_giveMin(0, no, join_aggr[i].agg_attribute);
        }
        else if( strcmp(join_aggr[i].agg_func, "max") == 0)
        {
            join_giveMax(0, no, join_aggr[i].agg_attribute);
        }
      /*  else if(strcmp(aggr[i].agg_func, "distinct") == 0)
        {
            strcpy(join_attribute, aggr[i].agg_attribute);
            printf("%sattribute\n",join_attribute);
            groupby_flag = 1;
            
        }*/
       /* else if(strcmp(agg_func, "count") == 0)
        {
            giveCount(agg_attribute);
        }*/
}

void join_callAggregateGroupBy(int low, int high, int i)
{
        if(strcmp(join_aggr[i].agg_func, "sum") == 0 )
        {
            join_giveSum(low, high, join_aggr[i].agg_attribute);
        }
        else if(strcmp(join_aggr[i].agg_func, "avg") == 0)
        {
            join_giveAverage(low, high, join_aggr[i].agg_attribute);
        }
        else if (strcmp(join_aggr[i].agg_func, "min") == 0)
        {
            join_giveMin(low, high, join_aggr[i].agg_attribute);
        }
        else if( strcmp(join_aggr[i].agg_func, "max") == 0)
        {
            join_giveMax(low, high, join_aggr[i].agg_attribute);
        }
        
}

void join_parseAggregate()
{
    int i;
    char * fob, * fcb;
    int agg_func_len;
    int att_len, llen;

    for (i = 0; i < join_aggregate_list_count; i++)
    { 
        // printf("%s\n", aggregate_list[i]); 
        join_aggr[i].agg_func[0] = '\0';
        join_aggr[i].agg_attribute[0] = '\0'; 
        fob = strchr(join_aggregate_list[i], '(');
        fcb = strchr(join_aggregate_list[i], ')');
        att_len = strlen(fob);
        agg_func_len = strlen(join_aggregate_list[i]) - att_len;
        strncpy(join_aggr[i].agg_func, join_aggregate_list[i], agg_func_len);
        join_aggr[i].agg_func[agg_func_len] = '\0';
        /*strncpy(agg_attribute , fob + 1, att_len - 1);
        agg_attribute[att_len - 1] = '\0';*/
        llen = strlen(fcb);
        strncpy(join_aggr[i].agg_attribute , fob + 1, att_len - llen - 1);
        join_aggr[i].agg_attribute[att_len - llen - 1] = '\0';
        // printf("%s %s\n", agg_func, agg_attribute);
        if (strcmp(join_aggr[i].agg_func, "distinct") == 0)
        {
            strcpy(join_attribute, join_aggr[i].agg_attribute);
            groupby_flag = 1;
            join_quicksort(join_tb, 0, no - 1, join_aggr[i].agg_attribute, 0);
        }
        
    }
    
}


void join_orderby(int order_seq)
{
    int i;
    printf("\nEnter the column to order by : ");
    scanf("%s", join_attribute);
    join_quicksort(join_tb, 0, no - 1, join_attribute, 0);

}


void join_groupby()
{

    int i;
    printf("\nEnter the column to group by : ");
    scanf("%s", join_attribute);
    join_quicksort(join_tb, 0, no - 1, join_attribute, 0);
    join_groupby_flag = 1;
    
}


void join_groupByDisplayCount()
{
    int i, j, ct = 1;
        
    if (strcmp(join_attribute,"item_code") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].item_code != join_tb[i + 1].item_code)
            { 
                printf("%d\t\t%d\t\t", join_tb[i].item_code, ct);
                for (j = 0; j < join_aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
           
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"transaction_date") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (strcmp(join_tb[i].transaction_date, join_tb[i + 1].transaction_date) != 0)
            {
                printf("%s\t\t%d\t\t", join_tb[i].transaction_date, ct);
                for (j = 0; j < join_aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"transaction_quantity") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].transaction_quantity != join_tb[i + 1].transaction_quantity)
            {
                printf("%d\t\t%d\t\t", join_tb[i].transaction_quantity, ct);
                for (j = 0; j < join_aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(join_attribute, "total_price") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].total_price != join_tb[i + 1].total_price)
            {
                //low = i + 1 - ct, high = i + 1 aggregate

                printf("%f\t\t%d\t\t", join_tb[i].total_price, ct);
                for (j = 0; j < join_aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"transaction_id") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].transaction_id != join_tb[i + 1].transaction_id)
            {
                //low = i + 1 - ct, high = i + 1 aggregate
                printf("%d\t\t%d\t\t", join_tb[i].transaction_id, ct);
                for (j = 0; j < join_aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }  
    
    if (strcmp(join_attribute,"item_name") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (strcmp(join_tb[i].item_name, join_tb[i + 1].item_name) != 0)
            {
                printf("%s\t\t%d\t\t", join_tb[i].item_name, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }

                
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"item_type") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].item_type != join_tb[i + 1].item_type)
            {
                printf("%d\t\t%d\t\t", join_tb[i].item_type, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"item_price") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].item_price != join_tb[i + 1].item_price)
            {
                //low = i + 1 - ct, high = i + 1 aggregate

                printf("%f\t\t%d\t\t", join_tb[i].item_price, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"item_quantity") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].item_quantity != join_tb[i + 1].item_quantity)
            {
                //low = i + 1 - ct, high = i + 1 aggregate
                printf("%d\t\t%d\t\t", join_tb[i].item_quantity, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }

    if (strcmp(join_attribute,"item_reorder_level") == 0)
    {
        printf("%s\tCount\n", join_attribute);

        for (i = 0; i < no; i++)
        {
            if (join_tb[i].item_reorder_level != join_tb[i + 1].item_reorder_level)
            {
                printf("%d\t\t%d\t\t", join_tb[i].item_reorder_level, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    join_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }      
}

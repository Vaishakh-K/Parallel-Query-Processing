void join_groupby()
{
    char join[25]; // join attribut variable should be made global//
    int i;
    printf("\nEnter the column to group by : ");
    scanf("%s", join_attribute);
    join_quicksort(join_tb, 0, no-1, join_attribute);
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
                printf("%s\t\t%d\t\t", join_join_tb[i].transaction_date, ct);
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

void groupByDisplayCount()
{
    int i, j, ct = 1;
        
    if (strcmp(attribute,"item_code") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (s2[relevant_records[i]].item_code != s2[relevant_records[i + 1]].item_code)
            { 
                printf("%d\t\t%d\t\t", s2[relevant_records[i]].item_code, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
           
            else
                ct++;
        }
    }

    if (strcmp(attribute,"item_name") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (strcmp(s2[relevant_records[i]].item_name, s2[relevant_records[i + 1]].item_name) != 0)
            {
                printf("%s\t\t%d\t\t", s2[relevant_records[i]].item_name, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }

                
            else
                ct++;
        }
    }

    if (strcmp(attribute,"item_type") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (s2[relevant_records[i]].item_type != s2[relevant_records[i + 1]].item_type)
            {
                printf("%d\t\t%d\t\t", s2[relevant_records[i]].item_type, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(attribute,"item_price") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (s2[relevant_records[i]].item_price != s2[relevant_records[i + 1]].item_price)
            {
                //low = i + 1 - ct, high = i + 1 aggregate

                printf("%f\t\t%d\t\t", s2[relevant_records[i]].item_price, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(attribute,"item_quantity") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (s2[relevant_records[i]].item_quantity != s2[relevant_records[i + 1]].item_quantity)
            {
                //low = i + 1 - ct, high = i + 1 aggregate
                printf("%d\t\t%d\t\t", s2[relevant_records[i]].item_quantity, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }

    if (strcmp(attribute,"item_reorder_level") == 0)
    {
        printf("%s\tCount\n", attribute);

        for (i = 0; i < relevant_records_count; i++)
        {
            if (s2[relevant_records[i]].item_reorder_level != s2[relevant_records[i + 1]].item_reorder_level)
            {
                printf("%d\t\t%d\t\t", s2[relevant_records[i]].item_reorder_level, ct);
                for (j = 0; j < aggregate_list_count; j++)
                    callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }      
         
}

void printRelevantRecords()
{
    int i;
    printf("\nThere are %d relevant records\n", relevant_records_count);

    for (i = 0; i < aggregate_list_count; i++)
    {
        callAggregate(i);
    }

    for (i = 1; i <= 6; i++)
    {
        if (sel_item_tab[i].item_attribute_flag == 1)
        {
            printf("%s\t", sel_item_tab[i].item_attribute);
        }
    }
    printf("\n");
    for (i = 0; i < relevant_records_count; i++)
    {
        //printf("%d\n", relevant_records[i]);
        if (sel_item_tab[1].item_attribute_flag == 1)
        {
            printf("%d\t\t", s2[relevant_records[i]].item_code);
        }
        
        if (sel_item_tab[2].item_attribute_flag == 1)
        {
            printf("%s\t\t", s2[relevant_records[i]].item_name);
        }
    
        if (sel_item_tab[3].item_attribute_flag == 1)
        {
            printf("%d\t\t", s2[relevant_records[i]].item_type);
        }
        
        if (sel_item_tab[4].item_attribute_flag == 1)
        {
            printf("%d\t\t", s2[relevant_records[i]].item_quantity);
        }
    
        if (sel_item_tab[5].item_attribute_flag == 1)
        {
            printf("%f\t\t", s2[relevant_records[i]].item_price);
        }
        
        if (sel_item_tab[6].item_attribute_flag == 1)
        {
            printf("%d\t\t", s2[relevant_records[i]].item_reorder_level);
        }
        
        printf("\n");
        // printf("%d \t%d \t%d \t%f \t%s\n", s2[relevant_records[i]].item_code, s2[relevant_records[i]].item_type, s2[relevant_records[i]].item_quantity, s2[relevant_records[i]].item_price, s2[relevant_records[i]].item_name);
    }    
}
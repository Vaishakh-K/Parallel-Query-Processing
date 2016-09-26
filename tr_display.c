void tr_groupByDisplayCount()
{
    int i, j, ct = 1;
        
    if (strcmp(tr_attribute,"item_code") == 0)
    {
        printf("%s\tCount\n", tr_attribute);

        for (i = 0; i < tr_relevant_records_count; i++)
        {
            if (tr_s2[tr_relevant_records[i]].item_code != tr_s2[tr_relevant_records[i + 1]].item_code)
            { 
                printf("%d\t\t%d\t\t", tr_s2[tr_relevant_records[i]].item_code, ct);
                for (j = 0; j < tr_aggregate_list_count; j++)
                    tr_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
           
            else
                ct++;
        }
    }

    if (strcmp(tr_attribute,"transaction_date") == 0)
    {
        printf("%s\tCount\n", tr_attribute);

        for (i = 0; i < tr_relevant_records_count; i++)
        {
            if (strcmp(tr_s2[tr_relevant_records[i]].transaction_date, tr_s2[tr_relevant_records[i + 1]].transaction_date) != 0)
            {
                printf("%s\t\t%d\t\t", tr_s2[tr_relevant_records[i]].transaction_date, ct);
                for (j = 0; j < tr_aggregate_list_count; j++)
                    tr_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }

    if (strcmp(tr_attribute,"transaction_quantity") == 0)
    {
        printf("%s\tCount\n", tr_attribute);

        for (i = 0; i < tr_relevant_records_count; i++)
        {
            if (tr_s2[tr_relevant_records[i]].transaction_quantity != tr_s2[tr_relevant_records[i + 1]].transaction_quantity)
            {
                printf("%d\t\t%d\t\t", tr_s2[tr_relevant_records[i]].transaction_quantity, ct);
                for (j = 0; j < tr_aggregate_list_count; j++)
                    tr_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(tr_attribute, "total_price") == 0)
    {
        printf("%s\tCount\n", tr_attribute);

        for (i = 0; i < tr_relevant_records_count; i++)
        {
            if (tr_s2[tr_relevant_records[i]].total_price != tr_s2[tr_relevant_records[i + 1]].total_price)
            {
                //low = i + 1 - ct, high = i + 1 aggregate

                printf("%f\t\t%d\t\t", tr_s2[tr_relevant_records[i]].total_price, ct);
                for (j = 0; j < tr_aggregate_list_count; j++)
                    tr_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
            
            else
                ct++;
        }
    }

    if (strcmp(tr_attribute,"transaction_id") == 0)
    {
        printf("%s\tCount\n", tr_attribute);

        for (i = 0; i < tr_relevant_records_count; i++)
        {
            if (tr_s2[tr_relevant_records[i]].transaction_id != tr_s2[tr_relevant_records[i + 1]].transaction_id)
            {
                //low = i + 1 - ct, high = i + 1 aggregate
                printf("%d\t\t%d\t\t", tr_s2[tr_relevant_records[i]].transaction_id, ct);
                for (j = 0; j < tr_aggregate_list_count; j++)
                    tr_callAggregateGroupBy(i + 1 - ct, i + 1, j);
                ct = 1;
                printf("\n");
            }
                
            else
                ct++;
        }
    }          
}

void tr_printRelevantRecords()
{
    int i;
    printf("\nThere are %d relevant records\n", tr_relevant_records_count);

    for (i = 0; i < tr_aggregate_list_count; i++)
    {
        tr_callAggregate(i);
    }

    for (i = 1; i <= 6; i++)
    {
        if (sel_trans_tab[i].trans_attribute_flag == 1)
        {
            printf("%s\t", sel_trans_tab[i].trans_attribute);
        }
    }
    printf("\n");
    for (i = 0; i < tr_relevant_records_count; i++)
    {
        //printf("%d\n", relevant_records[i]);
        if (sel_trans_tab[1].trans_attribute_flag == 1)
        {
            printf("%d\t\t", tr_s2[tr_relevant_records[i]].transaction_id);
        }
        if (sel_trans_tab[2].trans_attribute_flag == 1)
        {
            printf("%d\t\t", tr_s2[tr_relevant_records[i]].item_code);
        }
        if (sel_trans_tab[3].trans_attribute_flag == 1)
        {
            printf("%d\t\t\t", tr_s2[tr_relevant_records[i]].transaction_quantity);
        }
        
        if (sel_trans_tab[4].trans_attribute_flag == 1)
        {
            printf("%f\t\t", tr_s2[tr_relevant_records[i]].total_price);
        }
    
        if (sel_trans_tab[5].trans_attribute_flag == 1)
        {
            printf("%s\t\t", tr_s2[tr_relevant_records[i]].transaction_date);
        }

        printf("\n");
        // printf("%d \t%d \t%d \t%f \t%s\n", tr_s2[tr_relevant_records[i]].item_code, tr_s2[tr_relevant_records[i]].item_type, tr_s2[tr_relevant_records[i]].item_quantity, tr_s2[tr_relevant_records[i]].item_price, tr_s2[tr_relevant_records[i]].item_name);
    }    
}
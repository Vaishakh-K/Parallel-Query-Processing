void joinTablesSelect()
{ 
    int join_count = 0;
    int tr_tab_ind, it_tab_ind = 0;
    no = 0;
    int done = 0;
    printf("rc %d trc %d\n", relevant_records_count, tr_relevant_records_count);
    #pragma omp parallel for private(it_tab_ind)
    for (tr_tab_ind = 0; tr_tab_ind < tr_relevant_records_count; tr_tab_ind++)
    { 
        for (it_tab_ind = 0; it_tab_ind < relevant_records_count; it_tab_ind++)

        if (tr_s2[tr_relevant_records[tr_tab_ind]].item_code == s2[relevant_records[it_tab_ind]].item_code)
        {
            join_tb[no].slno = no;
            join_tb[no].item_code = s2[relevant_records[it_tab_ind]].item_code ;
            strcpy(join_tb[no].item_name, s2[relevant_records[it_tab_ind]].item_name) ;
            join_tb[no].item_type = s2[relevant_records[it_tab_ind]].item_type ;
 			join_tb[no].item_quantity = s2[relevant_records[it_tab_ind]].item_quantity;
			join_tb[no].item_price = s2[relevant_records[it_tab_ind]].item_price;
			join_tb[no].item_reorder_level = s2[relevant_records[it_tab_ind]].item_reorder_level; 
	        
            join_tb[no].transaction_id = tr_s2[tr_relevant_records[tr_tab_ind]].transaction_id;
			join_tb[no].transaction_quantity = tr_s2[tr_relevant_records[tr_tab_ind]].transaction_quantity;
	        join_tb[no].total_price = tr_s2[tr_relevant_records[tr_tab_ind]].total_price;
            strcpy(join_tb[no].transaction_date , tr_s2[tr_relevant_records[tr_tab_ind]].transaction_date );
            #pragma omp atomic
                no++ ;
            break;
        }

        /*if (done)
        {
            break;
        }*/
    }
    printf("no %d\n", no);
} //Problem was not using relevent_records


void joinTablesDelete()
{ 
    int join_count = 0;
    int tr_tab_ind, it_tab_ind = 0;
    delcount = 0;
    int done = 0;
    quicksort(relevant_records, 0, relevant_records_count - 1, "item_code", 0);
    tr_quicksort(tr_relevant_records, 0, tr_relevant_records_count - 1, "item_code", 0); 
    printf("rc %d trc %d\n", relevant_records_count, tr_relevant_records_count);

    if (delete_flag == 0)
    {
        #pragma omp parallel for private(it_tab_ind)
        for (tr_tab_ind = 0; tr_tab_ind < tr_relevant_records_count; tr_tab_ind++)
        { 
            for (it_tab_ind = 0; it_tab_ind < relevant_records_count; it_tab_ind++)
            if (tr_s2[tr_relevant_records[tr_tab_ind]].item_code == s2[relevant_records[it_tab_ind]].item_code)
            {
                join_delete[delcount] =  s2[relevant_records[it_tab_ind]].slno;
                #pragma omp atomic
                delcount++ ;
                break;
            }

        }
    }
    

    else 
    {
        #pragma omp parallel for private(it_tab_ind)
        for (tr_tab_ind = 0; tr_tab_ind < tr_relevant_records_count; tr_tab_ind++)
        { 
            for (it_tab_ind = 0; it_tab_ind < relevant_records_count; it_tab_ind++)
            if (tr_s2[tr_relevant_records[tr_tab_ind]].item_code == s2[relevant_records[it_tab_ind]].item_code)
            {
                join_delete[delcount] =  tr_s2[tr_relevant_records[tr_tab_ind]].slno;
                #pragma omp atomic
                delcount++ ;
                break;
            }

        }
    }
    printf("delcount %d\n", delcount);
} //Problem was not using relevent_records


void joinTablesUpdate()
{ 
    int join_count = 0;
    int tr_tab_ind, it_tab_ind = 0;
    updcount = 0;
    int done = 0;
    printf("rc %d trc %d\n", relevant_records_count, tr_relevant_records_count);

    if (update_flag == 0)
    {
        #pragma omp parallel for private(it_tab_ind)
        for (tr_tab_ind = 0; tr_tab_ind < tr_relevant_records_count; tr_tab_ind++)
        { 
            for (it_tab_ind = 0; it_tab_ind < relevant_records_count; it_tab_ind++)
            if (tr_s2[tr_relevant_records[tr_tab_ind]].item_code == s2[relevant_records[it_tab_ind]].item_code)
            {
                join_update[updcount] =  s2[relevant_records[it_tab_ind]].slno;
                #pragma omp atomic
                updcount++ ;
                break;
            }

        }
    }
    

    else 
    {
        #pragma omp parallel for private(it_tab_ind)
        for (tr_tab_ind = 0; tr_tab_ind < tr_relevant_records_count; tr_tab_ind++)
        { 
            for (it_tab_ind = 0; it_tab_ind < relevant_records_count; it_tab_ind++)
            if (tr_s2[tr_relevant_records[tr_tab_ind]].item_code == s2[relevant_records[it_tab_ind]].item_code)
            {
                join_update[updcount] =  tr_s2[tr_relevant_records[tr_tab_ind]].slno;
                #pragma omp atomic
                updcount++ ;
                break;
            }
        }
    }
    printf("updcount %d\n", updcount);
} //Problem was not using relevent_records


 

 

void printJoin()
{
    int i;
    printf("\nThere are %d relevant records\n", no);

    for (i = 0; i < join_aggregate_list_count; i++)
    {
        join_callAggregate(i);
    }

    if (sel_item_tab[1].item_attribute_flag == 1 || sel_trans_tab[2].trans_attribute_flag == 1)//for item_code
    {
        printf("%s\t", sel_item_tab[1].item_attribute);
    }
    for (i = 2; i <= 6; i++)
    {
        if (sel_item_tab[i].item_attribute_flag == 1)
        {
            printf("%s\t", sel_item_tab[i].item_attribute);
        }
    }
    for (i = 1; i <= 5; i++)
    {
        if (i == 2)
        {
            continue;
        }
        if (sel_trans_tab[i].trans_attribute_flag == 1)
        {
            printf("%s\t", sel_trans_tab[i].trans_attribute);
        }
    }
    printf("\n");

    for (i = 0; i < no; i++)
    {
        //printf("%d\n", relevant_records[i]);
        if (sel_item_tab[1].item_attribute_flag == 1 || sel_trans_tab[2].trans_attribute_flag == 1)
        {
            printf("%d\t\t", join_tb[i].item_code);
        }
        
        if (sel_item_tab[2].item_attribute_flag == 1)
        {
            printf("%s\t\t", join_tb[i].item_name);
        }
    
        if (sel_item_tab[3].item_attribute_flag == 1)
        {
            printf("%d\t\t", join_tb[i].item_type);
        }
        
        if (sel_item_tab[4].item_attribute_flag == 1)
        {
            printf("%d\t\t", join_tb[i].item_quantity);
        }
    
        if (sel_item_tab[5].item_attribute_flag == 1)
        {
            printf("%f\t\t", join_tb[i].item_price);
        }
        
        if (sel_item_tab[6].item_attribute_flag == 1)
        {
            printf("%d\t\t", join_tb[i].item_reorder_level);
        }

        if (sel_trans_tab[1].trans_attribute_flag == 1)
        {
            printf("%d\t\t", join_tb[i].transaction_id);
        }
        
        if (sel_trans_tab[3].trans_attribute_flag == 1)
        {
            printf("%d\t\t\t", join_tb[i].transaction_quantity);
        }
        
        if (sel_trans_tab[4].trans_attribute_flag == 1)
        {
            printf("%f\t\t", join_tb[i].total_price);
        }
    
        if (sel_trans_tab[5].trans_attribute_flag == 1)
        {
            printf("%s\t\t", join_tb[i].transaction_date);
        }
        
        printf("\n");
        // printf("%d \t%d \t%d \t%f \t%s\n", s2[relevant_records[i]].item_code, s2[relevant_records[i]].item_type, s2[relevant_records[i]].item_quantity, s2[relevant_records[i]].item_price, s2[relevant_records[i]].item_name);
    }    

}
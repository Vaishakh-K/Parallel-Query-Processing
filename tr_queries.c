void tr_get_relevant_records(int no_of_records)
{
    int i, n_of_cond;

    for (i = 0; i < no_of_records; i++)
    {
        tr_s2[i].isvalid_record = 1;
    }
gettimeofday(&TimeValue_Start, NULL);
    #pragma omp parallel for if (no_of_records > PC)
    for (i = 0; i < no_of_records; i++)
    {
        if (tr_s2[i].isAlive)
        {
            if (tr_item_code_flag == 1 && tr_s2[i].isvalid_record)
            {
                if (!check_condition_int_type(tr_s2[i].item_code, tr_item_code_op, tr_item_code_check, tr_item_code_check_count))
                {
                    tr_s2[i].isvalid_record = 0;
                }

            }

            if (tr_date_flag == 1 && tr_s2[i].isvalid_record)
            {
                if (!check_condition_string_type(tr_s2[i].transaction_date, tr_date_op , tr_date_check, tr_date_check_count))
                {
                    tr_s2[i].isvalid_record = 0;
                }

            }

            if (tr_quantity_flag == 1 && tr_s2[i].isvalid_record)
            {
                if (!check_condition_int_type(tr_s2[i].transaction_quantity, tr_quantity_op, tr_quantity_check, tr_quantity_check_count))
                {
                    tr_s2[i].isvalid_record = 0;
                }

            }

            if (tr_id_flag == 1 && tr_s2[i].isvalid_record)
            {
                if (!check_condition_int_type(tr_s2[i].transaction_id, tr_id_op, tr_id_check, tr_id_check_count))
                {
                    tr_s2[i].isvalid_record = 0;
                }

            }

            if (tr_price_flag == 1 && tr_s2[i].isvalid_record)
            {
                if (!check_condition_float_type(tr_s2[i].total_price, tr_price_op, tr_price_check, tr_price_check_count))
                {
                    tr_s2[i].isvalid_record = 0;
                }

            }

            //printf("troutside %d\n", i);
            if (tr_s2[i].isvalid_record)
            {  
                //printf("trinside %d\n", i); 
                //#pragma omp critical
                tr_relevant_records[tr_relevant_records_count++] = i;
            }
        }

    }
    gettimeofday(&TimeValue_Final, NULL);
    calcTime();
}

void tr_orderby(int order_seq)
{
    int i;
    printf("\nEnter the column to order by : ");
    scanf("%s", tr_attribute);
    tr_quicksort(tr_relevant_records, 0, tr_relevant_records_count - 1, tr_attribute, 0);

}


void tr_groupby()
{

    int i;
    printf("\nEnter the column to group by : ");
    scanf("%s", tr_attribute);
    tr_quicksort(tr_relevant_records, 0, tr_relevant_records_count - 1, tr_attribute, 0);
    tr_groupby_flag = 1;

}
void tr_select_func(int no_of_records)
{
    int order_option;
    printf("Enter the colums to select\n");
    //tr_setSelectFlags();
    tr_get_relevant_records(no_of_records);
    printf("\n0 - NO CONSTRAINTS\n1 - ORDER BY ASCENDING\n2 - ORDER BY DESCENDING\n3 - GROUP BY\n");
    scanf("%d", &order_option);
    switch( order_option )
    {
        case 1: tr_orderby(1);
                break;
        case 2: tr_orderby(2);
                break;
        case 3: tr_groupby();
                break;
    }



}

void tr_update_func(int no_of_records, int * update_records, int update_records_count)
{
    int set_no_columns, i;
    char set_columns[100], condition[100];
    printf("\nNumber of columns to be Updated \n");
    scanf("%d",&set_no_columns);
    getchar();
    for (i = 0; i < set_no_columns; i++)
    {
        fgets(set_columns, 100, stdin);
        //puts(condition);
        tr_set_parse(set_columns);
    }
    // tr_get_relevant_records(tr_no_of_records);

    #pragma omp parallel for if(update_records_count > PC)
    for(i = 0; i < update_records_count; i++)
    {
        if(set_tr_item_code_flag)
        {
            tr_s2[update_records[i]].item_code = set_tr_item_code_check;
        }

        if(set_tr_date_flag)
        {
            strcpy(tr_s2[update_records[i]].transaction_date, set_tr_date_check);
        }

        if(set_tr_price_flag)
        {
            tr_s2[update_records[i]].total_price = set_tr_price_check;
        }

        if(set_tr_quantity_flag)
        {
            tr_s2[update_records[i]].transaction_quantity = set_tr_quantity_check;
        }

    }
}

void tr_delete_func(int no_of_records, int * delete_records, int delete_records_count)
{
    int i, record_id;
    //tr_get_relevant_records(no_of_records);
    tr_start_queue = tr_end_queue = 0;
    //printf("faux %d\n", emptyAuxillaryArr(auxillary_arr, max_auxillary_arr));

    if((tr_emptyAuxillaryArr(tr_auxillary_arr, tr_max_auxillary_arr) > delete_records_count))
    {
        //Add to queue
        //#pragma omp parallel for if(delete_records_count > PC)
        for (i = 0; i < delete_records_count; i++)
        {
            record_id = delete_records[i];
            tr_s2[record_id].isAlive = 0;
            tr_end_queue = (tr_end_queue + 1) % tr_max_auxillary_arr;
            tr_auxillary_arr[tr_end_queue] = record_id;

        }
    }
    else
    {
        //Rearrange
        for (i = 0; i < delete_records_count; i++)
        {
            record_id = delete_records[i];
            tr_s2[record_id].isAlive = 0;
        }


        int valid_record_pointer = tr_no_of_records - 1;
        i = 0;

        while (i < valid_record_pointer)
        {
            if(tr_s2[i].isvalid_record && !tr_s2[valid_record_pointer].isvalid_record)
            {
                i++;
                valid_record_pointer--;
            }
            else if(!tr_s2[i].isvalid_record && !tr_s2[valid_record_pointer].isvalid_record)
            {
                valid_record_pointer--;
            }
            else if(tr_s2[i].isvalid_record && tr_s2[valid_record_pointer].isvalid_record)
                i++;
            else
            {
                tr_s2[i] = tr_s2[valid_record_pointer];
                tr_s2[i].slno = i;
                tr_s2[valid_record_pointer].isAlive = 0;
                i++;
                valid_record_pointer--;
            }
        }
        tr_no_of_records = valid_record_pointer + 1;
    }

}

/*int reorderTrigger(int item_quantity)
{
    return 0.2 * item_quantity;
}*/

void tr_insert_func()
{
    if( tr_start_queue == tr_end_queue )
    {
        tr_s2[tr_no_of_records].slno = tr_no_of_records;
        printf("Enter the transaction ID:");
        scanf("%d", &tr_s2[tr_no_of_records].transaction_id);
        printf("Enter the item code:");
        scanf("%d", &tr_s2[tr_no_of_records].item_code);//should be automatic
        printf("Enter the transaction date:");
        scanf("%s", tr_s2[tr_no_of_records].transaction_date);
        printf("Enter the transaction quantity:");
        scanf("%d", &tr_s2[tr_no_of_records].transaction_quantity);
        printf("Enter the total price:");
        scanf("%f", &tr_s2[tr_no_of_records].total_price);
        // tr_s2[no_of_records].item_reorder_level = reorderTrigger(tr_s2[no_of_records].item_quantity);
        tr_s2[tr_no_of_records].isAlive = 1;
        tr_no_of_records++ ;
    }
    else
    {
        tr_s2[tr_no_of_records + 1].slno = tr_start_queue + 1;
        printf("Enter the transaction ID:");
        scanf("%d", &tr_s2[tr_auxillary_arr[tr_start_queue + 1]].transaction_id);
        printf("Enter the item code:");
        scanf("%d", &tr_s2[tr_auxillary_arr[tr_start_queue + 1]].item_code);//should be automatic
        printf("Enter the transaction date:");
        scanf("%s", tr_s2[tr_auxillary_arr[tr_start_queue + 1]].transaction_date);
        printf("Enter the transaction quantity:");
        scanf("%d", &tr_s2[tr_auxillary_arr[tr_start_queue + 1]].transaction_quantity);
        printf("Enter the total price:");
        scanf("%f", &tr_s2[tr_auxillary_arr[tr_start_queue + 1]].total_price);
        //tr_s2[start_queue + 1].item_reorder_level = reorderTrigger(tr_s2[start_queue + 1].item_quantity);
        tr_s2[tr_no_of_records + 1].isAlive = 1;
        tr_start_queue++ ;

    }
}
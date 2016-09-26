void get_relevant_records(int no_of_records)
{
    int i, n_of_cond;

    for (i = 0; i < no_of_records; i++)
    {
        s2[i].isvalid_record = 1;
    }

    //gettimeofday(&TimeValue_Start, NULL);
    #pragma omp parallel for
    for (i = 0; i < no_of_records; i++)
    {
        if (s2[i].isAlive)
        {
            if (item_code_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_int_type(s2[i].item_code, item_code_op, item_code_check, item_code_check_count))
                {
                    s2[i].isvalid_record = 0;
                }
            
            }
        
            if (item_name_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_string_type(s2[i].item_name, item_name_op, item_name_check, item_name_check_count))
                {
                    s2[i].isvalid_record = 0;
                }
            
            }
        
            if (item_type_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_int_type(s2[i].item_type, item_type_op, item_type_check, item_type_check_count))
                {
                    s2[i].isvalid_record = 0;
                }
            
            }
        
            if (item_quantity_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_int_type(s2[i].item_quantity, item_quantity_op, item_quantity_check, item_quantity_flag))
                {
                    s2[i].isvalid_record = 0;
                }
            
            }
        
            if (item_price_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_float_type(s2[i].item_price, item_price_op, item_price_check, item_price_check_count))
                {
                    s2[i].isvalid_record = 0;
                }
            
            }
        
            if (item_reorder_level_flag == 1 && s2[i].isvalid_record)
            {
                if (!check_condition_int_type(s2[i].item_reorder_level, item_reorder_level_op, item_reorder_level_check, item_reorder_level_check_count))
                {
                    s2[i].isvalid_record = 0;
                }          
            }

            //printf("outside %d\n", i);
            if (s2[i].isvalid_record)
            {    
                //printf("inside %d\n", i);
                //#pragma omp critical
                relevant_records[relevant_records_count++] = i;
            }//make it atomic
        }
        
    }
    //gettimeofday(&TimeValue_Final, NULL);
}

void orderby(int order_seq)
{
    int i;
    printf("\nEnter the column to order by : ");
    scanf("%s", attribute);
    quicksort(relevant_records, 0, relevant_records_count - 1, attribute, 0);

}


void groupby()
{

    int i;
    printf("\nEnter the column to group by : ");
    scanf("%s", attribute);
    quicksort(relevant_records, 0, relevant_records_count - 1, attribute, 0);
    groupby_flag = 1;
    
}
void select_func(int no_of_records)
{
    int order_option;
    /*printf("Enter the colums to select\n");
    parseSelectMain();*/
    get_relevant_records(no_of_records);
    printf("\n0 - NO CONSTRAINTS\n1 - ORDER BY ASCENDING\n2 - ORDER BY DESCENDING\n3 - GROUP BY\n");
    scanf("%d", &order_option);
    switch(order_option)
    {
        case 1: orderby(1);
                break;
        case 2: orderby(2);
                break;
        case 3: groupby();
                break;
    }



}

void update_func(int no_of_records, int * update_records, int update_records_count)
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
        set_parse(set_columns);
    }
    //get_relevant_records(no_of_records);
    gettimeofday(&TimeValue_Start, NULL);
    #pragma omp parallel for if(update_records_count > PC)
    for(i = 0; i < update_records_count; i++)
    {
        if(set_item_code_flag)
        {
            s2[update_records[i]].item_code = set_item_code_check;
        }
        
        if(set_item_name_flag)
        {
            strcpy(s2[update_records[i]].item_name, set_item_name_check);
        }
      
        if(set_item_price_flag)
        {
            s2[update_records[i]].item_price = set_item_price_check;
        }
      
        if(set_item_quantity_flag)
        {
            s2[update_records[i]].item_quantity = set_item_quantity_check;
        }

        if(set_item_type_flag)
        {
            s2[update_records[i]].item_type = set_item_type_check;
        }
      
        if(set_item_reorder_level_flag)
        {
            s2[update_records[i]].item_reorder_level = set_item_reorder_level_check;
        }

    }
    gettimeofday(&TimeValue_Final, NULL);
    calcTime();
}

void delete_func(int no_of_records, int * delete_records, int delete_records_count)
{
    int i, record_id;
    //get_relevant_records(no_of_records);
    start_queue = end_queue = 0;
    //printf("faux %d\n", emptyAuxillaryArr(auxillary_arr, max_auxillary_arr));

    if((emptyAuxillaryArr(auxillary_arr, max_auxillary_arr) > delete_records_count))
    {
        //Add to queue
        //#pragma omp parallel for if (delete_records_count > PC)
        for (i = 0; i < delete_records_count; i++)
        {
            record_id = delete_records[i];
            s2[record_id].isAlive = 0;
            end_queue = (end_queue + 1) % max_auxillary_arr;
            auxillary_arr[end_queue] = record_id;   

        }
    }
    else
    {
        //Rearrange
        for (i = 0; i < delete_records_count; i++)
        {
            record_id = delete_records[i];
            s2[record_id].isAlive = 0;
        }


        int valid_record_pointer = no_of_records - 1;
        i = 0;

        while (i < valid_record_pointer)
        {
            if(s2[i].isvalid_record && !s2[valid_record_pointer].isvalid_record)
            {
                i++;
                valid_record_pointer--;
            }
            else if(!s2[i].isvalid_record && !s2[valid_record_pointer].isvalid_record)
            {
                valid_record_pointer--;
            }
            else if(s2[i].isvalid_record && s2[valid_record_pointer].isvalid_record)
                i++;
            else
            {
                s2[i] = s2[valid_record_pointer];
                s2[i].slno = i;
                s2[valid_record_pointer].isAlive = 0;
                i++;
                valid_record_pointer--;
            }
        }
        no_of_records = valid_record_pointer + 1;
    }

}

int reorderTrigger(int item_quantity)
{
    return 0.2 * item_quantity;
}

void insert_func()
{
    if(start_queue == end_queue)
    {
        s2[no_of_records].slno = no_of_records;
        printf("Enter the item code:");
        scanf("%d", &s2[no_of_records].item_code);//should be automatic
        printf("Enter the item name:");
        scanf("%s", s2[no_of_records].item_name);
        printf("Enter the item type:");
        scanf("%d", &s2[no_of_records].item_type);
        printf("Enter the item quantity:");
        scanf("%d", &s2[no_of_records].item_quantity);
        printf("Enter the item price:");
        scanf("%f", &s2[no_of_records].item_price);
        s2[no_of_records].item_reorder_level = reorderTrigger(s2[no_of_records].item_quantity);
        s2[no_of_records].isAlive = 1;
        no_of_records++ ;
    }
    else
    {
        s2[no_of_records + 1].slno = start_queue + 1;
        printf("Enter the item code:");
        scanf("%d", &s2[auxillary_arr[start_queue + 1]].item_code);
        printf("Enter the item name:");
        scanf("%s", s2[auxillary_arr[start_queue + 1]].item_name);
        printf("Enter the item type:");
        scanf("%d", &s2[auxillary_arr[start_queue + 1]].item_type);
        printf("Enter the item quantity:");
        scanf("%d", &s2[auxillary_arr[start_queue + 1]].item_quantity);
        printf("Enter the item price:");
        scanf("%f", &s2[auxillary_arr[start_queue + 1]].item_price);
        s2[start_queue + 1].item_reorder_level = reorderTrigger(s2[start_queue + 1].item_quantity);
        s2[no_of_records + 1].isAlive = 1;
        start_queue++ ;

    }
}

void tr_parseValue(char * value)
{
    int i;
    int loc_of_cb;
    int val_len;
    char * ptr;
    int ptr_len;
    char * loc;

    tr_no_of_val = 0;

    val_len = strlen(value);
    while((ptr = strchr(value, ',')) != NULL)
    {
        ptr_len = strlen(ptr);
        strncpy(tr_values[tr_no_of_val], value, val_len - ptr_len);
        tr_values[tr_no_of_val++][val_len - ptr_len] = '\0';
        value = ptr + 1;
        val_len = strlen(value);
    }

    loc_of_cb = strlen(strchr(value, ')'));
    strncpy(tr_values[tr_no_of_val], value, val_len - loc_of_cb);
    tr_values[tr_no_of_val++][val_len - loc_of_cb] = '\0';
    
    /*for (i = 0; i < no_of_val; i++)
    {
        puts(values[i]);
    }*/
}



void tr_callAggregate(int i)
{
    if(strcmp(tr_aggr[i].tr_agg_func, "sum") == 0 )
    {
        tr_giveSum(0, tr_relevant_records_count, tr_aggr[i].tr_agg_attribute);
    }
    else if(strcmp(tr_aggr[i].tr_agg_func, "avg") == 0)
    {
        tr_giveAverage(0, tr_relevant_records_count, tr_aggr[i].tr_agg_attribute);
    }
    else if (strcmp(tr_aggr[i].tr_agg_func, "min") == 0)
    {
        tr_giveMin(0, tr_relevant_records_count, tr_aggr[i].tr_agg_attribute);
    }
    else if(strcmp(tr_aggr[i].tr_agg_func, "max") == 0)
    {
        tr_giveMax(0, tr_relevant_records_count, tr_aggr[i].tr_agg_attribute);
    }
  /*  else if(strcmp(aggr[i].agg_func, "distinct") == 0)
    {
        strcpy(attribute, aggr[i].agg_attribute);
        printf("%sattribute\n",attribute);
        groupby_flag = 1;
        
    }*/
   /* else if(strcmp(agg_func, "count") == 0)
    {
        giveCount(agg_attribute);
    }*/
}

void tr_callAggregateGroupBy(int low, int high, int i)
{
        if(strcmp(tr_aggr[i].tr_agg_func, "sum") == 0 )
        {
            tr_giveSum(low, high, tr_aggr[i].tr_agg_attribute);
        }
        else if(strcmp(tr_aggr[i].tr_agg_func, "avg") == 0)
        {
            tr_giveAverage(low, high, tr_aggr[i].tr_agg_attribute);
        }
        else if (strcmp(tr_aggr[i].tr_agg_func, "min") == 0)
        {
            tr_giveMin(low, high, tr_aggr[i].tr_agg_attribute);
        }
        else if( strcmp(tr_aggr[i].tr_agg_func, "max") == 0)
        {
            tr_giveMax(low, high, tr_aggr[i].tr_agg_attribute);
        }
        
}


void tr_parseAggregate()
{
    int i;
    char * fob, * fcb;
    int agg_func_len;
    int att_len, llen;

    for (i = 0; i < tr_aggregate_list_count; i++)
    { 
        // printf("%s\n", aggregate_list[i]); 
        tr_aggr[i].tr_agg_func[0] = '\0';
        tr_aggr[i].tr_agg_attribute[0] = '\0'; 
        fob = strchr(tr_aggregate_list[i], '(');
        fcb = strchr(tr_aggregate_list[i], ')');
        att_len = strlen(fob);
        agg_func_len = strlen(tr_aggregate_list[i]) - att_len;
        strncpy(tr_aggr[i].tr_agg_func, tr_aggregate_list[i], agg_func_len);
        tr_aggr[i].tr_agg_func[agg_func_len] = '\0';
        /*strncpy(agg_attribute , fob + 1, att_len - 1);
        agg_attribute[att_len - 1] = '\0';*/
        llen = strlen(fcb);
        strncpy(tr_aggr[i].tr_agg_attribute , fob + 1, att_len - llen - 1);
        tr_aggr[i].tr_agg_attribute[att_len - llen - 1] = '\0';
        // printf("%s %s\n", agg_func, agg_attribute);
        if (strcmp(tr_aggr[i].tr_agg_func, "distinct") == 0)
        {
            strcpy(tr_attribute, tr_aggr[i].tr_agg_attribute);
            tr_groupby_flag = 1;
            tr_quicksort(tr_relevant_records, 0, tr_relevant_records_count - 1, tr_aggr[i].tr_agg_attribute, 0);
        }   
    }
}


void tr_parseSelect(char * value)
{
    int i;
    int loc_of_cb;
    int val_len;
    char * ptr;
    int ptr_len;
    char * loc;

    tr_no_of_col_sel = 0;
    val_len = strlen(value);
    
    while((ptr = strchr(value, ',')) != NULL)
    {
        ptr_len = strlen(ptr);
        strncpy(tr_col_sel[tr_no_of_col_sel], value, val_len - ptr_len);
        tr_col_sel[tr_no_of_col_sel++][val_len - ptr_len] = '\0';
        value = ptr + 1;
        val_len = strlen(value);
    }

    loc_of_cb = strlen(strrchr(value, ')'));
    strncpy(tr_col_sel[tr_no_of_col_sel], value, val_len - loc_of_cb);
    tr_col_sel[tr_no_of_col_sel++][val_len - loc_of_cb] = '\0';
    /*for (i = 0; i < no_of_val; i++)
    {
        puts(values[i]);
    }*/
}

void tr_parse(char * condition)
{
    int i, comp_cond;
    char * first, * last;
    char attribute[30];
    char value[30];
    int condlen, flen, llen;

    condlen = strlen(condition);//gets length of the condition
    first = strchr(condition, ' ');//get the first occurance of space
    last = strchr(condition, '(');//get the last occurance of space
    flen = condlen - strlen(first);//
    llen = condlen - strlen(last);//

    strncpy(attribute, condition, flen);
    attribute[flen] = '\0';//This has to be done. Otherwise garbage will be appended
    strcpy(value, condition + llen + 1);
    //puts(attribute);
    //puts(value);
    tr_parseValue(value);

    for (i = flen; i < llen; i++)
    {
        if (condition[i] == '>')
        {
            comp_cond = 3;
            break;
        }
        else if (condition[i] == '=')
        {
            comp_cond = 2;
            break;
        }
        else if (condition[i] == '<')
        {
            comp_cond = 1;
            break;
        }
        else if (condition[i] == 'I')
        {
            comp_cond = 2;
            break;
        }

    }

    if (strcmp(attribute, "item_code") == 0)
    {
        tr_item_code_op = comp_cond;

        for (i = 0; i < tr_no_of_val; i++)
        {
            tr_item_code_check[i] = atoi(tr_values[i]);
        }
        tr_item_code_check_count = tr_no_of_val;
        tr_item_code_flag = 1;
    }
    else if (strcmp(attribute, "transaction_id") == 0)
    {
        tr_id_op = comp_cond;

        for (i = 0; i < tr_no_of_val; i++)
        {
            tr_id_check[i] = atoi(tr_values[i]);
        }
        tr_id_check_count = tr_no_of_val;
        tr_id_flag = 1;
    }
    else if (strcmp(attribute, "transaction_quantity") == 0)
    {
        tr_quantity_op = comp_cond;

        for (i = 0; i < tr_no_of_val; i++)
        {
            tr_quantity_check[i] = atoi(tr_values[i]);
        }
        tr_quantity_check_count = tr_no_of_val;
        tr_quantity_flag = 1;
    }
    else if (strcmp(attribute, "total_price") == 0)
    {
        tr_price_op = comp_cond;

        for (i = 0; i < tr_no_of_val; i++)
        {
            tr_price_check[i] = atof(tr_values[i]);
        }
        tr_price_check_count = tr_no_of_val;
        tr_price_flag = 1;
    }
    else if (strcmp(attribute, "transaction_date") == 0)
    {
        tr_date_op = comp_cond;

        for (i = 0; i < tr_no_of_val; i++)
        {
            strcpy(tr_date_check[i], tr_values[i]);
        }
        tr_date_check_count = tr_no_of_val;
        tr_date_flag = 1;
    }
}

void tr_set_parse(char * set_columns)
{
    int i;
    char * first, * last;
    char attribute[30];
    char value[30];
    int condlen, flen, llen;

    condlen = strlen(set_columns);//gets length of the set_columns
    first = strchr(set_columns, ' ');//get the first occurance of space
    last = strrchr(set_columns, ' ');//get the last occurance of space
    flen = condlen - strlen(first);//
    llen = condlen - strlen(last);//

    strncpy(attribute, set_columns, flen);
    attribute[flen] = '\0';//This has to be done. Otherwise garbage will be appended
    strcpy(value, set_columns + llen + 1);
    //puts(attribute);
    //puts(value);
   if (strcmp(attribute, "item_code") == 0)
    {
        set_tr_item_code_check = atoi(value);
        set_tr_item_code_flag = 1;
    }
    else if (strcmp(attribute, "transaction_date") == 0)
    {
        int len;
        len = strlen(value);
        strncpy(set_tr_date_check, value, len - 1);
        set_tr_date_check[len] = '\0';
        set_tr_date_flag = 1;
    }
    else if (strcmp(attribute, "transaction_id") == 0)
    {
        set_tr_id_check = atoi(value);
        set_tr_id_flag = 1;
    }
    else if (strcmp(attribute, "transaction_quantity") == 0)
    {
        set_tr_quantity_check = atoi(value);
        set_tr_quantity_flag = 1;
    }
    else if (strcmp(attribute, "total_price") == 0)
    {
        set_tr_price_check = atof(value);
        set_tr_price_flag = 1;
    }
}


void tr_setSelectFlags(char set_of_sels[200])
{
    int i, j;
    int is_attribute;
    /*getchar();
    fgets(set_of_sels, 200, stdin);*/
    tr_parseSelect(set_of_sels);
    if (strcmp(tr_col_sel[0], "*") == 0)//need not always be 0th
    {
        for (j = 1; j <= 5; j++)
        {
            sel_trans_tab[j].trans_attribute_flag = 1;
        }
    }
    else
    {
        for (i = 0; i < tr_no_of_col_sel; i++)
        {
            is_attribute = 0;
            for (j = 1; j <= 5; j++)
            {
                if (strcmp(tr_col_sel[i], sel_trans_tab[j].trans_attribute) == 0)
                {
                    sel_trans_tab[j].trans_attribute_flag = 1;
                    is_attribute = 1;
                    break;
                }

            }
            if (!is_attribute)
            {
                strcpy(tr_aggregate_list[tr_aggregate_list_count++], tr_col_sel[i]) ;
                strcpy(join_aggregate_list[join_aggregate_list_count++], col_sel[i]);
            }
        }
    }   
}
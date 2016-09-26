void parseValue(char * value)
{
    int i;
    int loc_of_cb;
    int val_len;
    char * ptr;
    int ptr_len;
    char * loc;

    no_of_val = 0;

    val_len = strlen(value);
    while((ptr = strchr(value, ',')) != NULL)
    {
        ptr_len = strlen(ptr);
        strncpy(values[no_of_val], value, val_len - ptr_len);
        values[no_of_val++][val_len - ptr_len] = '\0';
        value = ptr + 1;
        val_len = strlen(value);
    }

    loc_of_cb = strlen(strchr(value, ')'));
    strncpy(values[no_of_val], value, val_len - loc_of_cb);
    values[no_of_val++][val_len - loc_of_cb] = '\0';
    
    /*for (i = 0; i < no_of_val; i++)
    {
        puts(values[i]);
    }*/
}



void callAggregate(int i)
{
        gettimeofday(&TimeValue_Start, NULL);
        if(strcmp(aggr[i].agg_func, "sum") == 0 )
        {
            giveSum(0, relevant_records_count, aggr[i].agg_attribute);
        }
        else if(strcmp(aggr[i].agg_func, "avg") == 0)
        {
            giveAverage(0, relevant_records_count, aggr[i].agg_attribute);
        }
        else if (strcmp(aggr[i].agg_func, "min") == 0)
        {
            giveMin(0, relevant_records_count, aggr[i].agg_attribute);
        }
        else if( strcmp(aggr[i].agg_func, "max") == 0)
        {
            giveMax(0, relevant_records_count, aggr[i].agg_attribute);
        }
        gettimeofday(&TimeValue_Final, NULL);
        calcTime();
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

void callAggregateGroupBy(int low, int high, int i)
{
        gettimeofday(&TimeValue_Start, NULL);
        if(strcmp(aggr[i].agg_func, "sum") == 0 )
        {
            giveSum(low, high, aggr[i].agg_attribute);
        }
        else if(strcmp(aggr[i].agg_func, "avg") == 0)
        {
            giveAverage(low, high, aggr[i].agg_attribute);
        }
        else if (strcmp(aggr[i].agg_func, "min") == 0)
        {
            giveMin(low, high, aggr[i].agg_attribute);
        }
        else if( strcmp(aggr[i].agg_func, "max") == 0)
        {
            giveMax(low, high, aggr[i].agg_attribute);
        }
        gettimeofday(&TimeValue_Final, NULL);
        calcTime();
        
}

void parseAggregate()
{
    int i;
    char * fob, * fcb;
    int agg_func_len;
    int att_len, llen;

    for (i = 0; i < aggregate_list_count; i++)
    { 
        // printf("%s\n", aggregate_list[i]); 
        aggr[i].agg_func[0] = '\0';
        aggr[i].agg_attribute[0] = '\0'; 
        fob = strchr(aggregate_list[i], '(');
        fcb = strchr(aggregate_list[i], ')');
        att_len = strlen(fob);
        agg_func_len = strlen(aggregate_list[i]) - att_len;
        strncpy(aggr[i].agg_func, aggregate_list[i], agg_func_len);
        aggr[i].agg_func[agg_func_len] = '\0';
        /*strncpy(agg_attribute , fob + 1, att_len - 1);
        agg_attribute[att_len - 1] = '\0';*/
        llen = strlen(fcb);
        strncpy(aggr[i].agg_attribute , fob + 1, att_len - llen - 1);
        aggr[i].agg_attribute[att_len - llen - 1] = '\0';
        // printf("%s %s\n", agg_func, agg_attribute);
        // puts(aggr[i].agg_func);
        // puts(aggr[i].agg_attribute);
        if (strcmp(aggr[i].agg_func, "distinct") == 0)
        {
            strcpy(attribute, aggr[i].agg_attribute);
            groupby_flag = 1;
            quicksort(relevant_records, 0, relevant_records_count - 1, aggr[i].agg_attribute, 0);
        }
        
    }
    
}

void parseSelect(char * value)
{
    int i;
    int loc_of_cb;
    int val_len;
    char * ptr;
    int ptr_len;
    char * loc;

    no_of_col_sel = 0;

   
    val_len = strlen(value);
    while((ptr = strchr(value, ',')) != NULL)
    {
        ptr_len = strlen(ptr);
        strncpy(col_sel[no_of_col_sel], value, val_len - ptr_len);
        col_sel[no_of_col_sel++][val_len - ptr_len] = '\0';
        value = ptr + 1;
        val_len = strlen(value);
    }

    loc_of_cb = strlen(strrchr(value, ')'));
    strncpy(col_sel[no_of_col_sel], value, val_len - loc_of_cb);
    col_sel[no_of_col_sel++][val_len - loc_of_cb] = '\0';
    
    /*for (i = 0; i < no_of_val; i++)
    {
        puts(values[i]);
    }*/
}
//This function stores the attributes in a string array.

void parse(char * condition)
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
    parseValue(value);

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
        item_code_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            item_code_check[i] = atoi(values[i]);
        }
        item_code_check_count = no_of_val;
        item_code_flag = 1;
    }
    else if (strcmp(attribute, "item_name") == 0)
    {
        item_name_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            strcpy(item_name_check[i], values[i]);
        }
        item_name_check_count = no_of_val;
        item_name_flag = 1;
    }
    else if (strcmp(attribute, "item_type") == 0)
    {
        item_type_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            item_type_check[i] = atoi(values[i]);
        }
        item_type_check_count = no_of_val;
        item_type_flag = 1;
    }
    else if (strcmp(attribute, "item_quantity") == 0)
    {
        item_quantity_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            item_quantity_check[i] = atoi(values[i]);
        }
        item_quantity_check_count = no_of_val;
        item_quantity_flag = 1;
    }
    else if (strcmp(attribute, "item_price") == 0)
    {
        item_price_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            item_price_check[i] = atof(values[i]);
        }
        item_price_check_count = no_of_val;
        item_price_flag = 1;
    }
    else if (strcmp(attribute, "item_reorder_level") == 0)
    {
        item_reorder_level_op = comp_cond;

        for (i = 0; i < no_of_val; i++)
        {
            item_reorder_level_check[i] = atoi(values[i]);
        }
        item_reorder_level_check_count = no_of_val;
        item_reorder_level_flag = 1;
    }

}

void set_parse(char * set_columns)
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
        set_item_code_check = atoi(value);
        set_item_code_flag = 1;
    }
    else if (strcmp(attribute, "item_name") == 0)
    {
        int len;
        len = strlen(value);
        strncpy(set_item_name_check, value, len - 1);
        set_item_name_check[len] = '\0';
        set_item_name_flag = 1;
    }
    else if (strcmp(attribute, "item_type") == 0)
    {
        set_item_type_check = atoi(value);
        set_item_type_flag = 1;
    }
    else if (strcmp(attribute, "item_quantity") == 0)
    {
        set_item_quantity_check = atoi(value);
        set_item_quantity_flag = 1;
    }
    else if (strcmp(attribute, "item_price") == 0)
    {
        set_item_price_check = atof(value);
        set_item_price_flag = 1;
    }
    else if (strcmp(attribute, "item_reorder_level") == 0)
    {

        set_item_reorder_level_check= atoi(value);
        set_item_reorder_level_flag = 1;
    }

}
//set the values in update function

void setSelectFlags(char set_of_sels[200])
{
    int i, j;
    int is_attribute;
    /*getchar();
    fgets(set_of_sels, 200, stdin);*/
    parseSelect(set_of_sels);//If from stdin then set_of_sel + 1
    if (strcmp(col_sel[0], "*") == 0)//need not always be 0th
    {
        for (j = 1; j <= 6; j++)
        {
            sel_item_tab[j].item_attribute_flag = 1;
        }
    }
    else
    {
        for (i = 0; i < no_of_col_sel; i++)
        {
            is_attribute = 0;
            for (j = 1; j <= 6; j++)
            {
                if (strcmp(col_sel[i], sel_item_tab[j].item_attribute) == 0)
                {
                    sel_item_tab[j].item_attribute_flag = 1;
                    is_attribute = 1;
                    break;
                }

            }
            if (!is_attribute)
            {
                strcpy(aggregate_list[aggregate_list_count++], col_sel[i]);
                strcpy(join_aggregate_list[join_aggregate_list_count++], col_sel[i]);
               

            }
        }
    }   
}

void parseSelectMain()
{
    char select_query[300], tab_attr[200];
    int i, j;
    char *ptrcsb, *ptrosb;
    int tab_nam_len, tab_attr_len;
    char tab_name[20];
    getchar();
    printf("Enter the columns to select\n");
    fgets(select_query, 300, stdin);
    //puts(select_query);
    ptrcsb = strchr(select_query, ']');
    while ((ptrcsb = strchr(select_query, ']')) != NULL)
    {
        ptrosb = strchr(select_query, '[');
        tab_nam_len = strlen(select_query) - strlen(ptrosb);
        strncpy(tab_name, select_query, tab_nam_len);
        tab_name[tab_nam_len] = '\0';
        tab_attr_len = strlen(select_query) - strlen(ptrcsb) - tab_nam_len;
        strncpy(tab_attr, select_query + tab_nam_len + 2, tab_attr_len - 2);//from the first character after ( to the closing bracket ')'.
        tab_attr[tab_attr_len - 2] = '\0';
        strcpy(select_query, ptrcsb + 2);
        // puts(tab_name);
        // puts(tab_attr);
        // puts(select_query);
        if (strcmp(tab_name,"item") == 0)
        {
            item_table_flag = 1;
            setSelectFlags(tab_attr);
        }
        else if (strcmp(tab_name, "transaction") == 0)
        {
            trans_table_flag = 1;
            tr_setSelectFlags(tab_attr);
        }
    }
    //parseSelect(set_of_sels + 1);
}
//This function gets the select query, splits it into parts based on the table names and then calls the respective parse function based on the tablename.

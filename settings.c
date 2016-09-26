void setInit()
{
    int i;
    for (i = 1; i <= 6; i++)
    {
        sel_item_tab[i].item_attribute_flag = 0;
    }
    strcpy(sel_item_tab[1].item_attribute, "item_code\0");
    strcpy(sel_item_tab[2].item_attribute, "item_name\0");
    strcpy(sel_item_tab[3].item_attribute, "item_type\0");
    strcpy(sel_item_tab[4].item_attribute, "item_quantity\0");
    strcpy(sel_item_tab[5].item_attribute, "item_price\0");
    strcpy(sel_item_tab[6].item_attribute, "item_reorder_level\0");
}

void reset_flags()
{
    int i = 0;
    set_item_name_flag = set_item_code_flag = set_item_price_flag = set_item_quantity_flag = set_item_reorder_level_flag = set_item_type_flag = 0;//update
    set_item_code_check = set_item_quantity_check = set_item_reorder_level_check = set_item_type_check = 0;
    set_item_price_check = 0;
    set_item_name_check[0] = '\0';

    item_name_flag = item_code_flag = item_price_flag = item_quantity_flag = item_reorder_level_flag = item_type_flag = 0;
    item_name_op = item_code_op = item_price_op = item_quantity_op = item_reorder_level_op = item_type_op = 0;
    item_code_check[0] = '\0';
    item_quantity_check[0] ='\0';
    item_reorder_level_check[0] = '\0';
    item_type_check[0] = '\0';
    item_price_check[0] = '\0';
    for( i = 0;i <20; i++)
        item_name_check[i][0] = '\0';

    select_item_name_flag = select_item_code_flag = select_item_price_flag = select_item_quantity_flag = select_item_reorder_level_flag = select_item_type_flag = 0;//select flag

    for (i = 1; i <= 6; i++)
    {
        sel_item_tab[i].item_attribute[0] = '\0';
        sel_item_tab[i].item_attribute_flag = 0;
    }

    relevant_records_count = 0;
    groupby_flag = 0;
}

int emptyAuxillaryArr(int *auxillary_arr, int max_auxillary_arr)
{
    if (end_queue >= start_queue)
    {
        free_queue_space = max_auxillary_arr - (end_queue - start_queue + 1);
    }
    else
    {
        free_queue_space = start_queue - end_queue - 1;
    }

    return free_queue_space;
}

void save_record()
{
    int i;
    i = no_of_records - 1;

    while (start_queue != end_queue)
    {
        if (s2[i].isAlive)
        {
            s2[auxillary_arr[start_queue + 1]] = s2[i];
            i--;
            start_queue++;
        }
        else
        {
            i--;
        }
    }
}
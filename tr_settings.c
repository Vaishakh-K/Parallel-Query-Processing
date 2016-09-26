void tr_setInit()
{
    int i;
    for (i = 1; i <= 5; i++)
    {
        sel_trans_tab[i].trans_attribute_flag = 0;
    }
    strcpy(sel_trans_tab[1].trans_attribute, "transaction_id\0");
    strcpy(sel_trans_tab[2].trans_attribute, "item_code\0");
    strcpy(sel_trans_tab[3].trans_attribute, "transaction_quantity\0");
    strcpy(sel_trans_tab[4].trans_attribute, "total_price\0");
    strcpy(sel_trans_tab[5].trans_attribute, "transaction_date\0");
}



void tr_reset_flags()
{
    int i = 0;
    set_tr_date_flag = set_tr_item_code_flag = set_tr_price_flag = set_tr_quantity_flag = set_tr_id_flag = 0;//update
    set_tr_item_code_check = set_tr_quantity_check = set_tr_id_check = 0;
    set_tr_price_check = 0;
    set_tr_date_check[0] = '\0';

    tr_date_flag = tr_item_code_flag = tr_price_flag = tr_quantity_flag = tr_id_flag = 0;
    tr_date_op = tr_item_code_op = tr_price_op = tr_quantity_op = tr_id_op = 0;
    tr_item_code_check[0] = '\0';
    tr_quantity_check[0] ='\0';
    tr_id_check[0] = '\0';
    tr_price_check[0] = '\0';
    for( i = 0;i < 20; i++)
        tr_date_check[i][0] = '\0';

    select_tr_date_flag = select_tr_item_code_flag = select_tr_price_flag = select_tr_quantity_flag = select_tr_id_flag = 0;//select flag

    for (i = 1; i <= 6; i++)
    {
        sel_trans_tab[i].trans_attribute[0] = '\0';
        sel_trans_tab[i].trans_attribute_flag = 0;
    }

    tr_relevant_records_count = 0;
    tr_groupby_flag = 0;
}

int tr_emptyAuxillaryArr(int *tr_auxillary_arr, int tr_max_auxillary_arr)
{
    if (tr_end_queue >= tr_start_queue)
    {
        tr_free_queue_space = tr_max_auxillary_arr - (tr_end_queue - tr_start_queue + 1);
    }
    else
    {
        tr_free_queue_space = tr_start_queue - tr_end_queue - 1;
    }

    return tr_free_queue_space;
}

void tr_save_record()
{
    int i;
    i = tr_no_of_records - 1;

    while (tr_start_queue != tr_end_queue)
    {
        if (tr_s2[i].isAlive)
        {
            tr_s2[tr_auxillary_arr[tr_start_queue + 1]] = tr_s2[i];
            i--;
            tr_start_queue++;
        }
        else
        {
            i--;
        }
    }
}
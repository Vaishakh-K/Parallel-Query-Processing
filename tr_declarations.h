struct transaction
{
	int slno;
	int transaction_id;
	int item_code;
	int transaction_quantity;
	float total_price;
	char transaction_date[10];//yyyy/mm/dd
	int isvalid_record;
    int isAlive;
};

struct select_table_transaction_table
{
	char trans_attribute[30];
    int trans_attribute_flag;
};

struct tr_aggregate 
{
	char tr_agg_func[10];
    char tr_agg_attribute[20];
};

extern struct aggregate aggr[10];

extern struct tr_aggregate tr_aggr[10];

extern struct select_table_item_table sel_item_tab[9];
extern struct select_table_transaction_table sel_trans_tab[6];

//Condition Flags
extern int tr_item_code_flag, tr_price_flag, tr_quantity_flag, tr_id_flag, tr_date_flag;
extern int tr_item_code_op, tr_price_op, tr_quantity_op, tr_id_op,  tr_date_op;
extern int tr_item_code_check[20], tr_quantity_check[20], tr_id_check[20];
extern float  tr_price_check[20];
extern char tr_date_check[20][30];
extern int tr_item_code_check_count, tr_price_check_count, tr_quantity_check_count, tr_id_check_count, tr_date_check_count;

//time
extern struct timeval  TimeValue_Start;
extern struct timeval  TimeValue_Final;

//Set Flags
extern int set_tr_item_code_flag, set_tr_id_flag, set_tr_price_flag, set_tr_quantity_flag, set_tr_date_flag; //update
extern int set_tr_item_code_check, set_tr_quantity_check, set_tr_id_check;
extern float set_tr_price_check;
extern char set_tr_date_check[30];
extern int tr_groupby_flag;


extern struct transaction tr_s[500000], tr_s2[500000], tr_t;
extern int tr_no_of_records;
extern int tr_no_of_val;//no of values for checking
extern char tr_values[20][30];//value set
 
extern int tr_relevant_records[500000];//To store relevant records ka slno from select query
extern int tr_relevant_records_count;//Count of relevant records from select query

extern int tr_auxillary_arr[10000], tr_max_auxillary_arr;//for deleting
extern int tr_start_queue, tr_end_queue, tr_free_queue_space;

extern int select_tr_item_code_flag, select_tr_id_flag, select_tr_price_flag, select_tr_quantity_flag, select_tr_date_flag;//select flag

extern int tr_no_of_col_sel;
extern char tr_col_sel[10][30];

extern char tr_attribute[30];

extern char tr_aggregate_list[10][30];
extern int tr_aggregate_list_count;

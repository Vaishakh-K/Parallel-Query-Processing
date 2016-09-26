struct item
{
	int slno;
	int item_code;
	char item_name[20];
	int item_type;
	int item_quantity;
	float item_price;
	int item_reorder_level; 
    int isvalid_record;
    int isAlive;
};

struct type
{
	int slno;
	int type_id;
	char type_name[20];
	char type_provider[30];
};

struct select_table_item_table
{
    char item_attribute[30];
    int item_attribute_flag;
};

struct aggregate 
{
	char agg_func[10];
    char agg_attribute[20];
};

struct join_aggregate 
{
	char agg_func[10];
    char agg_attribute[20];
};

extern struct aggregate aggr[10];
extern struct join_aggregate join_aggr[10];

extern struct select_table_item_table sel_item_tab[9];


//Condition Flags
extern int item_name_flag, item_code_flag, item_price_flag, item_quantity_flag, item_reorder_level_flag, item_type_flag;
extern int item_name_op, item_code_op, item_price_op, item_quantity_op, item_reorder_level_op, item_type_op;
extern int item_code_check[20], item_quantity_check[20], item_reorder_level_check[20], item_type_check[20];
extern float  item_price_check[20];
extern char item_name_check[20][30];
extern int item_code_check_count, item_name_check_count, item_type_check_count, item_quantity_check_count, item_price_check_count, item_reorder_level_check_count;

//time
extern struct timeval  TimeValue_Start;
extern struct timeval  TimeValue_Final;

//Set Flags
extern int set_item_name_flag, set_item_code_flag, set_item_price_flag, set_item_quantity_flag, set_item_reorder_level_flag, set_item_type_flag; //update
extern int set_item_code_check, set_item_quantity_check, set_item_reorder_level_check, set_item_type_check;
extern float set_item_price_check;
extern char set_item_name_check[30];
extern int groupby_flag;


extern struct item s[500000], s2[500000], t;
extern int no_of_records;
extern int no_of_val;//no of values for checking
extern char values[20][30];//value set
 
extern int relevant_records[500000];//To store relevant records ka slno from select query
extern int relevant_records_count;//Count of relevant records from select query

extern int auxillary_arr[10000], max_auxillary_arr;//for deleting
extern int start_queue, end_queue, free_queue_space;

extern int select_item_name_flag, select_item_code_flag, select_item_price_flag, select_item_quantity_flag, select_item_reorder_level_flag, select_item_type_flag;//select flag

extern int no_of_col_sel;
extern char col_sel[10][30];

extern char attribute[30];

extern char aggregate_list[10][30];
extern int aggregate_list_count;

struct combine
{
    int slno;
	int item_code;
	char item_name[20];
	int item_type;
	int item_quantity;
	float item_price;
	int item_reorder_level; 
	int transaction_id;
	int transaction_quantity;
	float total_price;
	char transaction_date[10];//yyyy/mm/dd 
};

extern struct combine join_tb[5000000];
extern int no;

extern int item_table_flag, trans_table_flag;
extern int delete_flag, update_flag;

extern int join_delete[500000];
extern int delcount;

extern int join_update[500000];//join update
extern int updcount;

extern char join_attribute[30];
extern char join_aggregate_list[10][30];
extern int join_aggregate_list_count;
extern int join_groupby_flag;

extern long time_start, time_end;
extern double time_overhead;


#define PC 100
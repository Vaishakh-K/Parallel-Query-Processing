#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

#include "declarations.h"
#include "tr_declarations.h"
#include "tools.c"
#include "qsort.c"
#include "tr_qsort.c"
#include "aggregate.c"
#include "tr_aggregate.c"
#include "join_aggregate.c"
#include "tr_parse.c"
#include "parse.c"
#include "display.c"
#include "tr_display.c"
#include "conditions.c"
#include "settings.c"
#include "tr_settings.c"
#include "queries.c"
#include "tr_queries.c"
#include "joinfiles.c"

struct select_table_item_table sel_item_tab[9];

//Condition Flags
int item_name_flag, item_code_flag, item_price_flag, item_quantity_flag, item_reorder_level_flag, item_type_flag;
int item_name_op, item_code_op, item_price_op, item_quantity_op, item_reorder_level_op, item_type_op;
int item_code_check[20], item_quantity_check[20], item_reorder_level_check[20], item_type_check[20];
float  item_price_check[20];
char item_name_check[20][30];
int item_code_check_count, item_name_check_count, item_type_check_count, item_quantity_check_count, item_price_check_count, item_reorder_level_check_count;

//time
struct timeval  TimeValue_Start;
struct timeval  TimeValue_Final;

//Set Flags
int set_item_name_flag, set_item_code_flag, set_item_price_flag, set_item_quantity_flag, set_item_reorder_level_flag, set_item_type_flag; //update
int set_item_code_check, set_item_quantity_check, set_item_reorder_level_check, set_item_type_check;
float set_item_price_check;
char set_item_name_check[30];
int groupby_flag = 0;


struct item s[500000], s2[500000], t;
int no_of_records;
int no_of_val;//no of values
char values[20][30];//value set

int relevant_records[500000];//To store relevant records ka slno from select query
int relevant_records_count = 0;//Count of relevant records from select query

int auxillary_arr[10000], max_auxillary_arr = 10000;//for deleting
int start_queue, end_queue, free_queue_space;

int select_item_name_flag, select_item_code_flag, select_item_price_flag, select_item_quantity_flag, select_item_reorder_level_flag, select_item_type_flag;//select flag

int no_of_col_sel;
char col_sel[10][30];

char attribute[30];

char aggregate_list[10][30];//Reset later
int aggregate_list_count = 0;

struct aggregate aggr[10];

//That of item table

struct tr_aggregate tr_aggr[10];

struct select_table_item_table sel_item_tab[9];
struct select_table_transaction_table sel_trans_tab[6];

//Condition Flags
int tr_item_code_flag, tr_price_flag, tr_quantity_flag, tr_id_flag, tr_date_flag;
int tr_item_code_op, tr_price_op, tr_quantity_op, tr_id_op,  tr_date_op;
int tr_item_code_check[20], tr_quantity_check[20], tr_id_check[20];
float  tr_price_check[20];
char tr_date_check[20][30];
int tr_item_code_check_count, tr_price_check_count, tr_quantity_check_count, tr_id_check_count, tr_date_check_count;

//time
struct timeval  TimeValue_Start;
struct timeval  TimeValue_Final;

//Set Flags
int set_tr_item_code_flag, set_tr_id_flag, set_tr_price_flag, set_tr_quantity_flag, set_tr_date_flag; //update
int set_tr_item_code_check, set_tr_quantity_check, set_tr_id_check;
float set_tr_price_check;
char set_tr_date_check[30];
int tr_groupby_flag;


struct transaction tr_s[500000], tr_s2[500000], tr_t;
int tr_no_of_records;
int tr_no_of_val;//no of values for checking
char tr_values[20][30];//value set
 
int tr_relevant_records[500000];//To store relevant records ka slno from select query
int tr_relevant_records_count;//Count of relevant records from select query

int tr_auxillary_arr[10000], tr_max_auxillary_arr;//for deleting
int tr_start_queue, tr_end_queue, tr_free_queue_space;

int select_tr_item_code_flag, select_tr_id_flag, select_tr_price_flag, select_tr_quantity_flag, select_tr_date_flag;//select flag

int tr_no_of_col_sel;
char tr_col_sel[10][30];

char tr_attribute[30];

char tr_aggregate_list[10][30];
int tr_aggregate_list_count;
//That of Transaction Table

struct combine join_tb[5000000];
int no;
int item_table_flag, trans_table_flag;
int delete_flag, update_flag;
int join_delete[500000];//join delete
int delcount;
int join_update[500000];//join update
int updcount;
char join_aggregate_list[10][30];
int join_aggregate_list_count = 0;
struct join_aggregate join_aggr[10];
char join_attribute[30];
int join_groupby_flag;

/*******************************************/
long time_start, time_end;
double time_overhead;

/**************************************************************************************************************************************************************************/

void parseCondition()
{
    int i, n_of_cond;
    char fullcondition[100];
    char *condition;
    int len_of_tname;
    char tname[20];
    printf("\nNumber of conditions : ");
    scanf("%d", &n_of_cond);
    getchar();//to ignore the \n
    for (i = 0; i < n_of_cond; i++)
    {
        fgets(fullcondition, 100, stdin);
        //puts(condition);
        condition = strchr(fullcondition, '.');
        len_of_tname = strlen(fullcondition) - strlen(condition);
        strncpy(tname, fullcondition, len_of_tname);
        tname[len_of_tname] = '\0';
        // puts(tname);
        if (strcmp(tname, "item") == 0)
        {
            item_table_flag = 1;
            parse(condition + 1);
        }
        else if (strcmp(tname, "transaction") == 0)
        {
            trans_table_flag = 1;
            tr_parse(condition + 1);
        }
        
    }
}

void selectq(int no_of_records)
{
    int order_option;
	parseSelectMain();
	parseCondition();
    gettimeofday(&TimeValue_Start, NULL);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (item_table_flag)
                get_relevant_records(no_of_records);
        }

        #pragma omp section
        {
            if (trans_table_flag)
                tr_get_relevant_records(no_of_records);
        }
    }
	gettimeofday(&TimeValue_Final, NULL);

    calcTime();
    
    if (item_table_flag && trans_table_flag)
    {
        gettimeofday(&TimeValue_Start, NULL);
        joinTablesSelect();
        gettimeofday(&TimeValue_Final, NULL);
        calcTime();
    }

    printf("\nSelect the Ordering Constraints\n0 - NO CONSTRAINTS\n1 - ORDER BY ASCENDING\n2 - ORDER BY DESCENDING\n3 - GROUP BY\n");
    scanf("%d", &order_option);

    switch(order_option)
    {
        case 1: if (item_table_flag && !trans_table_flag)
                {
                    orderby(1);
                }
                else if (trans_table_flag && !item_table_flag)
                {
                    tr_orderby(1);
                }
                else if (item_table_flag && trans_table_flag)
                {
                    join_orderby(1);
                }
                break;

        case 2: if (item_table_flag && !trans_table_flag)
                {
                    orderby(2);
                }
                else if (trans_table_flag && !item_table_flag)
                {
                    tr_orderby(2);
                }
                else if (item_table_flag && trans_table_flag)
                {
                    join_orderby(2);
                }
                break;
                
        case 3: if (item_table_flag && !trans_table_flag)
                {
                    groupby();
                }
                else if (trans_table_flag && !item_table_flag)
                {
                    tr_groupby();
                }
                else if (item_table_flag && trans_table_flag)
                {
                    join_groupby();
                }
                break;
    }

}

void updateq(int no_of_records)
{
    char tname[20];
    printf("Enter the tablename which you want to update\n");
    scanf("%s", tname); 
    if (strcmp(tname, "item") == 0)
    {
        update_flag = 0;
        item_table_flag = 1;
    }

    else if (strcmp(tname, "transaction") == 0)
    {
        update_flag = 1;
        trans_table_flag = 1;
    }

    parseCondition();
    
    gettimeofday(&TimeValue_Start, NULL);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (item_table_flag)
                get_relevant_records(no_of_records);
        }

        #pragma omp section
        {
            if (trans_table_flag)
                tr_get_relevant_records(no_of_records);
        }
    }
    gettimeofday(&TimeValue_Final, NULL);
    calcTime();
    if (item_table_flag && !trans_table_flag) // code added here
    {
        update_func(no_of_records, relevant_records, relevant_records_count);
    }

    else if (trans_table_flag && !item_table_flag)
    {
        tr_update_func(tr_no_of_records, tr_relevant_records, tr_relevant_records_count);
    }
    
    else if (item_table_flag && trans_table_flag)
    {
        gettimeofday(&TimeValue_Start, NULL);
        joinTablesUpdate();
        gettimeofday(&TimeValue_Final, NULL);
        calcTime();
        if (update_flag == 0)
        {
            update_func(no_of_records, join_update, updcount);
        }
        else
        {
            tr_update_func(tr_no_of_records, join_update, updcount);
        }
    }



}

void deleteq(int no_of_records)
{
    char tname[20];
    printf("Enter the tablename from which you want to delete\n");
    scanf("%s", tname);
    if (strcmp(tname, "item") == 0)
    {
        delete_flag = 0;
        item_table_flag = 1;
    }

    else if (strcmp(tname, "transaction") == 0)
    {
        delete_flag = 1;
        trans_table_flag = 1;
    }

    parseCondition();
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            if (item_table_flag)
                get_relevant_records(no_of_records);
        }

        #pragma omp section
        {
            if (trans_table_flag)
                tr_get_relevant_records(no_of_records);
        }
    }

   
    if (item_table_flag && !trans_table_flag)
    {
        delete_func(no_of_records, relevant_records, relevant_records_count);
    }

    else if (trans_table_flag && !item_table_flag)
    {
        tr_delete_func(tr_no_of_records, tr_relevant_records, tr_relevant_records_count);
    }
    
    else if (item_table_flag && trans_table_flag)
    {
        joinTablesDelete();

        if (delete_flag == 0)
        {
            delete_func(no_of_records, join_delete, delcount);
        }
        else
        {
            tr_delete_func(tr_no_of_records, join_delete, delcount);
        }
    }
}

void insertq()
{
    char tname[20];
    printf("Enter the table to which you want to insert\n");
    scanf("%s", tname);
    if (strcmp(tname, "item") == 0)
    {
        insert_func();
    }

    else if (strcmp(tname, "transaction") == 0)
    {
        tr_insert_func();
    }
}

int main()
{

	int i, ct;
    FILE *fptr, *tr_fptr;


    int query;
    int * join_delete = (int *) malloc (500000 * sizeof(int));//join delete
    int * join_update = (int *) malloc (500000 * sizeof(int));//join update
    // int * relevant_records = (int *) malloc (500000 * sizeof(int));//To store relevant records ka slno from select query
    // int * tr_relevant_records = (int *) malloc (500000 * sizeof(int));//To store relevant records ka slno from select query
    //omp_set_num_threads(8);
    printf("\nEnter the number of records\n");
    scanf("%d", &no_of_records);
    printf("\nEnter Which Command\nPress\n");
    printf("1 - SELECT\n");
    printf("2 - UPDATE\n");
    printf("3 - DELETE\n");
    printf("4 - INSERT\n");
    //printf("5 - QUIT\n");
    scanf("%d", &query);

    setInit();
    tr_setInit();

    fptr = fopen("record.txt", "rb");
    fread(s2, sizeof(s2), 1, fptr);

    tr_fptr = fopen("tr_record.txt", "rb");
    fread(tr_s2, sizeof(tr_s2), 1, tr_fptr);

    switch(query)
    {
        case 1: selectq(no_of_records);
                break;

        case 2: updateq(no_of_records);
                break;

        case 3: deleteq(no_of_records);
                break;

        case 4: insertq();
                break;

        default: printf("Enter Valid Command\n");

    }

    gettimeofday(&TimeValue_Start, NULL);
    parseAggregate();
    tr_parseAggregate();
    join_parseAggregate();//added on 5
    gettimeofday(&TimeValue_Final, NULL);
    calcTime();

    if (query == 1)
    {
        if (item_table_flag && !trans_table_flag)
        {
    	   if(!groupby_flag)
    	   {
        	   printRelevantRecords();
        	} // end of normal display

    	   else //groupby display
    	   {
        	   groupByDisplayCount();
    	   }   
        }

        else if (trans_table_flag && !item_table_flag)
        {
     	  if(!tr_groupby_flag)
    	   {
        	   tr_printRelevantRecords();
    	   } // end of normal display

    	   else //groupby display
    	   {
        	   tr_groupByDisplayCount();
    	   }
        }

        else if (item_table_flag && trans_table_flag)
        {
            //joinTablesSelect();
            if (!join_groupby_flag)
            {
                printJoin();
            }
            else
            {
                join_groupByDisplayCount();
            }            
        }
    }

    save_record();
    reset_flags();

    tr_save_record();
    tr_reset_flags();

    fptr = fopen("record.txt", "wb");
    fwrite(s2, sizeof(s2), 1, fptr);

    tr_fptr = fopen("tr_record.txt", "wb");
    fwrite(tr_s2, sizeof(tr_s2), 1, tr_fptr);

    printf("Time Overhead = %lf\n", time_overhead);  

    return 0;

}
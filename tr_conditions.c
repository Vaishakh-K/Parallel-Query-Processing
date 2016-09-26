
int check_condition_int_type(int record_value, int op, int * key_value, int no_of_val)
{
    int i;
    //printf("rec %d key %d op %d\n", record_value, key_value[0], op);
    switch (op)
    {
        case 1 :if (record_value < key_value[0])
                {
                    return 1;
                } 
                else
                {
                    return 0;
                }

        case 2 :for (i = 0; i < no_of_val; i++)
                {
                    if (record_value == key_value[i])
                    {
                        return 1;
                    }
                }
                return 0;
                

        case 3 :if (record_value > key_value[0])
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

        default:return 0;
    }
}


int check_condition_float_type(float record_value, int op, float  * key_value, int no_of_val)
{
    int i;
    //printf("rec %f key %f\n", record_value, key_value);
    switch (op)
    {
        case 1 :if (record_value < key_value[0])
                {
                    return 1;
                } 
                else
                {
                    return 0;
                }

        case 2 :for (i = 0; i < no_of_val; i++)
                {
                    if (record_value == key_value[i])
                    {
                        return 1;
                    }
                }
                return 0;

        case 3 :if (record_value > key_value[0])
                {
                    return 1;
                }
                else
                {
                    return 0;
                }

        default:return 0;
    }
}

int check_condition_string_type(char * record_value, int op, char key_value[20][30], int no_of_val)
{
    int klen, i, rlen, j;

    rlen = strlen(record_value);
    for (j = 0; j < no_of_val; j++)
    {
        /*klen = strlen(key_value[j]);
        printf("rec %s key %s rlen %d klen %d\n", record_value, key_value[j], rlen, klen);

        if (rlen == klen)
        {
            printf("Imi in fr loop\n");
            for (i = 0; i < klen - 1; i++)
            {
                if (key_value[j][i] != record_value[i])
                {
                    printf("%c %c\n", key_value[j][i], record_value[i]);
                    break;
                }
            }
            if (i == klen)
            {
                return 1;
            }   
        }*/
        if (strcmp(record_value, key_value[j]) == 0)
        {
            return 1;
        }
    }

    return 0;

}
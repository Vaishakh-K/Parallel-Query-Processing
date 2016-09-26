void tr_giveSum(int low, int high, char tr_agg_attribute[20])
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(tr_agg_attribute, "transaction_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)
			for (i = low; i < high; i++)
			{
				sum += tr_s2[tr_relevant_records[i]].transaction_quantity;
			}

		printf("Sum of %s is %d\n", tr_agg_attribute, sum);
	}

	else if (strcmp(tr_agg_attribute, "total_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)
			for (i = low; i < high; i++)
			{
				sum1 += tr_s2[tr_relevant_records[i]].total_price;
			}

		printf("Sum of %s is %f\n",tr_agg_attribute, sum1);
	}
}

void tr_giveMax(int low, int high, char tr_agg_attribute[20])
{
	int i, max_val;
	float max_val1;



	if (strcmp(tr_agg_attribute, "transaction_quantity") == 0)
	{
		max_val = tr_s2[tr_relevant_records[0]].transaction_quantity;
		#pragma omp parallel for reduction(max:max_val)
			for (i = low; i < high; i++)
			{
				if (max_val < tr_s2[tr_relevant_records[i]].transaction_quantity)
					max_val = tr_s2[tr_relevant_records[i]].transaction_quantity;
			}

		printf("Maximum of %s is %d\n", tr_agg_attribute, max_val);
	}

	else if (strcmp(tr_agg_attribute, "total_price") == 0)
	{
		max_val1 = tr_s2[tr_relevant_records[0]].total_price;
		#pragma omp parallel for reduction(max:max_val1)
			for (i = low; i < high; i++)
			{
				if (max_val1 < tr_s2[tr_relevant_records[i]].total_price)
					max_val1 = tr_s2[tr_relevant_records[i]].total_price;
			}

		printf("Maximum of %s is %f\n", tr_agg_attribute, max_val1);
	}

}

void tr_giveMin(int low, int high, char tr_agg_attribute[20])
{
	int i, min_val;
	float min_val1;


	if (strcmp(tr_agg_attribute, "transaction_quantity") == 0)
	{
		min_val = tr_s2[tr_relevant_records[0]].transaction_quantity;
		#pragma omp parallel for reduction(min:min_val)
			for (i = low; i < high; i++)
			{
				if (min_val > tr_s2[tr_relevant_records[i]].transaction_quantity)
					min_val = tr_s2[tr_relevant_records[i]].transaction_quantity;
			}

		printf("Minimum of %s is %d\n", tr_agg_attribute, min_val);
	}

	else if (strcmp(tr_agg_attribute, "total_price") == 0)
	{
		min_val1 = tr_s2[tr_relevant_records[0]].total_price;
		#pragma omp parallel for reduction(min:min_val1)
			for (i = low; i < high; i++)
			{
				if (min_val1 > tr_s2[tr_relevant_records[i]].total_price)
					min_val1 = tr_s2[tr_relevant_records[i]].total_price;
			}

		printf("Minimum of %s is %f\n", tr_agg_attribute, min_val1);
	}
}

void tr_giveAverage(int low, int high, char tr_agg_attribute[20])//Average of item_quantity should be integer
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(tr_agg_attribute, "transaction_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)
			for (i = low; i < high; i++)
			{
				sum += tr_s2[tr_relevant_records[i]].transaction_quantity;
			}

		printf("Average of %s is %f\n", tr_agg_attribute, (float)sum / tr_relevant_records_count);
	}

	else if (strcmp(tr_agg_attribute, "total_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)
			for (i = low; i < high; i++)
			{
				sum1 += tr_s2[tr_relevant_records[i]].total_price;
			}

		printf("Average of %s is %f\n", tr_agg_attribute, (float)sum1 / tr_relevant_records_count);
	}

}

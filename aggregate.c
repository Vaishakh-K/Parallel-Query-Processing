void giveSum(int low, int high, char agg_attribute[20])
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(agg_attribute, "item_quantity") == 0)
	{
		#pragma omp parallel for schedule(static) reduction(+:sum)	
			for (i = low; i < high; i++)
			{
				sum += s2[relevant_records[i]].item_quantity;
			}

		printf("Sum of %s is %d\n", agg_attribute, sum);
	}

	else if (strcmp(agg_attribute, "item_price") == 0)
	{
		#pragma omp parallel for schedule(runtime) reduction(+:sum1)
			for (i = low; i < high; i++)
			{
				sum1 += s2[relevant_records[i]].item_price;
			}

		printf("Sum of %s is %f\n", agg_attribute, sum1);
	}
}

void giveMax(int low, int high, char agg_attribute[20])
{
	int i, max_val;
	float max_val1;

	

	if (strcmp(agg_attribute, "item_quantity") == 0)
	{
		max_val = s2[relevant_records[0]].item_quantity;
		#pragma omp parallel for reduction(max:max_val)
			for (i = low; i < high; i++)
			{
				if (max_val < s2[relevant_records[i]].item_quantity)
					max_val = s2[relevant_records[i]].item_quantity;
			}

		printf("Maximum of %s is %d\n", agg_attribute, max_val);	
	}

	else if (strcmp(agg_attribute, "item_price") == 0)
	{
		max_val1 = s2[relevant_records[0]].item_price;
		#pragma omp parallel for reduction(max:max_val1)	
			for (i = low; i < high; i++)
			{
				if (max_val1 < s2[relevant_records[i]].item_price)
					max_val1 = s2[relevant_records[i]].item_price;
			}

		printf("Maximum of %s is %f\n", agg_attribute, max_val1);
	}

}

void giveMin(int low, int high, char agg_attribute[20])
{
	int i, min_val;
	float min_val1;
	

	if (strcmp(agg_attribute, "item_quantity") == 0)
	{
		min_val = s2[relevant_records[0]].item_quantity;
		#pragma omp parallel for reduction(min:min_val)	
			for (i = low; i < high; i++)
			{
				if (min_val > s2[relevant_records[i]].item_quantity)
					min_val = s2[relevant_records[i]].item_quantity;
			}

		printf("Minimum of %s is %d\n", agg_attribute, min_val);	
	}

	else if (strcmp(agg_attribute, "item_price") == 0)
	{
		min_val1 = s2[relevant_records[0]].item_price;
		#pragma omp parallel for reduction(min:min_val1)	
			for (i = low; i < high; i++)
			{
				if (min_val1 > s2[relevant_records[i]].item_price)
					min_val1 = s2[relevant_records[i]].item_price;
			}

		printf("Minimum of %s is %f\n", agg_attribute, min_val1);
	}
}

void giveAverage(int low, int high, char agg_attribute[20])//Average of item_quantity should be integer
{
	int i, sum = 0;
	float sum1 = 0;

	if (strcmp(agg_attribute, "item_quantity") == 0)
	{
		#pragma omp parallel for reduction(+:sum)	
			for (i = low; i < high; i++)
			{
				sum += s2[relevant_records[i]].item_quantity;
			}

		printf("Average of %s is %d\n", agg_attribute, sum / relevant_records_count);
	}

	else if (strcmp(agg_attribute, "item_price") == 0)
	{
		#pragma omp parallel for reduction(+:sum1)	
			for (i = low; i < high; i++)
			{
				sum1 += s2[relevant_records[i]].item_price;
			}

		printf("Average of %s is %f\n", agg_attribute, (float)sum1 / relevant_records_count);
	}
	
}

# Parallel-Query-Processing

Authors
Vaishakh K(13IT149), Pravalika A(13IT127), Samanvith A(13IT138), Abhishek Devasya V(13IT202)

To run,
gcc main.c
./a.out

To run with parallel constructs,
gcc main.c -fopenmp
./a.out


Enter Number of Records

Enter Which Command
Press
1 - SELECT
2 - UPDATE
3 - DELETE
4 - INSERT
5 - Get Items whose quantity is less than Reorder Level

SELECT
tablename1[(columnname1,columnname2,...)],tablename2[(columnname1,columnname2,...)] 
OR
tablename[(*)]
OR
tablename[(aggrfun(colname))]
eg: item[(sum(item_quantity))]


Conditions:
tablename.columnname op (value) where op can be '>, <, =, in'

Order By,
Enter the column to order by : columnname

Group By,
Enter the column to group by : item_type



Examaple:
Enter the number of records
100

Enter Which Command
Press
1 - SELECT
2 - UPDATE
3 - DELETE
4 - INSERT
1
Enter the columns to select
item[(sum(item_quantity))]

Number of conditions : 0

Select the Ordering Constraints
0 - NO CONSTRAINTS
1 - ORDER BY ASCENDING
2 - ORDER BY DESCENDING
3 - GROUP BY
3

Enter the column to group by : item_type
item_type	Count
0		96		Sum of item_quantity is 26143

1		2		Sum of item_quantity is 103

3		1		Sum of item_quantity is 123

6		1		Sum of item_quantity is 90

Time Overhead = 0.005098


INSERT, DELETE and UPDATE follow similar syntax. Use conditions like stated above

